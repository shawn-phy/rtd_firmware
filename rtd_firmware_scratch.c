#include "stm32f10x.h"

void delay(volatile uint32_t d) {
    while (d--);
}

void spi1_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;

    GPIOA->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5); 
    GPIOA->CRL |= (0x02 << GPIO_CRL_MODE5_Pos) | (0x02 << GPIO_CRL_CNF5_Pos); 

    GPIOA->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
    GPIOA->CRL |= (0x00 << GPIO_CRL_MODE6_Pos) | (0x01 << GPIO_CRL_CNF6_Pos); 

    GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4); 
    GPIOA->CRL |= (0x02 << GPIO_CRL_MODE4_Pos); 

    GPIOA->BSRR |= GPIO_BSRR_BS4;

    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE | SPI_CR1_BR_0;
}

uint16_t mcp3201_read_raw(void) {
    uint8_t h, l;
    uint16_t v;

    GPIOA->BRR = GPIO_BRR_BR4;

    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = 0xFF;
    while (!(SPI1->SR & SPI_SR_RXNE));
    h = SPI1->DR;

    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = 0xFF;
    while (!(SPI1->SR & SPI_SR_RXNE));
    l = SPI1->DR;

    GPIOA->BSRR = GPIO_BSRR_BS4;

    v = ((h << 8) | l) >> 1;
    return v & 0x0FFF;
}

float calculate_temperature(uint16_t adc_val) {
    const float Vref = 3.3f;
    const float ADCmax = 4095.0f;
    const float Rref = 100.0f;
    const float alpha = 0.00385f;

    float Vadc = (adc_val / ADCmax) * Vref;

    float gain = 5.0f;
    float Iexc = 1.0e-3f;

    float Vpt = Vadc / gain;
    float Rpt = Vpt / Iexc;

    float temp = (Rpt - Rref) / (Rref * alpha);
    return temp;
}

int main(void) {
    spi1_init();
    while (1) {
        uint16_t adc = mcp3201_read_raw();
        float temp = calculate_temperature(adc);
        delay(10000);
    }
}
