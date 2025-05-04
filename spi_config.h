/******************************************************************************
 * File: spi_config.h
 * Author: Shawn Philip Oyuga
 * Email: philipoyuga14@gmail.com
 * Repository: https://github.com/shawn-phy/rtd_firmware
 *
 * Description: SPI configuration for STM32F103 using CMSIS
 *
 * License: MIT License
 *
 * Copyright (c) 2025 Shawn Philip Oyuga
 ******************************************************************************/

#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

#include "stm32f10x.h"
#include <stdint.h>

void spi1_init(void);
uint8_t spi1_transfer(uint8_t data);
void spi1_cs_low(void);
void spi1_cs_high(void);

#endif
