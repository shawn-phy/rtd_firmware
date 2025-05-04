/******************************************************************************
 * File: ads1243.c
 * Author: Shawn Philip Oyuga
 * Email: philipoyuga14@gmail.com
 * Repository: https://github.com/shawn-phy/rtd_firmware
 *
 * Description: Implementation for ADS1243 24-bit ADC interface
 *
 * License: MIT License
 *
 * Copyright (c) 2025 Shawn Philip Oyuga
 ******************************************************************************/

#include "ads1243.h"

void ads1243_init(void) {
    spi1_init();
    spi1_cs_high();

    ads1243_reset();

    uint8_t setup_reg = 0x04;
    ads1243_write_reg(ADS1243_REG_SETUP, setup_reg);

    uint8_t mux_reg = 0x01;
    ads1243_write_reg(ADS1243_REG_MUX, mux_reg);
}

void ads1243_reset(void) {
    spi1_cs_low();
    spi1_transfer(ADS1243_CMD_RESET);
    spi1_cs_high();

    for(volatile uint32_t i = 0; i < 800000; i++);
}

void ads1243_write_reg(uint8_t reg, uint8_t value) {
    spi1_cs_low();
    spi1_transfer(ADS1243_CMD_WREG | reg);
    spi1_transfer(0x00);
    spi1_transfer(value);
    spi1_cs_high();
}

uint8_t ads1243_read_reg(uint8_t reg) {
    uint8_t value;

    spi1_cs_low();
    spi1_transfer(ADS1243_CMD_RREG | reg);
    spi1_transfer(0x00);
    value = spi1_transfer(0x00);
    spi1_cs_high();

    return value;
}

uint32_t ads1243_read_adc(void) {
    uint32_t adc_value = 0;

    spi1_cs_low();
    spi1_transfer(ADS1243_CMD_RDATA);

    for(volatile uint32_t i = 0; i < 24000; i++);

    adc_value = (uint32_t)spi1_transfer(0x00) << 16;
    adc_value |= (uint32_t)spi1_transfer(0x00) << 8;
    adc_value |= (uint32_t)spi1_transfer(0x00);

    spi1_cs_high();

    return adc_value;
}

void ads1243_set_channel(uint8_t channel) {
    if(channel > 7) return;

    uint8_t mux_value = (channel << 4) | 0x01;
    ads1243_write_reg(ADS1243_REG_MUX, mux_value);
}

void ads1243_calibrate(void) {
    spi1_cs_low();
    spi1_transfer(ADS1243_CMD_SELFCAL);
    spi1_cs_high();

    for(volatile uint32_t i = 0; i < 1600000; i++);
}

float ads1243_to_voltage(uint32_t adc_value, float vref) {
    float voltage;

    if(adc_value & 0x800000) {
        adc_value = (~adc_value + 1) & 0xFFFFFF;
        voltage = -((float)adc_value * vref) / 8388608.0f;
    } else {
        voltage = ((float)adc_value * vref) / 8388608.0f;
    }

    return voltage;
}
