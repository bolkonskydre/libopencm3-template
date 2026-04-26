#include "core/timer.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>



void timer_setup(void) {
    rcc_periph_clock_enable(RCC_TIM1);

    timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
}

void timer_pwm_set_duty_cicle(float duty_cycle) {



}