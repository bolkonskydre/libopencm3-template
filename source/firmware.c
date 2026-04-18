#include <stm32/rcc.h>
#include <stm32/gpio.h>

static void rcc_setup(void) {
	rcc_clock_setup_pll()
}

int main(void) {
	rcc_setup();
	while (1) {
		
	}
	return 0;
}
