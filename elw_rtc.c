#include "elw_rtc.h"
#include "fsl_rtc.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "board.h"

#define RTC_BASE_ADDR  RTC
#define RTC_CLOCK      1000

#define SECONDS_IN_A_DAY     (86400U)
#define SECONDS_IN_A_HOUR    (3600U)
#define SECONDS_IN_A_MIN     (60U)
#define MINS_IN_A_HOUR       (60U)
#define HOURS_IN_A_DAY       (24U)
#define DAYS_IN_A_YEAR       (365U)
#define DAYS_IN_A_LEAP_YEAR  (366U)
#define YEAR_RANGE_START     (1970U)
#define YEAR_RANGE_END       (2099U)

/* Number of days from begin of the non Leap-year*/
static const uint16_t MONTH_DAYS[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U,
    212U, 243U, 273U, 304U, 334U};

static void elw_seconds_to_datetime(uint32_t seconds, struct elw_rtc_datetime *datetime)
{
    assert(datetime);

    uint32_t x;
    uint32_t secondsRemaining, days;
    uint16_t daysInYear;
    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Start with the seconds value that is passed in to be converted to date time format */
    secondsRemaining = seconds;

    /* Calcuate the number of days, we add 1 for the current day which is represented in the
     * hours and seconds field
     */
    days = secondsRemaining / SECONDS_IN_A_DAY + 1;

    /* Update seconds left*/
    secondsRemaining = secondsRemaining % SECONDS_IN_A_DAY;

    /* Calculate the datetime hour, minute and second fields */
    datetime->hour = secondsRemaining / SECONDS_IN_A_HOUR;
    secondsRemaining = secondsRemaining % SECONDS_IN_A_HOUR;
    datetime->minute = secondsRemaining / 60U;
    datetime->second = secondsRemaining % SECONDS_IN_A_MIN;

    /* Calculate year */
    daysInYear = DAYS_IN_A_YEAR;
    datetime->year = YEAR_RANGE_START;
    while (days > daysInYear)
    {
        /* Decrease day count by a year and increment year by 1 */
        days -= daysInYear;
        datetime->year++;

        /* Adjust the number of days for a leap year */
        if (datetime->year & 3U)
        {
            daysInYear = DAYS_IN_A_YEAR;
        }
        else
        {
            daysInYear = DAYS_IN_A_YEAR + 1;
        }
    }

    /* Adjust the days in February for a leap year */
    if (!(datetime->year & 3U))
    {
        daysPerMonth[2] = 29U;
    }

    for (x = 1U; x <= 12U; x++)
    {
        if (days <= daysPerMonth[x])
        {
            datetime->month = x;
            break;
        }
        else
        {
            days -= daysPerMonth[x];
        }
    }

    datetime->day = days;
}

static void elw_datetime_to_secs(const struct elw_rtc_datetime *datetime, uint32_t *seconds)
{
    /* Compute number of days from 1970 till given year*/
    *seconds = (datetime->year - 1970U) * DAYS_IN_A_YEAR;
    /* Add leap year days */
    *seconds += ((datetime->year / 4) - (1970U / 4));
    /* Add number of days till given month*/
    *seconds += MONTH_DAYS[datetime->month];
    /* Add days in given month*/
    *seconds += datetime->day;
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if ((!(datetime->year & 3U)) && (datetime->month <= 2U))
    {
        (*seconds)--;
    }

    *seconds = ((*seconds) * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
               (datetime->minute * SECONDS_IN_A_MIN) + datetime->second;
}

void elw_rtc_init(void)
{
    rtc_config_t config;

    /* the board has a 8MHz crystal connected on system oscillator, but
     * the 8MHz OSC32KCLK can't be used for RTC, so we have to select
     * the internal 1kHz LPO as the clock source of RTC */
    CLOCK_SetEr32kClock(3);

    RTC_GetDefaultConfig(&config);
    RTC_Init(RTC_BASE_ADDR, &config);
}

void elw_rtc_datetime_get(struct elw_rtc_datetime *datetime)
{
    uint32_t seconds = 0;

    /* Since the input clock to the RTC counter is not 32KHz, the seconds register will not
       increment every second, therefore the seconds register value needs to be adjusted.
       to get actual seconds. We then add the prescaler register value to the seconds */
    seconds = ((RTC_BASE_ADDR->TSR) * (32768U / RTC_CLOCK)) +
              (RTC_BASE_ADDR->TPR / RTC_CLOCK);

    elw_seconds_to_datetime(seconds, datetime);
}

void elw_rtc_datetime_set(struct elw_rtc_datetime datetime)
{
    uint32_t seconds = 0;

    /* adjust day */
    datetime.day--;

    elw_datetime_to_secs((const struct elw_rtc_datetime *)&datetime, &seconds);

    /* As the seconds register will not increment every second, we need to adjust the value
       programmed to the seconds register */
    seconds = seconds / (32768U / RTC_CLOCK);

    RTC_StopTimer(RTC_BASE_ADDR);
    RTC_BASE_ADDR->TSR = seconds;
    RTC_StartTimer(RTC_BASE_ADDR);
}
