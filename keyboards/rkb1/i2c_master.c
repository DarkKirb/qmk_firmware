// rp2040 implementation of i2c_master.c
#include "i2c_master.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include <string.h>

void cos_i2c_init(void) {
    static bool is_initialized = false;
    if (!is_initialized) {
        is_initialized = true;

        gpio_set_function(18, GPIO_FUNC_I2C);
        gpio_set_function(19, GPIO_FUNC_I2C);
        gpio_pull_up(18);
        gpio_pull_up(19);
    }
}

static bool enabled = false;
static void init_i2c(void) {
    if (!enabled) {
        i2c_init(i2c1, 100 * 1000); // 100kb/s
        enabled = true;
    }
}

static uint8_t i2c_address;

static i2c_status_t pico_to_qmk(int result) {
    if (result == PICO_ERROR_TIMEOUT) return I2C_STATUS_TIMEOUT;
    if (result < 0) return I2C_STATUS_ERROR;
    return I2C_STATUS_SUCCESS;
}

i2c_status_t cos_i2c_start(uint8_t address) {
    i2c_address = address;
    init_i2c();
    return I2C_STATUS_SUCCESS;
}

i2c_status_t cos_i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout) {
    cos_i2c_start(address);
    return pico_to_qmk(i2c_write_timeout_us(i2c1, address, data, (size_t)length, false, (uint32_t)timeout * 1000));
}

i2c_status_t cos_i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout) {
    cos_i2c_start(address);
    return pico_to_qmk(i2c_read_timeout_us(i2c1, address, data, (size_t)length, false, (uint32_t)timeout * 1000));
}

i2c_status_t cos_i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout) {
    cos_i2c_start(devaddr);
    uint8_t complete_packet[length + 1];
    memcpy(complete_packet + 1, data, (size_t)length);
    complete_packet[0] = regaddr;

    return cos_i2c_transmit(devaddr, complete_packet, length + 1, timeout);
}

i2c_status_t cos_i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
    cos_i2c_start(devaddr);
    // TODO: uses 2x timeout
    i2c_status_t reg_result = cos_i2c_transmit(devaddr, &regaddr, 1, timeout);
    if (reg_result != I2C_STATUS_SUCCESS) return reg_result;
    return cos_i2c_receive(devaddr, data, length, timeout);
}

void cos_i2c_stop(void) {
    enabled = false;
    i2c_deinit(i2c1);
}
