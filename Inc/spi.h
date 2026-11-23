#ifndef SPI_H_
#define SPI_H_

#define STM32F103xB
#include "stm32f1xx.h"

void spi_init(void);
uint8_t spi_transfer(uint8_t data);
uint8_t mpu_read_register(uint8_t reg);

#endif /* SPI_H_ */
