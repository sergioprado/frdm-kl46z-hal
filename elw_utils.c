#include "elw_utils.h"

void elw_delay(uint32_t ms)
{
    unsigned int i;

    while(--ms) {
        for (i = 0; i < 1700; i++)
            __asm__("nop");
    }
}
