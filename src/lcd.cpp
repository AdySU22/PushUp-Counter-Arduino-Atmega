#include "lcd.h"
#include <Wire.h>

#define MAX_BUFFER_LENGTH 32

static uint8_t tx_buffer[MAX_BUFFER_LENGTH] = { };
static volatile uint8_t tx_buffer_idx = 0, tx_buffer_len = 0;  
static uint8_t rx_buffer[MAX_BUFFER_LENGTH] = { };
static volatile uint8_t rx_buffer_idx = 0, rx_buffer_len = 0;  

void init_LCD(void) {
	I2C_PORT |= (LCD_I2C_SDA_PIN_MASK | LCD_I2C_SCL_PIN_MASK);

	// Two Wire (TW) Control Register
	// Enable TW (TWEN), TWI interrupt (TWIE), and TW Acknowledge (TWEA) 
	TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
	
	// TWI Bit Rate Register.
	// Set using TWI bit rate formula:
	// SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR * 4 ^ TWPS))
	// NOTE: TWBR should be 10 or higher for master mode
	// It is 72 for a 16mhz Wiring board with 100kHz TWI
	TWBR = 72;

	// TWI Status Register.
	// Set prescaler to 64
	TWSR &= ~((1 << TWPS0) | (1 << TWPS1));
}

void write_char(char character) {
	TWDR = character;
	TWCR |= (1 << TWEN) | (1 << TWINT);
}

void write_str(const char *string) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	
	while (*string) write_char(*string++);
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

}

void send_cmd(uint8_t command, uint16_t t_us) {

	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);


	TWDR = command;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

	delay_us(t_us);
}

void move_cursor(uint8_t x, bool y) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	TWDR = 0x80 | (y * 0x40) | x;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void clear_LCD(void) {
	TODO();
}

ISR(TWI_vect) {
	
}