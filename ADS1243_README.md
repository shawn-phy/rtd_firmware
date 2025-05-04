# ADS1243 RTD Temperature Measurement Library

## Overview

This library provides a complete solution for interfacing with the ADS1243 24-bit ADC for high-precision RTD temperature measurement. It supports both PT100 and PT1000 RTD sensors with automatic detection and scaling.

## Author Information

- **Author:** Shawn Philip Oyuga
- **Email:** philipoyuga14@gmail.com
- **Repository:** https://github.com/shawn-phy/rtd_firmware


## Features

- Complete CMSIS-based SPI interface for STM32F103
- ADS1243 24-bit ADC driver with all essential functions
- Support for both PT100 and PT1000 RTD sensors
- Automatic RTD type detection based on resistance value
- Multiple temperature calculation methods
- High precision temperature measurement

## Files

### SPI Configuration

- **spi_config.h** - SPI interface declarations
- **spi_config.c** - SPI implementation using CMSIS direct register access

### ADS1243 ADC Driver

- **ads1243.h** - ADS1243 interface declarations
- **ads1243.c** - ADS1243 implementation

### RTD Temperature Conversion

- **rtd.h** - RTD class declarations
- **rtd.cpp** - RTD implementation with support for PT100 and PT1000

### Example Application

- **ads1243_rtd_example.c** - Example application demonstrating the complete system

## Usage

### SPI Configuration

```c
// Initialize SPI
spi1_init();

// Transfer data
uint8_t data = spi1_transfer(0x55);

// Control chip select
spi1_cs_low();
spi1_cs_high();
```

### ADS1243 ADC

```c
// Initialize ADS1243
ads1243_init();

// Calibrate the ADC
ads1243_calibrate();

// Select input channel
ads1243_set_channel(0);

// Read ADC value
uint32_t adc_value = ads1243_read_adc();

// Convert to voltage
float voltage = ads1243_to_voltage(adc_value, 2.5f);
```

### RTD Temperature Measurement

```c
// Create RTD object
RTD sensor;

// Read RTD resistance
float rtd_resistance = read_rtd_resistance();

// Auto-detect RTD type
if(rtd_resistance > 400.0f) {
    sensor.setType(RTD_PT1000);
} else {
    sensor.setType(RTD_PT100);
}

// Calculate temperature
float temperature = sensor.celsius(rtd_resistance);
```

## Implementation Notes

- The SPI configuration is optimized for the STM32F103 microcontroller
- The ADS1243 driver uses the standard SPI protocol as specified in the datasheet
- The RTD library supports multiple calculation methods for different accuracy/performance tradeoffs
- The example application demonstrates automatic detection between PT100 and PT1000 sensors

## License

MIT License

Copyright (c) 2025 Shawn Philip Oyuga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
