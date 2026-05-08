#include "core/system.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>

static volatile uint64_t ticks = 0;

//HSI 64MHz
//HSE 8MHz

void sys_tick_handler(void) {
	ticks++;
}

static void systick_setup(void) {
	systick_set_frequency(SYSTICK_FREQ, SYS_CLK);//RCC_CFGR_SW_PLL1 is used to indicate that the PLL1 output frequency should be used for the SYSTICK clock source, which is set to 480MHz in rcc_setup. This means that the SYSTICK timer will tick at a frequency of 480MHz / 1000 = 480kHz, resulting in an interrupt every 1ms (1000 ticks per second).
	systick_counter_enable();
	systick_interrupt_enable();

}

uint64_t system_get_ticks(void) {
	return ticks;
}

void rcc_setup(void){
  const struct rcc_pll_config pll_config = {
	.sysclock_source = RCC_PLL, //
	.pll_source = RCC_PLLCKSELR_PLLSRC_HSE,
	.hse_frequency = 8000000, // 8MHz
	.pll1 = {
		.divm = 0x1, // 8MHz / 1 = 8MHz
		.divn = 0x78, // 8MHz * 120 = 960MHz
		.divp = 0x2, // 960MHz / 2 = 480MHz
		.divq = 0xF, // 960MHz / 15 = 64MHz
		.divr = 0x2, // 960MHz / 2 = 480MHz
	},
	.pll2 = {
		.divm =0x20, // 8MHz / 32 = 250kHz
		.divn =0x80, // 250kHz * 128 = 32MHz
		.divp =0x2, // 32MHz / 2 = 16MHz
		.divq =0x2,
		.divr =0x2,
	},
	.pll3 = { 
		.divm =0x2,
		.divn =0x3C,
		.divp =0x2,
		.divq =0xF,
		.divr =0x2,
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
	.flash_waitstates = 0x4, // 4 wait states for 480MHz
  };

  rcc_clock_setup_pll(&pll_config);
}


void system_setup(void) {
    rcc_setup();
    systick_setup();
}