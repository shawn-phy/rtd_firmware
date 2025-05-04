/******************************************************************************
 * File: ads1243.h
 * Author: Shawn Philip Oyuga
 * Email: philipoyuga14@gmail.com
 * Repository: https://github.com/shawn-phy/rtd_firmware
 *
 * Description: Interface for ADS1243 24-bit ADC for RTD temperature measurement
 *
 * License: MIT License
 *
 * Copyright (c) 2025 Shawn Philip Oyuga
 ******************************************************************************/

#ifndef ADS1243_H
#define ADS1243_H

#include "stm32f10x.h" // sneaky little HAL :) cause it wont compile without this include.
#include "spi_config.h"
#include <stdint.h>

#define ADS1243_CMD_RESET      0xFE
#define ADS1243_CMD_RDATA      0x01
#define ADS1243_CMD_RDATAC     0x03
#define ADS1243_CMD_SDATAC     0x0F
#define ADS1243_CMD_RREG       0x10
#define ADS1243_CMD_WREG       0x50
#define ADS1243_CMD_SELFCAL    0xF0
#define ADS1243_CMD_SELFOCAL   0xF1
#define ADS1243_CMD_SELFGCAL   0xF2
#define ADS1243_CMD_SYSOCAL    0xF3
#define ADS1243_CMD_SYSGCAL    0xF4
#define ADS1243_CMD_WAKEUP     0xFD
#define ADS1243_CMD_DSYNC      0xFC
#define ADS1243_CMD_SLEEP      0xFD

#define ADS1243_REG_SETUP      0x00
#define ADS1243_REG_MUX        0x01
#define ADS1243_REG_ACR        0x02
#define ADS1243_REG_ODAC       0x03
#define ADS1243_REG_DIO        0x04
#define ADS1243_REG_DIR        0x05
#define ADS1243_REG_IOCON      0x06
#define ADS1243_REG_OCR0       0x07
#define ADS1243_REG_OCR1       0x08
#define ADS1243_REG_OCR2       0x09
#define ADS1243_REG_FSR0       0x0A
#define ADS1243_REG_FSR1       0x0B
#define ADS1243_REG_FSR2       0x0C

void ads1243_init(void);
void ads1243_reset(void);
void ads1243_write_reg(uint8_t reg, uint8_t value);
uint8_t ads1243_read_reg(uint8_t reg);
uint32_t ads1243_read_adc(void);
void ads1243_set_channel(uint8_t channel);
void ads1243_calibrate(void);
float ads1243_to_voltage(uint32_t adc_value, float vref);

#endif
