#include "spi.h"

void init_spi(const bool master = true) {
	is_master = master;
	if (master) {
		// Set MOSI pin as output
		SPI_DDR = (SPI_MOSI_PIN_MASK) | (SPI_SCK_PIN_MASK);
		// Enable SPI, Master, set clock rate fck/16
		SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	} else {
		// Set MISO pin as output
		SPI_DDR = (SPI_MISO_PIN_MASK);
		// Enable SPI, Master, set clock rate fck/16
		SPCR = (1 << SPIE) | (1 << SPE);
	}
}

void toggle_mode(void) {
	is_master ^= is_master;
	// Either reset SS pin as master
	// or drive SS pin low to activate slave SPI
	SPI_PORT &= ~SPI_SS_PIN_MASK;
	SPCR ^= (1 << MSTR);
}

bool master_transmit(uint8_t *data, uint8_t len) {
	for (uint8_t i = 0; i < len; i++) {
		SPDR = data[i];
		while (!(SPSR & (1 << SPIF))) {}
	}
	return true;
}

bool slave_receive(uint8_t len) {
	for (uint8_t i = 0; i < len; i++) {
		while(!(SPSR & (1 << SPIF))) {};
		rx_buffer[i] = SPDR;
	}
	return true;
}

// SPI Transfer complete interrupt / handler
ISR(SPI_STC_vect) {
	
}