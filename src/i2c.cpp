#include "common.h"
#include "i2c.h"

inline void init_i2c(void) {
	// TWI Bit Rate Register.
	// Set using TWI bit rate formula:
	// SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR * 4 ^ TWPS))
	// NOTE: TWBR should be 10 or higher for master mode
	// It is 72 for a 16mhz Wiring board with 100kHz TWI
	TWBR = 72;

	// TWI Status Register.
	// Set prescaler to 1
	TWSR &= ~((1 << TWPS0) | (1 << TWPS1));
}

inline void stop_i2c(void) {
	// Send stop signal
	// Two Wire (TW) Control Register
	// Enable TW (TWEN), TW Interrupt Clear (TWINT), TW Acknowledge (TWEA), TW Start (TWSTA), and TW Interrupt Enable(TWIE).
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWSTO) | (1 << TWIE);

	// Wait until stop condition occurs
	while (TWCR & (1 << TWSTO));
}

inline void start_i2c(void) {
	// Send start signal
	// Two Wire (TW) Control Register
	// Enable TW (TWEN), TW Acknowledge (TWEA), TW Start (TWSTA), and TW Interrupt Enable(TWIE).
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWSTA) | (1 << TWIE);
}

bool write_byte(uint8_t b) { 
	TWDR = b;
	TWCR = (1 << TWINT) | (1 << TWEN);
	// while (TWCR & (1 << TWINT));
	// buf[idx++] = b
}

ISR(TWI_vect) {
	switch(I2C_STATUS) {
		case I2C_MT_SLA_NACK:
			
			break;
	}
}