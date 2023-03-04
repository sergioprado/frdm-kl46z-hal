#ifndef ELW_BTN_H_
#define ELW_BTN_H_

#include <stdint.h>

/**
 * button ID
 */
#define ELW_BTN_SW1  0
#define ELW_BTN_SW3  1

/**
 * button status
 */
#define ELW_BTN_RELEASED  0
#define ELW_BTN_PRESSED   1

/**
 * ISR callback
 *
 * @param  btn  Button ID (ELW_BTN_SW1, ELW_BTN_SW3)
 *
 * @return none
 */
typedef void (*elw_btn_isr_callback_t)(uint8_t btn);

/**
 * Initialize buttons
 *
 * @param  none
 *
 * @return none
 */
void elw_btn_init(void);

/**
 * Get SW1 button status
 *
 * @param  none
 *
 * @return ELW_BTN_PRESSED or ELW_BTN_RELEASED
 */
uint8_t elw_btn_status_sw1(void);

/**
 * Get SW3 button status
 *
 * @param  none
 *
 * @return ELW_BTN_PRESSED or ELW_BTN_RELEASED
 */
uint8_t elw_btn_status_sw3(void);

/**
 * Enable buttons interrupt
 *
 * @param  callback  Function to be called to handle the interrupt
 *
 * @return none
 */
void elw_btn_irq_enable(elw_btn_isr_callback_t callback);

/**
 * Disable buttons interrupt
 *
 * @param  none
 *
 * @return none
 */
void elw_btn_irq_disable(void);

#endif /* ELW_BTN_H_ */
