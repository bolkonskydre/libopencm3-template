#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/flash.h>
#define STM32H7

int SYSTICK_FREQ = 1000;
int SYS_CLK = 84000000;

uint64_t ticks = 0;

void rcc_setup(void){
  const struct rcc_pll_config pll_config = {
	.sysclock_source = RCC_PLL,
	.pll_source = RCC_PLLCKSELR_PLLSRC_HSE,
	.hse_frequency = 8000000,
	.pll1 = {
		.divm = 1,
		.divn = 60,
		.divp = 1,
		.divq = 0,
		.divr = 0,
	},
	.power_mode = PWR_SYS_LDO,
	.voltage_scale = PWR_VOS_SCALE_3,
	.pll2 = {.divm = 0},
	.pll3 = {.divm = 0},
	.core_pre = 1,
	.hpre = 1,
	.ppre1 = 2,
	.ppre2 = 2,
	.ppre3 = 2,
	.ppre4 = 4
  };
  rcc_clock_setup_pll(&pll_config);
}


static void gpio_setup(void) { //config for the GPIO Port C pin 13
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
}

static void systick_setup(void) {
	systick_set_frequency(SYSTICK_FREQ, SYS_CLK);
	systick_counter_enable();
	systick_interrupt_enable();

}

static void delay_cicles(uint32_t cycles) {
	for (uint32_t i = 0; i < cycles; i++);

}

int main(void) {
	rcc_setup();
	gpio_setup();
	systick_setup();
	while (1) {
	
	return 0;
	}
}
