#include "lcd.h" 

// Function to send a byte via I2C to the LCD backpack
// This encapsulates the interaction with the PCF8574
void send_bits(uint8_t data, uint8_t flags) {

    // Wait if I2C is busy from a previous operation
    while (i2c_is_busy()) {
        // You could add a timeout here
    }
    // Handle previous errors if necessary
    if(i2c_status != I2C_STATE_IDLE) {
        // Log error, try to re-init I2C, etc.
        init_i2c(); // Attempt re-initialization
				delay_ms(10);
				if(i2c_status != I2C_STATE_IDLE) return; // Give up if re-init failed
    }

    // Set the data pins and control pins (RS, RW, EN, Backlight)
    // PCF8574 only needs one byte at a time
    uint8_t packet = data | flags | LCD_BACKLIGHT_BIT_MASK; // Add flags (RS) and keep backlight on

    // Send the data byte (Enable low)
    send_byte(packet, false); // Don't send stop yet
    while (i2c_is_busy()); // Wait for completion
    delay_us_sync(1); // Short delay

    // Pulse Enable High
    packet |= LCD_ENABLE_BIT_MASK;
    send_byte(packet, false); // Don't send stop yet
    while (i2c_is_busy());
    delay_us_sync(1); // Enable pulse width

    // Pulse Enable Low
    packet &= ~LCD_ENABLE_BIT_MASK;
    send_byte(packet, true); // Send stop after this final part
    while (i2c_is_busy()) {}
	delay_us_sync(50); // Delay after command/data write
}

// Send a command byte to the LCD
void send_command(uint8_t cmd) {
    uint8_t high = cmd & 0xF0, low = (cmd << 4) & 0xF0;
    send_bits(high, 0); // RS=0 for command
    send_bits(low, 0); // RS=0 for command
}

// Send a data byte (character) to the LCD
void write_char(uint8_t data) {
    uint8_t high = data & 0xF0, low = (data << 4) & 0xF0;
    send_bits(high, LCD_REGISTER_SELECT_BIT_MASK); // RS=1 for data
    send_bits(low, LCD_REGISTER_SELECT_BIT_MASK); // RS=1 for data
}

// Initialize the LCD in 4-bit mode via I2C
void init_lcd(void) {
    delay_ms(50); // Wait for LCD power up

    // Need to send initialization sequence for 4-bit mode
    send_bits(0x30, 0); // Function set (8-bit mode) - Step 1
    delay_ms(5);
    send_bits(0x30, 0); // Function set (8-bit mode) - Step 2
    delay_us_sync(100);
    send_bits(0x30, 0); // Function set (8-bit mode) - Step 3
    delay_us_sync(100);
    send_bits(0x20, 0); // Function set (4-bit mode)
    delay_us_sync(100);

    send_command(0x28); // Function Set: 4-bit, 2 lines, 5x8 font
    send_command(0x08); // Display OFF, Cursor OFF, Blink OFF
    send_command(0x01); // Clear Display
    delay_ms(2);           // Clear display takes longer
    send_command(0x06); // Entry Mode Set: Increment cursor, no shift
    send_command(0x0F); // Display ON, Cursor OFF, Blink OFF
}

void move_cursor(bool y, uint8_t x) {
    send_command((0x80 | x | y << 6));
}

void write_str(const char* str) {
    while (*str) {
        write_char(*str++);
    }
}

void clear_screen(void) {
	send_command(0x1);
	delay_us_sync(1640);
}
