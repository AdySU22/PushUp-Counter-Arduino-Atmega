#include <avr/io.h>
#define TODO() static_assert(false, "TODO: implementation needed in " __FILE__);

// DDRs
#ifndef DDRS__
#define DDRS__

#define INFRARED_SENSOR_DDR DDRK
#define RESET_SWITCH_DDR DDRJ
#define LEFT_TOUCH_SENSOR_DDR DDRB
#define RIGHT_TOUCH_SENSOR_DDR DDRB

#endif // DDRS__

// PORTs
#ifndef PORTS__
#define PORTS__

#define INFRARED_SENSOR_PORT PORTK
#define RESET_SWITCH_PORT PORTJ
#define LEFT_TOUCH_SENSOR_PORT PORTB
#define RIGHT_TOUCH_SENSOR_PORT PORTB

#endif // PORTS__

// PIN numbers
#ifndef PIN_NUMBERS__
#define PIN_NUMBERS__

/** @brief analog pin 9 (19) / digital pin 63 (D63) */
#define INFRARED_SENSOR_PIN_NUMBER PK1
/** @brief digital pin 15 (D15) */
#define RESET_SWITCH_PIN_NUMBER PJ0
/** @brief digital pin 53 (D5)*/
#define LEFT_TOUCH_SENSOR_PIN_NUMBER PB0
/** @brief digital pin 52 (D52) */
#define RIGHT_TOUCH_SENSOR_PIN_NUMBER PB1

#endif // PIN_NUMBERS__

// PIN masks
#ifndef PIN_MASKS__
#define PIN_MASKS__

#define INFRARED_SENSOR_PIN_MASK (1 << INFRARED_SENSOR_PIN_NUMBER)
#define RESET_SWITCH_PIN_MASK (1 << RESET_SWITCH_PIN_NUMBER)
#define LEFT_TOUCH_SENSOR_PIN_MASK (1 << LEFT_TOUCH_SENSOR_PIN_NUMBER)
#define RIGHT_TOUCH_SENSOR_PIN_MASK (1 << RIGHT_TOUCH_SENSOR_PIN_NUMBER)

#endif // PIN_MASKS__

// PCINT numbers
#ifndef PCINT_NUMBERS__
#define PCINT_NUMBERS__

#define INFRARED_SENSOR_PCINT_NUMBER PCINT17
#define RESET_SWITCH_PCINT_NUMBER PCINT9
#define LEFT_TOUCH_SENSOR_PCINT_NUMBER PCINT0
#define RIGHT_TOUCH_SENSOR_PCINT_NUMBER PCINT1

#endif // PCINT_NUMBERS__

// PCINT masks
#ifndef PCINT_MASKS__
#define PCINT_MASKS__

#define INFRARED_SENSOR_PCINT_MASK (1 << INFRARED_SENSOR_PCINT_NUMBER)
#define RESET_SWITCH_PCINT_MASK (1 << RESET_SWITCH_PCINT_NUMBER)
#define TOUCH_SENSOR_PCINT_MASK ((1 << LEFT_TOUCH_SENSOR_PCINT_NUMBER) | (1 << RIGHT_TOUCH_SENSOR_PCINT_NUMBER))

#endif // PCINT_MASKS__

// PCMSKs
#ifndef PCSMKS__
#define PCSMKS__

#define INFRARED_SENSOR_PCMSK PCMSK2
#define RESET_SWITCH_PCMSK PCMSK1
#define TOUCH_SENSOR_PCMSK PCMSK0

#endif // PCSMKS__

// PCIE Numbers
#ifndef PCIE_NUMBERS__
#define PCIE_NUMBERS__

#define INFRARED_SENSOR_PCIE_NUMBER PCIE0
#define RESET_SWITCH_PCIE_NUMBER PCIE1
#define TOUCH_SENSOR_PCIE_NUMBER PCIE2

#endif // PCIE_NUMBERS__

// PCIE masks
#ifndef PCIE_MASKS__
#define PCIE_MASKS__

#define INFRARED_SENSOR_PCIE_MASK (1 << INFRARED_SENSOR_PCIE_NUMBER)
#define RESET_SWITCH_PCIE_MASK (1 << RESET_SWITCH_PCIE_NUMBER)
#define TOUCH_SENSOR_PCIE_MASK (1 << TOUCH_SENSOR_PCIE_NUMBER)

#endif // PCIE_MASKS__

// PCINT vectors
#ifndef PCINT_VECTORS__
#define PCINT_VECTORS__

#define INFRARED_SENSOR_PCINT_VECTOR PCINT2_vect
#define RESET_SWITCH_PCINT_VECTOR PCINT1_vect
#define TOUCH_SENSOR_PCINT_VECTOR PCINT0_vect

#endif // PCINT_VECTORS__