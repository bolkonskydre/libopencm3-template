#ifndef INC_TIMER_H
#define INC_TIMER_H
#include <stdint.h>

void timer_setup(void);
void timer_pwm_set_duty_cycle(float duty_cycle);

void wait_ms(uint32_t ms);

#endif

