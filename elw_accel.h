#ifndef ELW_ACCEL_H_
#define ELW_ACCEL_H_

#include <stdint.h>

/**
 * Initialize accelerometer
 *
 * @param  none
 *
 * @return none
 */
void elw_accel_init(void);

/**
 * Read accelerometer
 *
 * @param  x  X axis
 * @param  y  Y axis
 * @param  z  Z axis
 *
 * @return none
 */
void elw_accel_read(int32_t *x, int32_t *y, int32_t *z);

#endif /* ELW_ACCEL_H_ */
