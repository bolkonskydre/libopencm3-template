
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/flash.h>
#include "core/system.h"

#define LEDPORT  (GPIOB)
#define LEDPIN   (GPIO14)

//testing
static void gpio_setup(void) { //config for the GPIO Port C pin 13
	rcc_periph_clock_enable(LEDPORT);
	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
	gpio_set_af(LEDPORT, GPIO_AF1, LEDPIN);
}


int main(void) {
	system_setup();
	gpio_setup();
	
	uint64_t start_time = system_get_ticks();
	float duty_cycle = 1.0f;

	while (1) {
		if (system_get_ticks() - start_time >= 10) { //update duty cycle every 10ms
			duty_cycle += 1.0f; //increase duty cycle by 1% every second
			if (duty_cycle > 100.0f) {
				duty_cycle = 0.0f; //reset duty cycle after reaching 100%
			}
			timer_pwm_set_duty_cycle(duty_cycle);
			start_time = system_get_ticks();
		}
	return 0;
	}
}
