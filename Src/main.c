#include "systick.h"
#include "spi.h"
#include "mpu.h"
#include "uart.h"


void main(void){
	systick_init();//SysTick & 72MHz clock initialization
	spi_init();//SPI initialization
	mpu_init();//MPU initialization
	uart_init();//UART initialization

	while(1){
		//Subhan Allah
	}
}
