#ifndef LCD_H__
#define LCD_H__

#include "common.h"
#include "i2c.h"
#include "timer.h"

#define LCD_ADDRESS_DEFAULT 0x27 // Default
#define LCD_ADDRESS_ALTERNATIVE 0x3F // Alternative
#define LCD_ADDRESS LCD_ADDRESS_DEFAULT 

void init_lcd(void);
void send(uint8_t value, uint16_t delay);
void move_cursor(uint8_t x, bool y);
void write_char(char character);
void write_str(const char *string, uint8_t len);
void clear_screen(void);

#endif // LCD_H__
