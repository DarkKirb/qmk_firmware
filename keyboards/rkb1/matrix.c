#include QMK_KEYBOARD_H
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "matrix.pio.h"
#include "split_util.h"

// Faster, PIO based matrix scanning routines
// It sets up two DMAs that feed a PIO FSM to scan the matrix.

static uint32_t          matrix_scan_input[] __attribute__((aligned(8))) = {0x01020408, 0x10200000};
static int               tx_chan, rx_chan;
static volatile uint32_t matrix_scan_result;

static void dma_handler(void) {
    // Restart the DMAs when they have finished
    if (!dma_channel_is_busy(tx_chan)) {
        dma_channel_acknowledge_irq0(tx_chan);
        dma_channel_set_trans_count(tx_chan, ~0, true);
        if (debug_matrix) {
            uprintf("TX DMA restarted\n");
        }
    }
    if (!dma_channel_is_busy(rx_chan)) {
        dma_channel_acknowledge_irq0(rx_chan);
        dma_channel_set_trans_count(rx_chan, ~0, true);
        if (debug_matrix) {
            uprintf("RX DMA restarted\n");
        }
    }
}

void matrix_init_custom(void) {
    PIO  pio    = pio0;
    uint offset = pio_add_program(pio, &matrix_program);
    uint sm     = pio_claim_unused_sm(pio, true);
    matrix_program_init(pio, sm, offset, 0);

    uint tx_dreq = pio_get_dreq(pio, sm, true);
    uint rx_dreq = pio_get_dreq(pio, sm, false);

    tx_chan = dma_claim_unused_channel(true);

    dma_channel_config tx_cfg = dma_channel_get_default_config(tx_chan);

    channel_config_set_read_increment(&tx_cfg, true);
    channel_config_set_write_increment(&tx_cfg, false);
    channel_config_set_dreq(&tx_cfg, tx_dreq);
    channel_config_set_transfer_data_size(&tx_cfg, DMA_SIZE_32);
    channel_config_set_ring(&tx_cfg, false, 3); // wrap read around

    dma_channel_set_config(tx_chan, &tx_cfg, false);
    dma_channel_set_irq0_enabled(tx_chan, true);
    dma_channel_set_read_addr(tx_chan, matrix_scan_input, false);
    dma_channel_set_write_addr(tx_chan, &pio0_hw->txf[sm], false);

    // Set up the rx channel
    rx_chan = dma_claim_unused_channel(true);

    dma_channel_config rx_cfg = dma_channel_get_default_config(rx_chan);
    channel_config_set_read_increment(&rx_cfg, false);
    channel_config_set_write_increment(&rx_cfg, false);
    channel_config_set_dreq(&rx_cfg, rx_dreq);
    channel_config_set_transfer_data_size(&rx_cfg, DMA_SIZE_32);

    dma_channel_set_config(rx_chan, &rx_cfg, false);
    dma_channel_set_irq0_enabled(rx_chan, true);
    dma_channel_set_read_addr(rx_chan, &pio0_hw->rxf[sm], false);
    dma_channel_set_write_addr(rx_chan, &matrix_scan_result, false);

    // Set up IRQs for restarting the DMAs
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
    // Call the IRQ handler manually to reset the trans counts and start the DMA channels
    dma_handler();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // Copy over the matrix scan result to avoid concurrent access from DMA
    uint32_t local_state      = matrix_scan_result;
    uint32_t local_state_copy = local_state;

    int start_row = isLeftHand ? 0 : 5;

    for (int row = 0; row < 5; row++) {
        // get a new matrix row by shifting it out of the state
        matrix_row_t new_row = local_state & 0x1F;
        local_state >>= 5;
        // check if the row has changed
        matrix_has_changed |= (current_matrix[start_row + row] != new_row);
        // update the current matrix
        current_matrix[start_row + row] = new_row;
    }

    if (debug_matrix && matrix_has_changed) {
        uprintf("Matrix scan: %08lx\n", local_state_copy);
    }

    return matrix_has_changed;
}
