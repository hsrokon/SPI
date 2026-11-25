#ifndef MPU_H_
#define MPU_H_
#include <stdint.h>

#define MPU_REG_PWR_MGMT_1 0x6B
#define MPU_REG_ACCEL_XOUT_H 0x3B

typedef struct{//typedef = Creates a custom name for an existing data type, so it can be used as a built in data type
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t temp_raw;
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
} mpu_data_t; //mpu_data_t is a data type


void mpu_init(void);
uint8_t mpu_read_reg(uint8_t reg);
void mpu_write_reg(uint8_t reg, uint8_t val);
void mpu_read_all(mpu_data_t *out_dest);

#endif /* MPU_H_ */
