#include "lcd.h"
#include <Wire.h>

void init_lcd(void) {
	delay_ms(50);
	I2C_PORT |= (LCD_I2C_SDA_PIN_MASK | LCD_I2C_SCL_PIN_MASK);
	init_i2c();
}

void write_char(char character) {
	write_byte(character);
	delay_us(46);
}

void write_str(const char *string, uint8_t len) {
	auto l = tx_buffer_len;
	if (l + len < MAX_BUFFER_LENGTH) {
		while (*string) {
			tx_buffer[l++] = *string++;
		}
		tx_buffer_len = l;
	}
	start_i2c();
}

void send(uint8_t value, uint16_t t_us) {
	start_i2c();
	write_byte(value & 0xF);
	write_byte(value >> 4);
	stop_i2c();
	delay_us(t_us);
}

void clear_LCD(void) {

}

void move_cursor(uint8_t x, bool y) {

}

void clear_screen(void) {
	write_byte(0x1);
}