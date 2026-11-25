#include "mpu.h"
#include "systick.h"
#include "spi.h"


uint8_t mpu_read_reg(uint8_t reg){
	cs_low();
	spi_transfer(0x80|reg);//0x80=1000 0000, 7th bit = 1 = Read | reg is our target register to read
	//this first byte sends 8 clock, msb gets sent first, mpu decodes the address, loads value in that address and waits for another byte/8 clock pulses
	//During this time whatever bits was is mpu's shift reg gets pushed through miso, SPI1->DR receives garbage byte

	uint8_t rx_data = spi_transfer(0xFF);//Pushing dummy byte to gen 8 clock pulses to receive decoded address value from mpu

	cs_high();

	return rx_data;
}

void mpu_write_reg(uint8_t reg, uint8_t val){
	cs_low();
	spi_transfer(0x7F & reg);// 0x7F=0111 1111, 7th bit =0=write, doing & operation clears that first bit to 0
	spi_transfer(val);//Writing value to our target register
	cs_high();
}

void mpu_init(void){
	mpu_write_reg(MPU_REG_PWR_MGMT_1, 0x01);//Resetting power management register, waking up chip and configuration auto selecting best avail clock source/PLL
	delay_ms(10);
}

void mpu_read_all(mpu_data_t *out_dest){//out_dest(output destination) is a pointer that holds the mem address of mpu_data_t struct

	uint8_t buffer[14];//Taking a buffer of size 14, each size 8 bit
	cs_low();
	spi_transfer(0x80 | MPU_REG_ACCEL_XOUT_H);
	//Want to read and sent first register address and it will make data ready for first register & will help for cont. reg. data fetching
	for(uint8_t i=0; i<14; i++){
		buffer[i]=spi_transfer(0xFF);
	}
	cs_high();

	out_dest->accel_x = (int16_t)(((uint16_t)buffer[0]<<8) | buffer[1]);//ACCEL_XOUT_H[15:8], ACCEL_XOUT_L[7:0]
	out_dest->accel_y = (int16_t)(((uint16_t)buffer[2]<<8) | buffer[3]);
	out_dest->accel_z = (int16_t)(((uint16_t)buffer[4]<<8) | buffer[5]);
	out_dest->temp_raw= (int16_t)(((uint16_t)buffer[6]<<8) | buffer[7]);
	out_dest->gyro_x = (int16_t)(((uint16_t)buffer[8]<<8) | buffer[9]);
	out_dest->gyro_y = (int16_t)(((uint16_t)buffer[10]<<8) | buffer[11]);
	out_dest->gyro_z = (int16_t)(((uint16_t)buffer[12]<<8) | buffer[13]);
}
