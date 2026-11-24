#ifndef MPU_H_
#define MPU_H_

#define MPU_REG_PWR_MGMT_1 0x6B

void mpu_init(void);
uint8_t mpu_read_reg(uint8_t reg);
uint8_t mpu_write_reg(uint8_t reg, uint8_t val);

#endif /* MPU_H_ */
