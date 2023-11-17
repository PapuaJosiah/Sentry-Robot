/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define M1IN1 0
#define M1IN2 1
#define M2IN1 2
#define M2IN2 3

#define Sound 4
#define SoundR 6
#define LEDPin 5
#define LEDPin2 7



int soundDetected = 0;
int soundDetected2 = 0;
uint64_t triggerTimeR = 0;
uint64_t triggerTimeL = 0;

void stopMotors(){
	gpio_put(M1IN1, 0);
	gpio_put(M1IN2, 0);
	gpio_put(M2IN1, 0);
	gpio_put(M2IN2, 0);
}

void goForwards(){
	gpio_put(M1IN1, 1);
	gpio_put(M1IN2, 0);
	gpio_put(M2IN1, 1);
	gpio_put(M2IN2, 0);
}

void goBackwards(){
	gpio_put(M1IN1, 0);
	gpio_put(M1IN2, 1);
	gpio_put(M2IN1, 0);
	gpio_put(M2IN2, 1);
}

void turnCounterClockwise(){
	gpio_put(M1IN1, 1);
	gpio_put(M1IN2, 0);
	gpio_put(M2IN1, 0);
	gpio_put(M2IN2, 1);
}

void turnClockwise(){
	gpio_put(M1IN1, 0);
	gpio_put(M1IN2, 1);
	gpio_put(M2IN1, 1);
	gpio_put(M2IN2, 0);
}

void turn90(){
    turnClockwise();
    sleep_ms(225);
    stopMotors();
    }

void turn90Opp(){
    turnCounterClockwise();
    sleep_ms(215);
    stopMotors();
    }

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

void setup() {

	gpio_init(M1IN1);
	gpio_set_dir(M1IN1, GPIO_OUT);
	gpio_init(M1IN2);
	gpio_set_dir(M1IN2, GPIO_OUT);
	gpio_init(M2IN1);
	gpio_set_dir(M2IN1, GPIO_OUT);
	gpio_init(M2IN2);
	gpio_set_dir(M2IN2, GPIO_OUT);
	stopMotors();
    gpio_init(Sound);
    gpio_set_dir(Sound, GPIO_IN);
    gpio_init(SoundR);
    gpio_set_dir(SoundR, GPIO_IN);
    gpio_init(LEDPin);
    gpio_set_dir(LEDPin, GPIO_OUT);
    gpio_init(LEDPin2);
    gpio_set_dir(LEDPin2, GPIO_OUT);

}

void sound_isr(uint gpio_pin, uint32_t event_mask){
    if(gpio_pin==6)YellowLight();
    if(gpio_pin==4)RedLight();
}


int main() {
	setup();
    gpio_set_irq_enabled_with_callback(Sound, GPIO_IRQ_EDGE_RISE, true, &sound_isr);
    gpio_set_irq_enabled(SoundR, GPIO_IRQ_EDGE_RISE, true);

	while(1)
{
    sleep_ms(100);
    if((to_us_since_boot(triggerTimeR)) - (to_us_since_boot(triggerTimeL)) > 0){
    turn90();
    triggerTimeR = 0;
    triggerTimeL = 0;
}
    else if((to_us_since_boot(triggerTimeR)) - (to_us_since_boot(triggerTimeL)) < 0){
    turn90Opp();
    triggerTimeL = 0;
    triggerTimeR = 0;
}
    if((soundDetected = 1) || (soundDetected2 = 1)){
    sleep_ms(500);
    soundDetected = 0;
    soundDetected2 = 0;
    gpio_put(LEDPin, 0);
    gpio_put(LEDPin2, 0);
    }
}
return 0;
}
