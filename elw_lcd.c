#include "elw_lcd.h"
#include "LCDDriver.h"
#include "pin_mux.h"

void elw_lcd_init(void)
{
    BOARD_InitSegment_LCD();
    vfnLCD_Init();
}

void elw_lcd_write_char(char ch)
{
    vfnLCD_Write_Char((unsigned char)ch);
}

void elw_lcd_write_string(char *str)
{
    vfnLCD_Write_Msg((unsigned char *)str);
}

void elw_lcd_home(void)
{
    vfnLCD_Home();
}

void elw_lcd_clear(void)
{
    vfnLCD_All_Segments_OFF();
    elw_lcd_home();
}
