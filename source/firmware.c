
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/flash.h>
#include "inc/core/system.h"

#define STM32H7

#define LEDPORT  (GPIOC)
#define LEDPIN   (GPIO13)


static void gpio_setup(void) { //config for the GPIO Port C pin 13
	rcc_periph_clock_enable(GPIOC);
	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
}


int main(void) {
	rcc_setup();
	gpio_setup();

	systick_setup();

	uint64_t start_time = get_ticks();

	while (1) {
		if (get_ticks() - start_time >= 1000) {
			gpio_toggle(GPIOC, GPIO13);
			start_time = get_ticks();
		}
	return 0;
	}
}
