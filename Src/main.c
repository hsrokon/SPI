#include "spi.h"

void main(void){

	RCC->APB2ENR |= (1<<12)|(1<<2); // SPI1 and port A enabled
	GPIOA->CRL &= ~(0xFFFF<<16);//7(MOSI),6(MISO),5(SCK), 4(NSS) reset
	//Configuring as a MASTER
	GPIOA->CRL |=(0xB4B3<<16);//Alternate function output push pull for MOSI, SCK | Input float for MISO
	//Output mode 50MHz, GPO push-pull for PA4, chip select pin, so we can manually set it high(3.3) & low/GND

	//Since Hardware select has a problem, we use software select & control NSS pin by controlling corresponding ODR bit through BSRR
	GPIOA->BSRR = (1<<4);

	//SPI Control Register 1 configuration following (25.3.3) configuring master mode procedure
	//Resetting is not req. since the following bits are set with equal operator,that also resets whole register including DFF, LSB First, BRR, CPOL CPHA
	SPI1->CR1 |= (3<<8)|(2<<3)|(1<<2)|(3<<0);//setting baud rate for 1MHz, by dividing fpclk/8, Assuming 8MHz APB clock speed
	//Setting both SSM SSI and CPOL CPHA to 1, Selecting as a Master
	SPI1->CR1 |= (1<<6);//SPI enabled

	while(1){

	}
}
