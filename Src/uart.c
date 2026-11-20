#include "uart.h"

void uart_init(void){
	RCC->APB2ENR |= (1<<14);//USART1 Enabled

	GPIOA->CRH &= ~(FF<<4); //Reset PA10,9
	GPIOA->CRH |= (0x4B<<4);//PA10 as input float, PA9 Alternate fun push pull 50 MHz output

	//USART1->BRR=xxxx;

	USART1->CR |= ((1<<13)|(3<2));//USART1 Enabled, Transmitter & Receiver Enabled
}

void uart_transmit(void){
	while(!(USART1->SR & (1<<7)));//Wait for TXE flag

	//USART1->DR=...;
}
