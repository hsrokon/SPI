#include "spi.h"
#include <stdint.h>

volatile uint8_t chip_id;//Got output 112(Dec)-0x70-WHO_AM_I

uint8_t spi_transfer(uint8_t data){
	while(!(SPI1->SR & (1<<1)));//Wait until transmit buffer empty
	SPI1->DR = data;//Sending byte
	//Hardware shifts bit to internal shift register, complete bit gets copied to RX buffer(SPI1->DR) & sets RXNE flag
	while(!(SPI1->SR & (1<<0)));//Wait for received buffer not empty flag

	//Reading received byte
	return (uint8_t) SPI1->DR;//Reading RX buffer(DR), automatically clears RXNE flag
}

uint8_t mpu_read_register(uint8_t reg){
	GPIOA->BSRR = (1<<16+4);//pulling it to low, to wake up mpu
	spi_transfer(0x80|reg);//0x80=1000 0000, 7th bit = 1 = Read
	//this first byte sends 8 clock, msb gets sent first, mpu decodes the address, loads value in that address and waits for another byte/8 clock pulses
	//During this time whatever bits was is mpu's shift reg gets pushed through miso, SPI1->DR receives garbage byte

	uint8_t rx_data = spi_transfer(0xFF);//Pushing dummy byte to gen 8 clock pulses to receive decoded address value from mpu

	while((SPI1->SR & (1<<7)));//Even though RXNE flag occurs, spi clock needs some time for cleanup, so wait until spi is busy
	GPIOA->BSRR = (1<<4);//Pulling line high (NSS) to mark end of communication
	return rx_data;
}

void main(void){

	RCC->APB2ENR |= (1<<12)|(1<<2); // SPI1 and port A enabled
	GPIOA->CRL &= ~(0xFFFF<<16);//7(MOSI)-SDA,6(MISO)-ADO,5(SCK)-SCL, 4(NSS)-NCS reset
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

	chip_id = mpu_read_register(0x75);//Reading WHO_AM_I register, returns chip id

	while(1){

	}
}
