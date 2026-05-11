
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include "core/system.h"
#include "core/timer.h"
#include "core/gpio.h"
#include "common_defines.h"

//testing
static void gpio_setup(void) { //config for the GPIO Port C pin 13
}

int main(void) {
	const struct gpio_config config = {
		.gpio_port = GPIOA,
		.gpio_pin = GPIO3,
		.gpio_af = GPIO_AF1,
		.peripheral = TIM2,
		.tim_channel = TIM_OC4,
		.duty_cycle = 10.0f, // Initial duty cycle of 10%
		.prescaler = 24000, // Prescaler value for 1 MHz timer clock (assuming 240 MHz system clock)
		.arr_value = 10000   // Auto-reload value for 1 kHz PWM frequency
	};
	system_setup();
	pwm_setup(&config);

	volatile uint32_t apb1_clk_freq = rcc_get_bus_clk_freq(RCC_APB1CLK);
	volatile uint32_t start_time = system_get_ticks();

	volatile float duty_cycle = 50.0f;
	uint32_t tim2_ccr = 0x4000003C; // Address of TIM2_CCR1 register
	uint32_t tim2_arr = 0x4000002C; // Address of TIM2_ARR register
	
	while (1) {
		volatile uint16_t tim2_cntr = timer_get_counter(TIM2);
		volatile uint32_t *tim2_ccr_ptr = (volatile uint32_t *)tim2_ccr;
		volatile uint32_t *tim2_arr_ptr = (volatile uint32_t *)tim2_arr;
	}
	return 0;
	}
