#ifndef LCD_H__
#define LCD_H__

#include "common.h"
#include "timer.h"

void init_LCD(void);
void send_cmd(uint8_t command, uint16_t delay);
void move_cursor(uint8_t x, bool y);
void write_char(char character);
void write_str(const char *string);
void clear_LCD(void);

#endif // LCD_H__
