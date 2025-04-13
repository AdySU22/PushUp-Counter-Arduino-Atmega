#include "common.h"
#include "i2c.h"
#include <Arduino.h> 

volatile uint16_t nacks = 0, bytes_sent = 0;

#define DELAY_1US_MANUAL() do { \
	asm volatile ( \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop\n\t" \
			"nop" \
			:: \
			); \
} while (0);

void init_i2c(void) {
	I2C_PORT |= (LCD_I2C_SDA_PIN_MASK | LCD_I2C_SCL_PIN_MASK);
	// TWI Bit Rate Register.
	// Set using TWI bit rate formula:
	// SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR * 4 ^ TWPS))
	// NOTE: TWBR should be 10 or higher for master mode
	// It is 72 for a 16mhz Wiring board with 100kHz TWI
	TWBR = 72;

	// TWI Status Register.
	// Set prescaler to 1
	TWSR &= ~((1 << TWPS0) | (1 << TWPS1));

	// Set idle flag
	i2c_status |= I2C_IDLE;
	sei();
}

void deinit_i2c(void) {
	I2C_PORT &= ~(LCD_I2C_SDA_PIN_MASK | LCD_I2C_SCL_PIN_MASK);
	TWBR = 0;
}

bool stop_i2c(void) {
	// Send stop signal
	// Two Wire (TW) Control Register
	// Enable TW (TWEN), TW Interrupt Clear (TWINT), TW Acknowledge (TWEA), TW Start (TWSTA), and TW Interrupt Enable(TWIE).
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWSTO) | (1 << TWIE);
	
	// Wait until stop condition occurs
	uint8_t counter = 10;
	while (TWCR & (1 << TWSTO)) {
		DELAY_1US_MANUAL();
		if (!(--counter)) {
			deinit_i2c();
			return false;
			break;
		}
	}
	TWCR = (1 << TWINT);
	TWDR = 0;
	return true;
}

bool start_i2c(void) {
	// Send start signal
	// Two Wire (TW) Control Register
	// Enable TW (TWEN), TW Acknowledge (TWEA), TW Start (TWSTA), and TW Interrupt Enable(TWIE).
	i2c_status = I2C_BUSY;
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWSTA) | (1 << TWIE);
	while (i2c_status & I2C_BUSY) {}
	if (i2c_status & I2C_STATUS_BIT_MASK) {
		Serial.print("i2c_status 1: ");
		Serial.println(i2c_status);
		return false;
	}
	
	TWDR = LCD_ADDRESS << 1;
	i2c_status = I2C_BUSY;
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWIE) | (1 << TWEA);
	while (i2c_status & I2C_BUSY) {}
	if (i2c_status & I2C_STATUS_BIT_MASK) {
		Serial.print("i2c_status 2: ");
		Serial.println(i2c_status);
		return false;
	}
	return true;
}

void store_byte(uint8_t b) { 
	uint8_t l = tx_buffer_end & (MAX_BUFFER_LENGTH - 1);
	tx_buffer[l++] = b;
	tx_buffer_end = l;
	i2c_status |= I2C_HAS_PENDING_DATA;
}

bool send_byte(void) {
	Serial.print("Bytes sent: ");
	Serial.println(bytes_sent);
	while (TWCR & (1 << TWWC));
	TWDR = tx_buffer[tx_buffer_start++];
	tx_buffer_start &= MAX_BUFFER_LENGTH - 1;
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWIE) | (1 << TWEA);
	i2c_status |= I2C_BUSY;
	while (i2c_status & I2C_BUSY);
}

bool send_all(void) {
	if (i2c_status & I2C_IDLE) {
		if (!start_i2c()) {
			deinit_i2c();
			return false;
		}
		if (!send_byte()) {
			deinit_i2c();
			return false;
		}
	}
	while (i2c_status & I2C_HAS_PENDING_DATA) {

	}
	return i2c_status == I2C_IDLE;
}

ISR(TWI_vect) {
	switch (I2C_STATUS) {
		case I2C_MT_DATA_ACK: { // data ACKed
			if (tx_buffer_start == tx_buffer_end) {
				i2c_status &= ~(I2C_HAS_PENDING_DATA | I2C_BUSY);
				break;
			} else {
				send_byte();
			}
		}
		case I2C_START: // I2C started
		case I2C_MT_SLA_ACK: { // SLA ACKed (slave address set, can send data)
			i2c_status = I2C_HAS_PENDING_DATA | I2C_IDLE;
		} break;
		case I2C_MT_DATA_NACK: { // data NACKed
			
		} 
		case I2C_MT_SLA_NACK: { // SLA NACKed (slave address not set, can't send data)

		} 
		default: {
			nacks++;
			stop_i2c();
			i2c_status = I2C_STATUS;
		} break;
	}
}

ISR(TIMER3_COMPA_vect) {
	TIFR3 |= (1 << OCF3A);
	TCCR3B &= ~I2C_TIMER_PRESCALER;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
	bytes_sent++;	
}