#include "elw_led.h"
#include "pin_mux.h"
#include "board.h"

static void elw_led_on(uint8_t led)
{
    switch (led) {

    case ELW_LED_GREEN:
        LED_GREEN_ON();
        break;

    case ELW_LED_RED:
        LED_RED_ON();
        break;
    }
}

static void elw_led_off(uint8_t led)
{
    switch (led) {

    case ELW_LED_GREEN:
        LED_GREEN_OFF();
        break;

    case ELW_LED_RED:
        LED_RED_OFF();
        break;
    }
}

static void elw_led_toggle(uint8_t led)
{
    switch (led) {

    case ELW_LED_GREEN:
        LED_GREEN_TOGGLE();
        break;

    case ELW_LED_RED:
        LED_RED_TOGGLE();
        break;
    }
}

void elw_led_set(uint8_t color, uint8_t status)
{
    switch (status) {

    case ELW_LED_OFF:
        elw_led_off(color);
        break;

    case ELW_LED_ON:
        elw_led_on(color);
        break;

    case ELW_LED_TOGGLE:
        elw_led_toggle(color);
        break;
    }
}

void elw_led_init(void)
{
    BOARD_InitLEDs();

    elw_led_set(ELW_LED_RED, ELW_LED_OFF);
    elw_led_set(ELW_LED_GREEN, ELW_LED_OFF);
}
