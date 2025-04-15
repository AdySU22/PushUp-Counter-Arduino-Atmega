#ifndef SPI_H__
#define SPI_H__

#include "common.h"
#include "timer.h"
#include <avr/interrupt.h>

#define SPI_ASYNC 0
#define SPI_SYNC 1
#define SPI_MODE_READY 0
#define SPI_MODE_SEND 1
#define SPI_MODE_RECEIVE 2

// State variables
#define BUFFER_LENGTH 256
extern volatile uint8_t tx_buffer[BUFFER_LENGTH], tx_buffer_start, tx_buffer_end;
extern volatile uint8_t rx_buffer[BUFFER_LENGTH], rx_buffer_start, rx_buffer_index, rx_buffer_end;
extern volatile bool is_master;
extern volatile uint8_t spi_mode; 
extern bool async;

void init_spi(const bool master);
void init_spi(const bool async, const bool master);

bool master_transmit_sync(uint8_t data);

#endif //SPI_H__