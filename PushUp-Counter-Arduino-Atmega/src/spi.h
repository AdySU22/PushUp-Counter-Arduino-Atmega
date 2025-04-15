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

#define BUFFER_LENGTH 256

void init_spi(const bool master);
void init_spi(const bool async, const bool master);

void toggle_async(void);
void toggle_mode(const bool set_async);

bool master_transmit_sync(const uint8_t *data, const uint8_t len);
void master_transmit_async(const uint8_t *data, const uint8_t len);
bool slave_receive_sync(uint8_t *data, const uint8_t len);
void slave_receive_async(uint8_t data[256], const uint8_t len);

#endif //SPI_H__