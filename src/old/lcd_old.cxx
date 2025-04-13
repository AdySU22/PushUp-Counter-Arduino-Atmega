#include "lcd.h"
#include <Arduino.h>
uint8_t init_lcd(void) {
	init_i2c();
	delay_ms(50);
	store_byte(char(0x8)); 
	if (!send_all()) {
		return -1;
	}

	if (!send_command(char(0x3 << 4), 4100)) {
		return 2;
	}
	
	if (!send_command(char(0x3 << 4), 100)) {
		return 3;
	}

	if (!send_command(char(0x3 << 4), 100)) {
		return 4;
	}

	if (!send_command(char(0x2 << 4), 100)) {
		return 5;
	}

	// Function set
	if (!send_command(char(0x2B), 100)) {
		return 6;
	}

	// Display off
	if (!send_command(char(0x8), 100)) {
		return 7;
	}

	if (!clear_screen()) {
		return 8;
	}

	// Entry set
	if (!send_command(char(0x6), 90)) {
		return 9;
	}

	// Display on
	if (!send_command(char(0xF), 90)) {
		return 10;
	}

	if (!clear_screen()) {
		return 11;
	}

	return 0;
}

bool write_char(char character) {
	uint8_t low = character & 0xF, high = character & 0xF0;
	store_byte(high);
	store_byte(high | LCD_BACKLIGHT_BIT_MASK | LCD_ENABLE_BIT_MASK | LCD_REGISTER_SELECT_BIT_MASK);
	store_byte((high | LCD_BACKLIGHT_BIT_MASK | LCD_REGISTER_SELECT_BIT_MASK) & ~(LCD_ENABLE_BIT_MASK));
	store_byte(low << 4);
	store_byte((low << 4) | LCD_BACKLIGHT_BIT_MASK | LCD_ENABLE_BIT_MASK | LCD_REGISTER_SELECT_BIT_MASK);
	store_byte(((low << 4) | LCD_BACKLIGHT_BIT_MASK | LCD_REGISTER_SELECT_BIT_MASK) & ~(LCD_ENABLE_BIT_MASK));
	if (!send_all()) {
		return false;
	}
	delay_us_sync(46);
	return true;
}

bool write_str(const char *str, uint8_t len) {
	while (*str) {
		if (!write_char(*str)) return false;
		str++;
	}
	return true;
}

inline bool send_command(uint8_t command, uint16_t t_us) {
	uint8_t low = command & 0xF, high = command & 0xF0;
	store_byte((high));
	store_byte((high) | LCD_BACKLIGHT_BIT_MASK | LCD_ENABLE_BIT_MASK);
	store_byte(((high) | LCD_BACKLIGHT_BIT_MASK) & ~(LCD_ENABLE_BIT_MASK));
	store_byte(command << 4);
	store_byte((command << 4) | LCD_BACKLIGHT_BIT_MASK | LCD_ENABLE_BIT_MASK);
	store_byte(((command << 4) | LCD_BACKLIGHT_BIT_MASK) & ~(LCD_ENABLE_BIT_MASK));
	if (!send_all()) {
		return false;
	}
	delay_us_sync(t_us);
	return true;
}

bool move_cursor(uint8_t x, bool y) {
	return send_command(0x80 | (0x80 >> y) | x, 40);
}

bool clear_screen(void) {
	return send_command(0x1, 1640);
}
