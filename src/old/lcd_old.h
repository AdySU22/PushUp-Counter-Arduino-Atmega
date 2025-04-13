#ifndef LCD_H__
#define LCD_H__

#include "common.h"
#include "i2c.h"
#include "timer.h"
#include <avr/interrupt.h>

#define LCD_REGISTER_SELECT_BIT_MASK 0x1
#define LCD_WRITE_READ_BIT_MASK 0x2
#define LCD_ENABLE_BIT_MASK 0x4
#define LCD_BACKLIGHT_BIT_MASK 0x8

uint8_t init_lcd(void);
inline bool send_command(uint8_t value, uint16_t t_us);
bool move_cursor(uint8_t x, bool y);
bool write_char(char character);
bool write_str(const char *str, uint8_t len);
bool clear_screen(void);

#endif // LCD_H__
