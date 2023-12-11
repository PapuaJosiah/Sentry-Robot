#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"


#define X_Pin 26
#define Y_Pin 27

uint16_t readJoystickX() {
    adc_select_input(0);
    uint adc_x_raw = adc_read();
    return adc_x_raw;
}

uint16_t readJoystickY() {
    adc_select_input(1);
    uint adc_y_raw = adc_read();
    return adc_y_raw;
}

void WhereTo() {
    if(readJoystickY() <= 600)
    {
        goForwards();
        sleep_ms(1000);
        stopMotors();
    }
    else if(readJoystickY() >= 4000){
        goBackwards();
        sleep_ms(1000);
        stopMotors();
    }
    else if(readJoystickX() <=600){
        turn90Opp();
    }
    else if (readJoystickX() >= 4000){
        turn90();    
    }
}
