#include "core/timer.h"
#include "core/system.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>
#include <stdint.h>

//freq = APB1_CLK / ((PRESCALER - 1) * (ARR_VALUE - 1))

#define PRESCALER   (240)
#define ARR_VALUE    (1000)


void timer_setup(void) {
    rcc_periph_clock_enable(RCC_TIM2);

    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);

    timer_enable_counter(TIM2);
    timer_enable_oc_output(TIM2, TIM_OC1);

    timer_set_prescaler(TIM2, PRESCALER - 1);
    timer_set_period(TIM2, ARR_VALUE - 1);

}

void timer_pwm_set_duty_cycle(float duty_cycle) {
    const float raw_value = (float)ARR_VALUE * (duty_cycle / 100.0f);
    timer_set_oc_value(TIM2, TIM_OC1, (uint32_t)raw_value);

}

void wait_ms(uint32_t ms) {
    uint32_t target_ticks = system_get_ticks() + ms;
    while ((uint64_t)system_get_ticks() < target_ticks) {
        // Busy wait until the target time is reached
    }
}