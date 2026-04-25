
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/flash.h>
#include "core/system.h"

#define LEDPORT  (GPIOC)
#define LEDPIN   (GPIO13)


static void gpio_setup(void) { //config for the GPIO Port C pin 13
	rcc_periph_clock_enable(LEDPORT);
	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
}


int main(void) {
	system_setup();
	gpio_setup();

	uint64_t start_time = system_get_ticks();

	while (1) {
		if (system_get_ticks() - start_time >= 1000) {
			gpio_toggle(LEDPORT, LEDPIN);
			start_time = system_get_ticks();
		}
	return 0;
	}
}
