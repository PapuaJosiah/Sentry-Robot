/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "sound.c"
#include "movement.c"

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
    if((to_us_since_boot(triggerTimeR)) > (to_us_since_boot(triggerTimeL))){
    turn90();
    triggerTimeR = 0;
    triggerTimeL = 0;
}
    else if((to_us_since_boot(triggerTimeL)) > (to_us_since_boot(triggerTimeR))){
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

