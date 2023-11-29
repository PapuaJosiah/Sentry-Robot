#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define Sound 4
#define SoundR 6
#define LEDPin 5
#define LEDPin2 7

int soundDetected = 0;
int soundDetected2 = 0;
uint64_t triggerTimeR = 0;
uint64_t triggerTimeL = 0;


void RedLight(){
    gpio_put(LEDPin, 1);
    soundDetected = 1;
    triggerTimeL = get_absolute_time();
}

void YellowLight(){
    gpio_put(LEDPin2, 1);
    soundDetected2 = 1;  
    triggerTimeR = get_absolute_time();
    
    }
