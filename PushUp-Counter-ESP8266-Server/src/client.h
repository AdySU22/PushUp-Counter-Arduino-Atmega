#ifndef CLIENT_H__
#define CLIENT_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <lwip/sockets.h>
#include <lwip/api.h>

extern int16_t err_number;

void init_server_communication(void);
bool send_data(uint16_t data);

#endif // CLIENT_H__