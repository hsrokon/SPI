#include "spi.h"

void main(void){

	RCC->APB2ENR |= (1<<12)|(1<<2); // SPI1 and port A enabled
	GPIOA->CRL &= ~(0xFFF<<5);//7(MOSI),6(MISO),5(SCK) reset
	//Configuring as a MASTER
	GPIOA->CRL |=(0xB4B<<5);//Alternate function output push pull for MOSI, SCK | Input float for MISO

	//SPI Control Register 1 configuration following (25.3.3) configuring master mode procedure
	SPI1->CR1 &= ~(7<<3);//Resetting
	SPI1->CR1 |= (2<<3);//setting baud rate for 1MHz, by dividing fpclk/8, Assuming 8MHz APB clock speed

}
