#ifndef ELW_RTC_H_
#define ELW_RTC_H_

#include <stdint.h>

/**
 * Date and time structure
 */
struct elw_rtc_datetime
{
    uint16_t year;   /* 1970 to 2099 */
    uint8_t month;   /* 1 to 12 */
    uint8_t day;     /* 1 to 31 */
    uint8_t hour;    /* 0 to 23 */
    uint8_t minute;  /* 0 to 59 */
    uint8_t second;  /* 0 to 59 */
};

/**
 * Initialize RTC
 *
 * @param  none
 *
 * @return none
 */
void elw_rtc_init(void);

/**
 * Set RTC date and time.
 *
 * @param  datetime  date and time to be set
 *
 * @return none
 */
void elw_rtc_datetime_set(struct elw_rtc_datetime datetime);

/**
 * Get RTC date and time.
 *
 * @param  datetime  structure to store date and time
 *
 * @return none
 */
void elw_rtc_datetime_get(struct elw_rtc_datetime *datetime);

#endif /* ELW_RTC_H_ */
