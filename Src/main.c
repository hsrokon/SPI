#include "systick.h"
#include "spi.h"
#include "mpu.h"
#include "uart.h"


void main(void){
	systick_init();//SysTick & 72MHz clock initialization
	spi_init();//SPI initialization, port A enable includes here
	uart_init();//UART initialization, must be after spi_init, since uart uses port A

	while(1){
		//Subhan Allah
	}
}
