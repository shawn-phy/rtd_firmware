/******************************************************************************
 * File: spi_config.c
 * Author: Shawn Philip Oyuga
 * Email: philipoyuga14@gmail.com
 * Repository: https://github.com/shawn-phy/rtd_firmware
 *
 * Description: SPI configuration implementation for STM32F103 using CMSIS
 *
 * License: MIT License
 *
 * Copyright (c) 2025 Shawn Philip Oyuga
 ******************************************************************************/

#include "spi_config.h"

void spi1_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;

    GPIOA->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    GPIOA->CRL |= (0x02 << GPIO_CRL_MODE5_Pos) | (0x02 << GPIO_CRL_CNF5_Pos);

    GPIOA->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
    GPIOA->CRL |= (0x00 << GPIO_CRL_MODE6_Pos) | (0x01 << GPIO_CRL_CNF6_Pos);

    GPIOA->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
    GPIOA->CRL |= (0x02 << GPIO_CRL_MODE7_Pos) | (0x02 << GPIO_CRL_CNF7_Pos);

    GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
    GPIOA->CRL |= (0x02 << GPIO_CRL_MODE4_Pos);

    GPIOA->BSRR |= GPIO_BSRR_BS4;

    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE | SPI_CR1_BR_0;
}

uint8_t spi1_transfer(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_RXNE));
    return SPI1->DR;
}

void spi1_cs_low(void) {
    GPIOA->BRR = GPIO_BRR_BR4;
}

void spi1_cs_high(void) {
    GPIOA->BSRR = GPIO_BSRR_BS4;
}
