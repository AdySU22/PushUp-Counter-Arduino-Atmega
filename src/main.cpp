#include <Arduino.h>
#include "reset_switch.h"
#include "lcd.h"
#include "infrared_sensor.h"
#include "touch_sensor.h"
#include "timer.h"
#include "client.h"

#define RESET_SWITCH_PRESSED true
#define RESET_SWITCH_RELEASED false

// Downward movement
#define MOVEMENT_DOWN true
// Upward movement
#define MOVEMENT_UP false

volatile bool switch_state = RESET_SWITCH_RELEASED;
volatile bool ir_sensor_state = MOVEMENT_UP;
volatile uint16_t push_up_count = 0;

int16_t main(void) {
	init_timer0();
	init_timer1();
	init_reset_switch_pin();
	init_touch_sensor_pins();
	init_infrared_sensor_pin();
	init_server_communication();
	init_lcd();
	sei();
	while (1) {
		
	}
	return 0;
}

ISR(RESET_SWITCH_PCINT_VECTOR) {
    if (RESET_SWITCH_PRESSED) {
		push_up_count = 0;
	}
	switch_state = !switch_state;
}

ISR(INFRARED_SENSOR_PCINT_VECTOR) {
	if (MOVEMENT_DOWN) {
		push_up_count++;
	}
	ir_sensor_state = !ir_sensor_state;
}