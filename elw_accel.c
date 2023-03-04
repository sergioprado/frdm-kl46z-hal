#include "elw_accel.h"
#include "pin_mux.h"
#include "mma8451.h"

void elw_accel_init(void)
{
    BOARD_InitACCEL();
    accel_init();
}

void elw_accel_read(int32_t *x, int32_t *y, int32_t *z)
{
    accel_read_xyz(x, y, z);
}
