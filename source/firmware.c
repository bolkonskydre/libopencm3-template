
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include "core/system.h"
#include "core/timer.h"
#include "core/gpio.h"
#include "common_defines.h"
#include "core/comms.h"


// Buffer to hold data read from I2C device
volatile uint8_t buffer[2];
#define ADXL345_ADDR 0x53 // I2C address for ADXL345 accelerometer
//testing

#define PWR_CTL 0x2D

uint8_t jooj = 0x08; // Set the measure bit in the power control register to start measurements
uint8_t xdata_ptr = 0x32; // Pointer to the start of X data registers on the ADXL345

struct gpio_config config = {
		.gpio_port = GPIOC,
		.gpio_pin = GPIO6,
		.gpio_af = GPIO_AF2,
		.peripheral = TIM3,
		.tim_channel = TIM_OC1,
		.duty_cycle = 0.0f, // Initial duty cycle of 10%
		.prescaler = 240, // Prescaler value for 1 MHz timer clock (assuming 240 MHz system clock)
		.arr_value = 1000   // Auto-reload value for 1 kHz PWM frequency
	};


int main(void) {
	
	system_setup();

//	i2c_write(ADXL345_ADDR, PWR_CTL, &jooj, 1); // Set data rate to 25Hz	
	volatile uint32_t apb1_clk_freq = rcc_get_bus_clk_freq(RCC_APB1CLK);
	volatile uint32_t start_time = system_get_ticks();

	uint32_t tim2_ccr = 0x4000003C; // Address of TIM2_CCR1 register
	uint32_t tim2_arr = 0x4000002C; // Address of TIM2_ARR register

//freq = APB1_CLK / ((PRESCALER - 1) * (ARR_VALUE - 1))

	while (1) {
	volatile uint16_t tim2_cntr = timer_get_counter(TIM3);
		volatile uint32_t *tim2_ccr_ptr = (volatile uint32_t *)tim2_ccr;
		volatile uint32_t *tim2_arr_ptr = (volatile uint32_t *)tim2_arr;
		volatile uint32_t tick_diff = system_get_ticks() - start_time;
		if (tick_diff >= 10) { // Update duty cycle every 1 second
			config.duty_cycle += 1.0f; // Increase duty cycle by 10%
			if (config.duty_cycle > 100.0f) {
				config.duty_cycle = 0.0f; // Reset to 0% after reaching 100%
				pwm_setup(&config); // Update PWM configuration with new duty cycle
			}
			start_time = system_get_ticks(); // Reset start time for next update
			pwm_setup(&config); // Update PWM configuration with new duty cycle
		}
	}
	return 0;
}
