
#ifndef _LCD_H_
#define _LCD_H_

#include "board.h"

#define LCD_MODE_NOSHIFT        0x00
#define LCD_MODE_SHIFT          0x01
#define LCD_MODE_DECR           0x00
#define LCD_MODE_INCR           0x02
#define LCD_MODE_MASK           0x03

#define LCD_SHIFT_CURSOR        0x00
#define LCD_SHIFT_DISPLAY       0x08
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x04
#define LCD_SHIFT_MASK          0x0c

#define LCD_DISPLAY_BLINK_OFF   0x00
#define LCD_DISPLAY_BLINK_ON    0x01
#define LCD_DISPLAY_CURSOR_OFF  0x00
#define LCD_DISPLAY_CURSOR_ON   0x02
#define LCD_DISPLAY_DISPLAY_OFF 0x00
#define LCD_DISPLAY_DISPLAY_ON  0x04
#define LCD_DISPLAY_MASK        0x07

void lcd_init (void);

int  lcd_backlight(int on);
void lcd_display(unsigned char display);
void lcd_mode(unsigned char mode);
void lcd_shift(unsigned char shift);

void lcd_clear(void);
void lcd_home(void);
void lcd_goto_xy (unsigned int x, unsigned int y);

void lcd_put_char(char c);
void lcd_put_string(const char *s);
void lcd_printf(const char * fmt, ...);

/*
 * lcd_new_char 
 *
 * it allows to make up to 8 user defined characters in CGRAM
 *
 * n    : user defined char id (1 <= n <= 8)
 * data : must be a pointer to an 8 char array filled with the char mask (5*8)
 *  -----
 * |   # | 0x02
 * |  #  | 0x04
 * | ### | 0x0E
 * |#   #| 0x11
 * |#####| 0x1F
 * |#    | 0x10
 * | ### | 0x0E
 * |     | 0x00
 *  -----
 * lcd_goto_xy() must be called after using lcd_new_char to switch back to
 * DDRAM output
 *
 * Warning ! n=0 is assigned to ascii 0x00 so that it can't be used in C string
 * As a work around, special characters are used with ascii codes 0x10 to 0x17
 */
void lcd_new_char(unsigned char n, unsigned char *data);

#endif
