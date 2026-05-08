
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/rcc.h>
#include "core/system.h"

#define LEDPORT  (GPIOE)
#define LEDPIN   (GPIO13)

//testing
static void gpio_setup(void) { //config for the GPIO Port C pin 13
	rcc_periph_clock_enable(RCC_GPIOE);
	gpio_mode_setup(LEDPORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LEDPIN);
	gpio_set_af(LEDPORT, GPIO_AF1, LEDPIN);

}

int main(void) {
	system_setup();
	gpio_setup();
	timer_setup();
	float duty_cycle = 0.0f;
	uint64_t start_time = system_get_ticks();
	timer_pwm_set_duty_cycle(duty_cycle); 

	while (1) {
		if (system_get_ticks() - start_time >= 1000) { // Update duty cycle every 100 ms
			duty_cycle += 10.0f; // Increase duty cycle by 10%
			if (duty_cycle > 100.0f) {
				duty_cycle = 0.0f; // Reset to 1% after reaching 100%
			}
			timer_pwm_set_duty_cycle(duty_cycle);
			start_time = system_get_ticks(); // Reset start time for next update
		}
	}
	return 0;
	}
