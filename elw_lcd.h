#ifndef ELW_LCD_H_
#define ELW_LCD_H_

/**
 * Initialize the LCD
 *
 * @param  none
 *
 * @return none
 */
void elw_lcd_init(void);

/**
 * Write one character to the LCD current position
 *
 * @param  ch  character to be written
 *
 * @return none
 */
void elw_lcd_write_char(char ch);

/**
 * Write a string to the LCD.
 * If the string size is greater than 4, the message is truncated.
 * If the string size is less than 4, the display is filled with blanks.
 *
 * @param  str  string to be written
 *
 * @return none
 */
void elw_lcd_write_string(char *str);

/**
 * Clear the LCD
 *
 * @param  none
 *
 * @return none
 */
void elw_lcd_clear(void);

/**
 * Go to LCD initial position
 *
 * @param  none
 *
 * @return none
 */
void elw_lcd_home(void);

#endif /* ELW_LCD_H_ */
