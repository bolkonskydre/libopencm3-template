#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/i2c.h>
#define STM32H7

int SYSTICK_FREQ = 1000;
int SYS_CLK = 84000000;

volatile uint64_t ticks = 0;
void sys_tick_handler(void) {
	ticks++;
}

void rcc_setup(void){
  const struct rcc_pll_config pll_config = {
	.sysclock_source = RCC_CFGR_SW_PLL1,
	.pll_source = RCC_PLLCKSELR_PLLSRC_HSE,
	.hse_frequency = 8000000,
	.pll1 = {
		.divm = RCC_PLLCKSELR_DIVM_BYP,
		.divn = 120,
		.divp = 2,
		.divq = 8,
		.divr = 2,
	},
	.pll2 = {
		.divm =RCC_PLLCKSELR_DIVM_BYP,
		.divn =32,
		.divp =2,
		.divq =2,
		.divr =2,
	},
	.pll3 = {
		.divm =2,
		.divn =128,
		.divp =2,
		.divq =2,
		.divr =16,
	},
	.power_mode = PWR_SYS_LDO,
	.voltage_scale = PWR_VOS_SCALE_0,
	.smps_level = 0,
	.core_pre = RCC_D1CFGR_D1CPRE_BYP,
	.hpre = RCC_D1CFGR_D1HPRE_DIV2,
	.ppre1 = RCC_D1CFGR_D1PPRE_DIV2,
	.ppre2 = RCC_D2CFGR_D2PPRE_DIV2,
	.ppre3 = RCC_D2CFGR_D2PPRE_DIV2,
	.ppre4 = RCC_D3CFGR_D3PPRE_DIV2,
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
