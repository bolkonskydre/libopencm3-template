#include "core/timer.h"
#include "core/system.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>
#include <stdint.h>

//freq = APB1_CLK / ((PRESCALER - 1) * (ARR_VALUE - 1))



void timer_setup(void) {
    rcc_periph_clock_enable(RCC_TIM2);
}

void wait_ms(uint32_t ms) {
    uint32_t target_ticks = system_get_ticks() + ms;
    while ((uint64_t)system_get_ticks() < target_ticks) {
        // Busy wait until the target time is reached
    }
}