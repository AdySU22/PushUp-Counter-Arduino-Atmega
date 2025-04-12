#ifndef COMMON_H__
#define COMMON_H__
#include <avr/io.h>
#define TODO() static_assert(false, "TODO: implementation needed in " __FILE__);

// DDRs
#ifndef DDRS__
#define DDRS__

#define INFRARED_SENSOR_DDR DDRK
#define RESET_SWITCH_DDR DDRJ
#define LEFT_TOUCH_SENSOR_DDR DDRB
#define RIGHT_TOUCH_SENSOR_DDR DDRB
#define SPI_DDR DDRB
#define I2C_DDR DDRD

#endif // DDRS__