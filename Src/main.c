#include "spi.h"
#include <stdint.h>


uint8_t spi_communicates(){
	GPIOA->BSRR = (1<<4+16);//pulling low

	while(!(SPI1->SR & (1<<1)));//Wait until transmit buffer empty

	SPI1->DR = (0xFF);//Sending dummy date to transmit buffer for transmit

	while(!(SPI1->SR & (1<<0)));//Wait for received buffer not empty flag


	//Setting PA4 high by marking end of transmission
	GPIOA->BSRR = (1<<4);

	//Reading data
	return (uint8_t) SPI1->DR;
}

void main(void){

	RCC->APB2ENR |= (1<<12)|(1<<2); // SPI1 and port A enabled
	GPIOA->CRL &= ~(0xFFFF<<16);//7(MOSI),6(MISO),5(SCK), 4(NSS) reset
	//Configuring as a MASTER
	GPIOA->CRL |=(0xB4B3<<16);//Alternate function output push pull for MOSI, SCK | Input float for MISO
	//Output mode 50MHz push-pull for PA4 chip select pin, so we can manually set it high(3.3) & low/GND

	//Since Hardware select has a problem, we use software select & control NSS pin by controlling corresponding ODR bit through BSRR
	GPIOA->BSRR = (1<<4);//For BSRR always have to use direct assignment"=", bcz its write only. |= wastes cpu instructions.

	//SPI Control Register 1 configuration following (25.3.3) configuring master mode procedure
	//Resetting is not req. since the following bits are set with equal operator,that also resets whole register including DFF, LSB First, BRR, CPOL CPHA
	SPI1->CR1 = (3<<8)|(2<<3)|(1<<2)|(3<<0);//setting baud rate for 1MHz, by dividing fpclk/8, Assuming 8MHz APB clock speed
	//Setting both SSM SSI and CPOL CPHA to 1, Selecting as a Master
	SPI1->CR1 |= (1<<6);//SPI enabled

	uint8_t val = spi_communicates();

	while(1){

	}
}
