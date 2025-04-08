#include <Arduino.h>
#include <avr/io.h>
#include "led.h"
#include "reset_switch.h"
// #include "timer.h"
#include "server.h"

#include "lcd.h"

typedef enum {
    UNPRESSED,
    PRESSED,
    HELD,
    RELEASED
} switch_state_t;
volatile switch_state_t state = switch_state_t::UNPRESSED;

int16_t main(void) {
    
    while (1) {

    }
    return 0;
}

ISR(PCINT0_vect) {
    switch (state) {
        case switch_state_t::UNPRESSED:
            state = switch_state_t::PRESSED;
            break;
        case switch_state_t::HELD:
            state = switch_state_t::RELEASED;
            break;
        default:
            break;
    }
}