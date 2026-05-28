#include "core/gpio.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void timer_pwm_set_duty_cycle(const struct gpio_config *config)
{
    const float raw_value = (float)config->arr_value * (config->duty_cycle / 100.0f);
    timer_set_oc_value(config->peripheral, config->tim_channel, (uint32_t)raw_value);
}

void pwm_setup(const struct gpio_config *config) {
    /* 1. Enable clocks */
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_TIM3);

    /* 2. Configure the specified GPIO pin as TIM2_CH4 (AF1) */
    gpio_mode_setup(config->gpio_port, GPIO_MODE_AF, GPIO_PUPD_NONE, config->gpio_pin);
    gpio_set_af(config->gpio_port, config->gpio_af, config->gpio_pin);        // Important: AF1 for TIM2 on H7

    /* 3. Timer base configuration */
    timer_set_mode(config->peripheral, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    
    timer_set_prescaler(config->peripheral, config->prescaler - 1);           // Timer tick = 1 MHz (240MHz / 240)
    timer_set_period(config->peripheral, config->arr_value - 1);              // 1 kHz PWM (1MHz / 1000)
    timer_enable_preload(config->peripheral);

    /* 4. PWM mode on Channel 4 */
    timer_set_oc_mode(config->peripheral, config->tim_channel, TIM_OCM_PWM1);     // PWM mode 1
    timer_set_oc_polarity_high(config->peripheral, config->tim_channel);
    timer_enable_oc_preload(config->peripheral, config->tim_channel);
    
    timer_enable_oc_output(config->peripheral, config->tim_channel);              // Enable compare output

    /* 5. Enable the timer */
    timer_enable_counter(config->peripheral);

    timer_pwm_set_duty_cycle(config); // Set initial duty cycle to 10%
}
