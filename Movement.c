
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define M1IN1 0
#define M1IN2 1
#define M2IN1 2
#define M2IN2 3

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
