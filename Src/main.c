#include "clock.h"
#include "systick.h"
#include "spi.h"
#include "mpu.h"
#include "uart.h"


void main(void){
	clock_init_72mhz();//72MHz clock initialization
	systick_init();//SysTick initialization
	spi_init();//SPI initialization, port A enable includes here
	uart_init();//UART initialization, must be after spi_init, since uart uses port A

	while(1){
		//Subhan Allah
	}
}
