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

uint8_t mpu_write_reg(uint8_t reg, uint8_t val){
	cs_low();
	spi_transfer(0x7F|reg);// 0x7F=0111 1111, 7th bit =0=write
	spi_transfer(val);//Writing value to our target register
	cs_high();
}

void mpu_init(void){
	mpu_write_reg(MPU_REG_PWR_MGMT_1, 0x01);//Resetting power management register, waking up chip and configuration auto selecting best avail clock source/PLL
	delay_ms(10);
}

void mpu_read_all(mpu_data_t *out_dest){

	uint8_t buffer[14];
	spi_transfer(0x80 | MPU_REG_ACCEL_XOUT_H);
	for(uint8_t i; i<14; i++){

	}


}
