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

// PORTs
#ifndef PORTS__
#define PORTS__

#define INFRARED_SENSOR_PORT PORTK
#define RESET_SWITCH_PORT PORTJ
#define LEFT_TOUCH_SENSOR_PORT PORTB
#define RIGHT_TOUCH_SENSOR_PORT PORTB
#define SPI_PORT PORTB
#define I2C_PORT PORTD

#endif // PORTS__

// PIN numbers
#ifndef PIN_NUMBERS__
#define PIN_NUMBERS__

/** @brief analog pin 9 (19) / digital pin 63 (D63) */
#define INFRARED_SENSOR_PIN_NUMBER PK1
/** @brief digital pin 15 (D15) */
#define RESET_SWITCH_PIN_NUMBER PJ0
/** @brief digital pin 12 (D12)*/
#define LEFT_TOUCH_SENSOR_PIN_NUMBER PB6
/** @brief digital pin 11 (D11) */
#define RIGHT_TOUCH_SENSOR_PIN_NUMBER PB5
/** @brief digital pin 53 (D53)*/
#define SPI_SS_PIN_NUMBER PB0
/** @brief digital pin 52 (D52) */
#define SPI_SCK_PIN_NUMBER PB1
/** @brief digital pin 51 (D51) */
#define SPI_MOSI_PIN_NUMBER PB2
/** @brief digital pin 50 (D50)*/
#define SPI_MISO_PIN_NUMBER PB3
/** @brief digital pin 20 (D20)*/
#define LCD_I2C_SCL_PIN_NUMBER PD0
/** @brief digital pin 21 (D21) */
#define LCD_I2C_SDA_PIN_NUMBER PD1
/** @brief digital pin 51 (D51) */
#define SPI_CS_PIN_NUMBER PB4

#endif // PIN_NUMBERS__

// PIN masks
#ifndef PIN_MASKS__
#define PIN_MASKS__

#define INFRARED_SENSOR_PIN_MASK (1 << INFRARED_SENSOR_PIN_NUMBER)
#define RESET_SWITCH_PIN_MASK (1 << RESET_SWITCH_PIN_NUMBER)
#define LEFT_TOUCH_SENSOR_PIN_MASK (1 << LEFT_TOUCH_SENSOR_PIN_NUMBER)
#define RIGHT_TOUCH_SENSOR_PIN_MASK (1 << RIGHT_TOUCH_SENSOR_PIN_NUMBER)
/** @brief Slave Sleect */
#define SPI_SS_PIN_MASK (1 << SPI_SS_PIN_NUMBER)
#define SPI_SCK_PIN_MASK (1 << SPI_SCK_PIN_NUMBER)
#define SPI_MOSI_PIN_MASK (1 << SPI_MOSI_PIN_NUMBER)
#define SPI_MISO_PIN_MASK (1 << SPI_MISO_PIN_NUMBER)
/** @brief Chip Select */
#define SPI_CS_PIN_MASK (1 << SPI_DATA_PIN_NUMBER)
#define LCD_I2C_SCL_PIN_MASK (1 << LCD_I2C_SCL_PIN_NUMBER)
#define LCD_I2C_SDA_PIN_MASK (1 << LCD_I2C_SDA_PIN_NUMBER)

#endif // PIN_MASKS__

// PCINT numbers
#ifndef PCINT_NUMBERS__
#define PCINT_NUMBERS__

#define INFRARED_SENSOR_PCINT_NUMBER PCINT17
#define RESET_SWITCH_PCINT_NUMBER PCINT9
#define LEFT_TOUCH_SENSOR_PCINT_NUMBER PCINT6
#define RIGHT_TOUCH_SENSOR_PCINT_NUMBER PCINT5

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

#endif // COMMON_H__