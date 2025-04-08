#ifndef TIMER_H__
#define TIMER_H__

#include "common.h"

void init_timer0(void);
void init_timer1(void);
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);

#endif // TIMER_H__