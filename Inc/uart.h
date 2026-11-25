#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart_transmit(uint8_t ch);
void uart_send_string(const char *str);

#endif /* UART_H_ */
