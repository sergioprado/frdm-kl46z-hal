#include "elw_hal.h"
#include "MKL46Z4.h"

static int hal_initialized = 0;

static void elw_irq_prio_init(void)
{
    for (int i = 0; i < 32; i++)
        NVIC_SetPriority(i, 3);
}

void elw_init_hal(void)
{
    if (!hal_initialized) {
        elw_irq_prio_init();
        elw_timer_init();
        elw_led_init();
        elw_btn_init();
        elw_lcd_init();
        elw_uart_init();
        elw_accel_init();
        elw_rtc_init();
        elw_light_init();
        hal_initialized = 1;
    }
}
