#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include "core/timer.h"

#define I2C_CR_NACKIE(i2c) I2C_CR1(i2c) |= I2C_CR1_NACKIE
#define I2C_CR_CLEAR_NACK(i2c) I2C_ICR(i2c) = I2C_ICR_NACKCF
#define I2C_CR_CLEAR_STOP(i2c) I2C_ICR(i2c) = I2C_ICR_STOPCF

//i2c Commands
void set_i2c_fastmode_timing(uint32_t i2c); // This function will set the timing for I2C fast mode (400 kHz). You will need to calculate the appropriate timing values based on the clock frequency of your microcontroller and the desired I2C speed. The specific calculations can be found in the STM32 reference manual.

void i2c_setup();//this function will set up the I2C peripheral. You will need to configure the GPIO pins for I2C, set the clock frequency, and enable the I2C peripheral. The specific configuration will depend on your hardware and requirements.

void i2c_read(uint8_t device_addr, uint8_t reg_addr, uint8_t *buffer, size_t len);//this function will read data from a specified register of an I2C device. You will need to send the device address, followed by the register address, and then read the data into the provided buffer. The length parameter specifies how many bytes to read.

void i2c_write(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, size_t len);//this function will write data to a specified register of an I2C device. You will need to send the device address, followed by the register address, and then write the data from the provided buffer. The length parameter specifies how many bytes to write.

void spi_write(uint8_t reg_addr, uint8_t *data);


