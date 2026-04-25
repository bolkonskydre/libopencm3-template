#include "core/system.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>

static volatile uint64_t ticks = 0;

void sys_tick_handler(void) {
	ticks++;
}

static void systick_setup(void) {
	systick_set_frequency(SYSTICK_FREQ, SYS_CLK);
	systick_counter_enable();
	systick_interrupt_enable();

}

uint64_t system_get_ticks(void) {
	return ticks;
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


void system_setup(void) {
    rcc_setup();
    systick_setup();
}