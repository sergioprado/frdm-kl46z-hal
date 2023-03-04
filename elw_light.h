#ifndef ELW_LIGHT_H_
#define ELW_LIGHT_H_

#include <stdint.h>

/**
 * Initialize light sensor ADC
 *
 * @param  none
 *
 * @return none
 */
void elw_light_init(void);

/**
 * Read light sensor ADC channel
 *
 * @param  none
 *
 * @return light sensor value (0 ~ 4096)
 */
uint32_t elw_light_read(void);

#endif /* ELW_LIGHT_H_ */
