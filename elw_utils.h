#ifndef ELW_UTILS_H_
#define ELW_UTILS_H_

#include <stdint.h>

/**
 * Delay in milliseconds. This function doesn't use a
 * timer. It just runs NOP instructions!
 *
 * @param  ms  delay time in milliseconds
 *
 * @return none
 */
void elw_delay(uint32_t ms);

#endif /* ELW_UTILS_H_ */
