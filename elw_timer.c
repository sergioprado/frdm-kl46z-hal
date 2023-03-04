#include "elw_timer.h"
#include "fsl_pit.h"

#define PIT_BASE_ADDR     PIT
#define PIT_CHANNEL       0
#define PIT_SOURCE_CLOCK  CLOCK_GetFreq(kCLOCK_BusClk)

static uint32_t counter = 0;

void elw_timer_init(void)
{
    pit_config_t config;

    PIT_GetDefaultConfig(&config);
    PIT_Init(PIT_BASE_ADDR, &config);
}

void elw_timer_start(uint32_t us)
{
    counter = 0;

    PIT_SetTimerPeriod(PIT_BASE_ADDR, PIT_CHANNEL, USEC_TO_COUNT(us, PIT_SOURCE_CLOCK));

    PIT_EnableInterrupts(PIT_BASE_ADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);
    EnableIRQ(PIT_IRQn);

    PIT_StartTimer(PIT_BASE_ADDR, PIT_CHANNEL);
}

void elw_timer_stop(void)
{
    PIT_StopTimer(PIT_BASE_ADDR, PIT_CHANNEL);

    DisableIRQ(PIT_IRQn);
    PIT_DisableInterrupts(PIT_BASE_ADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);
}

uint32_t elw_timer_counter_get(void)
{
    return counter;
}

void PIT_IRQHandler(void)
{
    PIT_ClearStatusFlags(PIT_BASE_ADDR, PIT_CHANNEL, kPIT_TimerFlag);
    counter++;
}
