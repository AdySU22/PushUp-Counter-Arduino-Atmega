#include "infrared_sensor.h"

void init_infrared_sensor_pin(void) {
	INFRARED_SENSOR_DDR &= ~INFRARED_SENSOR_PIN_MASK;
	INFRARED_SENSOR_PORT |= INFRARED_SENSOR_PIN_MASK;
}