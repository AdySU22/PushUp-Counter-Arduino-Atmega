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

void init_lcd(void);
void send_bits(uint8_t data, uint8_t flags);
void move_cursor(bool y, uint8_t x);
void write_char(uint8_t character);
void send_command(uint8_t command);
void write_str(const char* str);
void clear_screen(void);

#endif
