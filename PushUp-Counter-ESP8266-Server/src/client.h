#ifndef CLIENT_H__
#define CLIENT_H__

#include "common.h"

extern int16_t err_number;

void init_server_communication(void);
bool send_data(uint16_t data);

#endif // CLIENT_H__