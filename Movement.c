#include <stdio.h>
#include "pico/stdlib.h"

#define M1IN1 0
#define M1IN2 1
#define M2IN1 2
#define M2IN2 3

void setup() {

	gpio_init(M1IN1);
	gpio_set_dir(M1IN1, GPIO_OUT);
	gpio_init(M1IN2);
	gpio_set_dir(M1IN2, GPIO_OUT);
	gpio_init(M2IN1);
	gpio_set_dir(M2IN1, GPIO_OUT);
	gpio_init(M2IN2);
	gpio_set_dir(M2IN2, GPIO_OUT);

	stopMotor();
}

void stopMotor(){
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

void gobackwards(){
	gpio_put(M1IN1, 0);
	gpio_put(M1IN2, 1);
	gpio_put(M2IN1, 0);
	gpio_put(M2IN2, 1);
}

void turnClockwise(){
	gpio_put(M1IN1, 1);
	gpio_put(M1IN2, 0);
	gpio_put(M2IN1, 0);
	gpio_put(M2IN2, 1);
}

void turnCounterClockwise(){
	gpio_put(M1IN1, 0);
	gpio_put(M1IN2, 1);
	gpio_put(M2IN1, 1);
	gpio_put(M2IN2, 0);
}




int main() {
	stdio_init_all();
	setup();

	while(1)
{
	goForwards();
	sleep_ms(2000);
}
return 0;
}
