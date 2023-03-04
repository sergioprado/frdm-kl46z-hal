#ifndef ELW_LED_H_
#define ELW_LED_H_

#include <stdint.h>

/**
 * available leds
 */
#define ELW_LED_GREEN  0
#define ELW_LED_RED    1

/**
 * led status
 */
#define ELW_LED_OFF     0
#define ELW_LED_ON      1
#define ELW_LED_TOGGLE  2

/**
 * Initialize leds
 *
 * @param  none
 *
 * @return none
 */
void elw_led_init(void);

/**
 * Set led status
 *
 * @param  color   Led color (ELW_LED_GREEN, ELW_LED_RED)
 * @param  status  Led status (ELW_LED_OFF, ELW_LED_ON, ELW_LED_TOGGLE)
 *
 * @return none
 */
void elw_led_set(uint8_t color, uint8_t status);

#endif /* ELW_LED_H_ */
