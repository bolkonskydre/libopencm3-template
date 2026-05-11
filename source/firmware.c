
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/rcc.h>
#include "core/system.h"
#include "core/timer.h"

#define LEDPORT  (GPIOA)
#define LEDPIN   (GPIO3)

//testing
static void gpio_setup(void) { //config for the GPIO Port C pin 13
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(LEDPORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LEDPIN);
	gpio_set_af(LEDPORT, GPIO_AF1, LEDPIN);

}

int main(void) {
	system_setup();
	gpio_setup();
	timer_setup();
	volatile uint32_t apb1_clk_freq = rcc_get_bus_clk_freq(RCC_APB1CLK);
	volatile uint32_t start_time = system_get_ticks();

	volatile float duty_cycle = 0.0f;

	uint32_t tim2_ccr = 0x40000034; // Address of TIM2_CCR1 register
	volatile uint32_t *tim2_ccr_ptr = (volatile uint32_t *)tim2_ccr;
	uint32_t tim2_arr = 0x4000002C; // Address of TIM2_ARR register
	volatile uint32_t *tim2_arr_ptr = (volatile uint32_t *)tim2_arr;


	timer_pwm_set_duty_cycle(duty_cycle); 
	
	while (1) {
		volatile uint64_t tick_diff = system_get_ticks() - start_time;
		if (tick_diff >= 500) { // Update duty cycle every 100 ms
			duty_cycle += 10.0f; // Increase duty cycle by 1%
			if (duty_cycle > 100.0f) {
				duty_cycle = 0.0f; // Reset to 1% after reaching 100%
			}
			timer_pwm_set_duty_cycle(duty_cycle);
			start_time = system_get_ticks(); // Reset start time for next update
		}
	}
	return 0;
	}
