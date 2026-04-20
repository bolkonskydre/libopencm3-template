#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
int second = 84000000;

static void rcc_setup(void) {
	rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void gpio_setup(void) {
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
}

static void delay_cicles(uint32_t cycles) {
	for (uint32_t i = 0; i < cycles; i++);

}

int main(void) {
	rcc_setup();
	gpio_setup();
	
	while (1) {
		gpio_toggle(GPIOC, GPIO13);
		delay_cicles(second / 4);
	}
	return 0;
}
