#include <Arduino.h>
#include <stdfix.h>

#include "timer.h"
#include "reset_switch.h"
#include "lcd.h"
#include "infrared_sensor.h"
#include "touch_sensor.h"
#include "spi.h"

#define RESET_SWITCH_PRESSED true
#define RESET_SWITCH_RELEASED false

// Downward movement
#define MOVEMENT_DOWN true
// Upward movement
#define MOVEMENT_UP false

volatile bool switch_state = RESET_SWITCH_RELEASED;
volatile bool ir_sensor_state = MOVEMENT_UP;
volatile uint16_t push_up_count = 0;
volatile bool touch_sensors_triggered = false;

int16_t main(void) {
	init_timer0();
	init_timer1();
	init_timer3();
	init_reset_switch_pin();
	init_touch_sensor_pins();
	init_infrared_sensor_pin();
	init_spi();
	init_i2c();
	sei();
	init_lcd();
	while (1) {
		write_str("HELLO FROM I2C");
		delay_s(2);
		clear_screen();
		move_cursor(1, 0);
		write_str("HELLO FROM I2C");
		delay_s(2);
		move_cursor(0, 0);
		clear_screen();
	}
	return 0;
}

ISR(RESET_SWITCH_PCINT_VECTOR) {
    if (switch_state == RESET_SWITCH_PRESSED) {
		push_up_count = 0;
	}
	switch_state ^= switch_state;
}

ISR(INFRARED_SENSOR_PCINT_VECTOR) {
	if (ir_sensor_state == MOVEMENT_DOWN) {
		push_up_count++;
	}
	ir_sensor_state ^= ir_sensor_state;
}

#ifdef TOUCH_SENSORS_PCIE_NUMBER
ISR(TOUCH_SENSORS_PCINT_VECTOR) {
	touch_sensors_triggered = (TOUCH_SENSORS_PORT & TOUCH_SENSORS_PIN_MASK) == TOUCH_SENSORS_PIN_MASK;
}
#else
#warning "Don't forget to write an ISR for the touch sensors."
#endif // TOUCH_SENSORS_PCIE_NUMBER