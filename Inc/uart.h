#ifndef UART_H_
#define UART_H_
#include <stdint.h>

#define STM32F103xB
#include "stm32f1xx.h"

void uart_init(void);
void uart_transmit(uint8_t ch);
void uart_send_string(const char *str);

#endif /* UART_H_ */
