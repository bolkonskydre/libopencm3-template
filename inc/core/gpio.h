//prescaler max 65536

#define LEDPORT  (GPIOA)
#define LEDPIN   (GPIO3)

#include <stdint.h>

struct gpio_config {
    uint64_t gpio_port;
    uint16_t gpio_pin;
    uint8_t gpio_af;
    uint64_t peripheral;
    float duty_cycle;
    uint16_t prescaler;
    uint16_t arr_value;
    uint64_t tim_channel;
};

void pwm_setup(const struct gpio_config *config);
