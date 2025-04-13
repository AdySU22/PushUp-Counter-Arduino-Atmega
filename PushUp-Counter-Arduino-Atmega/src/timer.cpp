#include "timer.h"

void init_timer0(void) {
	TCCR0B = 0;
	TCCR0A = 1 << WGM01;
}

void init_timer1(void) {
	TCCR1B = 1 << WGM12;
	TCCR1A = 0;
}

void init_timer3(void) {
	// enable CTC mode
	TCCR3A = 0;
	TCCR3B = (1 << WGM32);
	// enable output compare A interrupt
	TIMSK3 = (1 << OCIE3A);
}