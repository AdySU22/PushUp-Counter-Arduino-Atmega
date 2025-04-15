#include "spi.h"

// State variables
static volatile uint8_t tx_buffer[BUFFER_LENGTH], tx_buffer_start, tx_buffer_end;
static volatile uint8_t *rx_buffer, rx_buffer_start, rx_buffer_end;
static volatile bool is_master;
static volatile uint8_t spi_mode; 
static bool async;

void init_spi(const bool master) {
	init_spi(false, master);
}

void init_spi(const bool async_mode, const bool master) {
	is_master = master;
	async = async_mode;
	if (master) {
		// Set MOSI pin as output
		SPI_DDR |= (SPI_MOSI_PIN_MASK) | (SPI_SCK_PIN_MASK) | (SPI_CS_PIN_MASK);
		// Enable SPI, Master, set clock rate fck/16
		SPCR |= (1 << SPIE) | (async << SPE) | (1 << MSTR) | (1 << SPR0);
	} else {
		// Set MISO pin as output
		SPI_DDR |= (SPI_MISO_PIN_MASK);
		// Enable SPI, Slave
		SPCR |= (1 << SPIE) | (async << SPE);
	}
}

void toggle_async(void) {
	async = !async;
	SPCR ^= (1 << SPIE);
}

void toggle_mode(const bool set_async = false) {
	is_master ^= is_master;
	SPI_DDR ^= SPI_CS_PIN_MASK;
	SPI_PORT |= SPI_CS_PIN_MASK;
	async = set_async;
	SPCR = ((SPCR ^ (1 << MSTR)) & ~(1 << SPIE)) | (async << SPIE);
}

bool master_transmit_sync(const uint8_t *data, const uint8_t len) {
	for (uint8_t i = 0; i < len; i++) {
		SPDR = data[i];
		// Poll for every byte
		while (!(SPSR & (1 << SPIF))) {}
	}
	return true;
}

void master_transmit_async(const uint8_t *data, const uint8_t len) {
	for (uint8_t i = 0; i < len; ++i) {
		tx_buffer[tx_buffer_end++] = data[i];
	}
	spi_mode = SPI_MODE_SEND;
	SPI_PORT &= ~SPI_CS_PIN_MASK;
	TWDR = tx_buffer[tx_buffer_start++];
}

bool slave_receive_sync(uint8_t *data, const uint8_t len) {
	for (uint8_t i = 0; i < len; i++) {
		// Wait for byte transfer
		while(!(SPSR & (1 << SPIF))) {
			// delay_ms(100);
		};
		data[i] = SPDR;
	}
	return true;
}

void slave_receive_async(uint8_t data[256], const uint8_t len) {
	rx_buffer = data;
	rx_buffer_end = len;
	rx_buffer_start = 0;
	spi_mode = SPI_MODE_RECEIVE;
	// TODO: signal wifi module to reply
}

// SPI Transfer complete interrupt / handler
ISR(SPI_STC_vect) {
	switch (spi_mode) {
		case SPI_MODE_SEND: {
			if (tx_buffer_start != tx_buffer_end) {
				TWDR = tx_buffer[tx_buffer_start++];
			} else {
				SPI_PORT |= SPI_CS_PIN_MASK;
				spi_mode = SPI_MODE_READY;
			}
		} break;
		case SPI_MODE_RECEIVE: {
			if (rx_buffer_start != rx_buffer_end) {
				rx_buffer[rx_buffer_start++] = TWDR;
			} else {
				
				spi_mode = SPI_MODE_READY;
			}
		} break;
		case SPI_MODE_READY: {

		} break;
		default:
			DEBUG_PRINT("Got error ");
			DEBUG_PRINTLN(spi_mode);
			break;
	}
}