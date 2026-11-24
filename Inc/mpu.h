#ifndef MPU_H_
#define MPU_H_

#define MPU_REG_PWR_MGMT_1 0x6B
#define MPU_REG_ACCEL_XOUT_H 0x3B

typedef struct{
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
uint8_t mpu_write_reg(uint8_t reg, uint8_t val);

#endif /* MPU_H_ */
