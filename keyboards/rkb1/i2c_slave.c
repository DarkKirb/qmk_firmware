#include "i2c_slave.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include <string.h>
#include "transactions.h"

// Code taken from here: https://github.com/harsha-vk/weeder_bot/blob/0bb2ac3f627dc2b3867480d210c0536ae0f684a5/assets/raspberry_pi_pico_code/src/i2c_slave.cpp

static volatile bool    is_callback_executor = false;
volatile uint8_t        i2c_slave_reg[I2C_SLAVE_REG_COUNT];
static volatile uint8_t buffer_address;
static volatile bool    sub_has_register_set = false;

static volatile bool transfer_in_progress = false;
enum i2c_event_t { I2C_SUB_RECEIVE, I2C_SUB_REQUEST, I2C_SUB_FINISH };

static void i2c_sub_handler(enum i2c_event_t event) {
    // uint8_t ack = 1;
    switch (event) {
        case I2C_SUB_RECEIVE: {
            while (i2c_get_read_available(i2c1)) {
                if (!sub_has_register_set) {
                    i2c_read_raw_blocking(i2c1, (uint8_t *)&buffer_address, 1);
                    if (buffer_address >= I2C_SLAVE_REG_COUNT) {
                        // ack = 0;
                        buffer_address = 0;
                    }
                    sub_has_register_set = true;
                    is_callback_executor = buffer_address == split_transaction_table[I2C_EXECUTE_CALLBACK].initiator2target_offset;
                } else {
                    // find out how many bytes we can safely read
                    uint32_t bytes_left    = I2C_SLAVE_REG_COUNT - buffer_address;
                    uint32_t bytes_to_read = i2c_get_read_available(i2c1);
                    uint32_t num_bytes     = (bytes_left < bytes_to_read) ? bytes_left : bytes_to_read;
                    i2c_read_raw_blocking(i2c1, (uint8_t *)i2c_slave_reg + buffer_address, num_bytes);
                    buffer_address += num_bytes;
                    if (buffer_address >= I2C_SLAVE_REG_COUNT) buffer_address = 0;
                    // If we're intending to execute a transaction callback, do so, as we've just received the transaction ID
                    if (is_callback_executor) {
                        split_transaction_desc_t *trans = &split_transaction_table[split_shmem->transaction_id];
                        if (trans->slave_callback) {
                            trans->slave_callback(trans->initiator2target_buffer_size, split_trans_initiator2target_buffer(trans), trans->target2initiator_buffer_size, split_trans_target2initiator_buffer(trans));
                        }
                    }
                }
            }
        } break;
        case I2C_SUB_REQUEST: {
            i2c_write_raw_blocking(i2c1, (uint8_t *)i2c_slave_reg + buffer_address, 1);
            buffer_address++;
            break;
        }
        case I2C_SUB_FINISH:
            sub_has_register_set = false;
            is_callback_executor = false;
            break;
    }
    // TODO: ack??
}

static void finish_transfer(void) {
    transfer_in_progress = false;
    i2c_sub_handler(I2C_SUB_FINISH);
}

static void i2c_handler(void) {
    i2c_hw_t *hw        = i2c_get_hw(i2c1);
    uint32_t  intr_stat = hw->intr_stat;
    if (intr_stat == 0) return; // spurious
    if (intr_stat & I2C_IC_INTR_STAT_R_TX_ABRT_BITS) {
        hw->clr_tx_abrt;
        finish_transfer();
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_START_DET_BITS) {
        hw->clr_start_det;
        finish_transfer();
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_STOP_DET_BITS) {
        hw->clr_stop_det;
        finish_transfer();
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_RX_FULL_BITS) {
        transfer_in_progress = true;
        i2c_sub_handler(I2C_SUB_RECEIVE);
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_RD_REQ_BITS) {
        hw->clr_rd_req;
        transfer_in_progress = true;
        i2c_sub_handler(I2C_SUB_REQUEST);
    }
}

void cos_i2c_slave_init(uint8_t address) {
    i2c_init(i2c1, 100 * 1000);
    i2c_set_slave_mode(i2c1, true, address);
    gpio_set_function(18, GPIO_FUNC_I2C);
    gpio_set_function(19, GPIO_FUNC_I2C);
    gpio_pull_up(18);
    gpio_pull_up(19);

    i2c_hw_t *hw  = i2c_get_hw(i2c1);
    hw->intr_mask = I2C_IC_INTR_MASK_M_RX_FULL_BITS | I2C_IC_INTR_MASK_M_RD_REQ_BITS | I2C_IC_RAW_INTR_STAT_TX_ABRT_BITS | I2C_IC_INTR_MASK_M_STOP_DET_BITS | I2C_IC_INTR_MASK_M_START_DET_BITS;
    irq_set_exclusive_handler(I2C1_IRQ, i2c_handler);
    irq_set_enabled(I2C1_IRQ, true);
}

void cos_i2c_slave_stop(void) {
    i2c_set_slave_mode(i2c1, false, 0);
    i2c_deinit(i2c1);
}
