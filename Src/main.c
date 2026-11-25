#include "systick.h"
#include "spi.h"
#include "mpu.h"
#include "uart.h"
#include <stdio.h>//for snprintf


void main(void){
	systick_init();//SysTick & 72MHz clock initialization
	spi_init();//SPI initialization
	mpu_init();//MPU initialization
	uart_init();//UART initialization

	mpu_data_t mpu_data;// reserves 14 bytes on stack to store 7 int16_t readings
	char tx_buffer[160];// reserves 160 consecutive 1 byte slot in ram

	while(1){
		mpu_read_all(&mpu_data);//Fetches fresh sensor data
		snprintf(tx_buffer, sizeof(tx_buffer),
		"accel_x: %d\r\naccel_y: %d\r\naccel_z: %d\r\n"
		"temp_raw: %d\r\n"
		"gyro_x: %d\r\ngyro_y: %d\r\ngyro_z: %d\r\nSubhan Allah\r\n",
		mpu_data.accel_x,mpu_data.accel_y,mpu_data.accel_z,
		mpu_data.temp_raw,
		mpu_data.gyro_x,mpu_data.gyro_y,mpu_data.gyro_z
		);//snprintf converts each int16_t into ASCII characters, auto puts null terminator(\0) at the end never writes past the end of buffer

		uart_send_string(tx_buffer);//Sending the whole converted string
		delay_ms(100);
		//Subhan Allah
	}
}
