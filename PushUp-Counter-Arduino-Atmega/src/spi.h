#ifndef SPI_H__
#define SPI_H__

#include "common.h"
#include "timer.h"
#include <avr/interrupt.h>

// State variables
#define BUFFER_LENGTH 256
static volatile uint8_t *tx_buffer[BUFFER_LENGTH], *rx_buffer[BUFFER_LENGTH];
static volatile uint8_t tx_buffer_start, rx_buffer_start;
static volatile bool is_master;

void init_spi(const bool master = true);

bool master_transmit(uint8_t data);

#endif //SPI_H__