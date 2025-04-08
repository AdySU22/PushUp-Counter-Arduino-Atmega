#include "timer.h"

void init_timer0(void) {
	TCCR0B = 0;
	TCCR0A = 1 << WGM01;
}

void init_timer1(void) {
	TCCR1B = 1 << WGM12;
	TCCR1A = 0;
}

void delay_us(uint16_t us) {
	TCCR1B |= 1 << CS11;
	OCR1A = us << 1;
	TCNT1 = 0;
	while (!(TIFR1 & (1 << OCF1A)));
	TIFR1 |= 1 << OCF1A;
	TCCR1B = 1 << WGM12;
}

void delay_ms(uint16_t ms) {
	// Prescaler 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// Set delay
	OCR1A = ms << 4;
	TCNT1 = 0;
	while (!(TIFR1 & (1 << OCF1A)));
	TIFR1 |= 1 << OCF1A;
	TCCR1B = 1 << WGM12;
}

void delay_s(uint16_t s) {
	TCCR1B |= 1 << CS12;
	OCR1A = 62500;
	TCNT1 = 0;
	while (s > 0) {
		while (!(TIFR1 & (1 << OCF1A)));
		s--;
		TIFR1 |= 1 << OCF1A;
	}
	TCCR1B = 1 << WGM12;
}
