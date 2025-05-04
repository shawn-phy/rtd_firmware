/******************************************************************************
 * File: ads1243_rtd_example.c
 * Author: Shawn Philip Oyuga
 * Email: philipoyuga14@gmail.com
 * Repository: https://github.com/shawn-phy/rtd_firmware
 *
 * Description: Example application using ADS1243 ADC with RTD temperature sensors
 *              Demonstrates automatic detection between PT100 and PT1000 sensors
 *
 * License: MIT License
 *
 * Copyright (c) 2025 Shawn Philip Oyuga
 ******************************************************************************/

#include "stm32f10x.h"
#include "ads1243.h"
#include "rtd.h"
#include <stdint.h>

#define RREF 4000.0f
#define VREF 2.5f

void delay_ms(uint32_t ms) {
    for(volatile uint32_t i = 0; i < ms * 8000; i++);
}

float read_rtd_resistance(void) {
    uint32_t adc_value = ads1243_read_adc();
    float voltage = ads1243_to_voltage(adc_value, VREF);
    float current = VREF / RREF;
    float resistance = voltage / current;
    return resistance;
}

int main(void) {
    ads1243_init();
    ads1243_calibrate();
    ads1243_set_channel(0);

    RTD sensor;

    while(1) {
        float rtd_resistance = read_rtd_resistance();

        if(rtd_resistance > 400.0f) {
            sensor.setType(RTD_PT1000);
        } else {
            sensor.setType(RTD_PT100);
        }

        float temperature = sensor.celsius(rtd_resistance);

        delay_ms(1000);
    }
}
