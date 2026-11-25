#include "uart.h"

void uart_init(void){
	RCC->APB2ENR |= (1<<14)|(1<<2);//USART1 and port A Enabled

	GPIOA->CRH &= ~(0xFF<<4); //Reset PA10,9
	GPIOA->CRH |= (0x4B<<4);//PA10 as input float, PA9 Alternate fun push pull 50 MHz output

	USART1->BRR=0x271;//(72MHz/115,200 baud rate)=625=0x271

	USART1->CR1 |= ((1<<13)|(3<<2));//USART1 Enabled, Transmitter & Receiver Enabled
}

void uart_transmit(uint8_t ch){
	while(!(USART1->SR & (1<<7)));//Wait for TXE flag

	USART1->DR=ch;
}
