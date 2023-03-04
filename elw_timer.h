#ifndef ELW_TIMER_H_
#define ELW_TIMER_H_

#include <stdint.h>

/**
 * Initialize timer
 *
 * @param  none
 *
 * @return none
 */
void elw_timer_init(void);

/**
 * Start timer
 *
 * @param  us  timer period in microseconds
 *
 * @return none
 */
void elw_timer_start(uint32_t us);

/**
 * Stop timer
 *
 * @param  none
 *
 * @return none
 */
void elw_timer_stop(void);

/**
 * Get timer counter
 *
 * @param  none
 *
 * @return timer counter value
 */
uint32_t elw_timer_counter_get(void);

#endif /* ELW_TIMER_H_ */
