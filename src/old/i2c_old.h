#ifndef I2C_H__
#define I2C_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

#define LCD_ADDRESS_DEFAULT 0x27 // Default
#define LCD_ADDRESS_ALTERNATIVE 0x3F // Alternative
#define LCD_ADDRESS LCD_ADDRESS_DEFAULT 

#ifndef I2C_STATUS__
#define I2C_STATUS__

// Custom status code
#define I2C_IDLE 0x1
#define I2C_BUSY 0x2
#define I2C_HAS_PENDING_DATA 0x100

#define I2C_STATUS_BIT_MASK 0xF8
#define I2C_STATUS (TWSR & I2C_STATUS_BIT_MASK)

// General status codes

/** @brief 0x08: A START condition has been transmitted */
#define I2C_START                           0x08
/** @brief 0x10: A repeated START condition has been transmitted */
#define I2C_REP_START                       0x10
/** @brief 0x38: Arbitration lost */
#define I2C_ARB_LOST                        0x38

/* Master Transmitter Mode Status Codes */

/** @brief 0x18: SLA+W has been transmitted; ACK has been received */
#define I2C_MT_SLA_ACK                      0x18
/** @brief 0x20: SLA+W has been transmitted; NACK has been received */
#define I2C_MT_SLA_NACK                     0x20
/** @brief 0x28: Data byte has been transmitted; ACK has been received */
#define I2C_MT_DATA_ACK                     0x28
/** @brief 0x30: Data byte has been transmitted; NACK has been received */
#define I2C_MT_DATA_NACK                    0x30
/* Note: 0x38 I2C_ARB_LOST also applies here */

/* Master Receiver Mode Status Codes */

/** @brief 0x40: SLA+R has been transmitted; ACK has been received */
#define I2C_MR_SLA_ACK                      0x40
/** @brief 0x48: SLA+R has been transmitted; NACK has been received */
#define I2C_MR_SLA_NACK                     0x48
/** @brief 0x50: Data byte has been received; ACK has been returned */
#define I2C_MR_DATA_ACK                     0x50
/** @brief 0x58: Data byte has been received; NACK has been returned */
#define I2C_MR_DATA_NACK                    0x58
/* Note: 0x38 I2C_ARB_LOST also applies here */

/* Slave Transmitter Mode Status Codes */

/** @brief 0xA8: Own SLA+R has been received; ACK has been returned */
#define I2C_ST_SLA_ACK                      0xA8
/** @brief 0xB0: Arbitration lost in SLA+R/W as master; own SLA+R received; ACK returned */
#define I2C_ST_ARB_LOST_SLA_ACK             0xB0
/** @brief 0xB8: Data byte in TWDR has been transmitted; ACK has been received */
#define I2C_ST_DATA_ACK                     0xB8
/** @brief 0xC0: Data byte in TWDR has been transmitted; NACK has been received */
#define I2C_ST_DATA_NACK                    0xC0
/** @brief 0xC8: Last data byte in TWDR transmitted (TWEA = 0); ACK has been received */
#define I2C_ST_LAST_DATA_ACK                0xC8

/* Slave Receiver Mode Status Codes */

/** @brief 0x60: Own SLA+W has been received; ACK has been returned */
#define I2C_SR_SLA_ACK                      0x60
/** @brief 0x68: Arbitration lost in SLA+R/W as master; own SLA+W received; ACK returned */
#define I2C_SR_ARB_LOST_SLA_ACK             0x68
/** @brief 0x70: General call address has been received; ACK has been returned */
#define I2C_SR_GCALL_ACK                    0x70
/** @brief 0x78: Arbitration lost in SLA+R/W as master; general call received; ACK returned */
#define I2C_SR_ARB_LOST_GCALL_ACK           0x78
/** @brief 0x80: Previously addressed with own SLA+W; data received; ACK returned */
#define I2C_SR_DATA_ACK                     0x80
/** @brief 0x88: Previously addressed with own SLA+W; data received; NACK returned */
#define I2C_SR_DATA_NACK                    0x88
/** @brief 0x90: Previously addressed with general call; data received; ACK returned */
#define I2C_SR_GCALL_DATA_ACK               0x90
/** @brief 0x98: Previously addressed with general call; data received; NACK returned */
#define I2C_SR_GCALL_DATA_NACK              0x98
/** @brief 0xA0: A STOP condition or repeated START condition received while addressed */
#define I2C_SR_STOP_REP_START               0xA0

/* Miscellaneous Status Codes */

/** @brief 0x00: Bus error due to illegal START or STOP condition */
#define I2C_BUS_ERROR                       0x00
/** @brief 0xF8: No relevant state information available; TWINT = 0 */
#define I2C_NO_INFO                         0xF8

#endif // I2C_STATUS__

void init_i2c(void);
void deinit_i2c(void);
bool start_i2c(void);
bool stop_i2c(void);
void store_byte(uint8_t b);
bool send_all(void);
bool send_byte(void);

// Buffers
#define MAX_BUFFER_LENGTH 256U

// Static variables (automatically zeroed)
static volatile uint16_t i2c_status;
static uint8_t tx_buffer[MAX_BUFFER_LENGTH];
static volatile uint8_t tx_buffer_start, tx_buffer_end;

#endif // I2C_H__ 