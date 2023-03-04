#ifndef ACCEL_MMA8451_H_
#define ACCEL_MMA8451_H_

#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;

void hal_dev_mma8451_init(void);
uint8 hal_dev_mma8451_read_reg(uint8 addr);
void hal_dev_mma8451_write_reg(uint8 addr, uint8 data);
uint16 hal_dev_mma8451_test_reg_rw(void);
void hal_dev_mma8451_test_function(void);
extern void accel_init(void);
void accel_read(void);
void accel_read_xyz(int *x, int *y, int *z);
void accel_test(void);
int iAcclReadX(void);
int iAcclReadY(void);
int iAcclReadZ(void);

#endif /* ACCEL_MMA8451_H_ */
