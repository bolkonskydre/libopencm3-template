#include "core/comms.h"
#include "common_defines.h"


void i2c_tcie_en(i2c) {
    I2C_CR1(i2c) |= I2C_CR1_TCIE;
}

void i2c_txie_en(i2c) {
    I2C_CR1(i2c) |= I2C_CR1_TXIE;
}

void i2c_stopie_en(i2c) {
    I2C_CR1(i2c) |= I2C_CR1_STOPIE;
}

void i2c_nackie_en(i2c) {
    I2C_CR1(i2c) |= I2C_CR1_NACKIE;
}

bool i2c_check_txe(uint32_t i2c) {
    return (I2C_ISR(i2c) & I2C_ISR_TXE);
}

bool i2c_check_txis(uint32_t i2c) {
    return (I2C_ISR(i2c) & I2C_ISR_TXIS);
}

void i2c_send_strt(uint32_t i2c) {
    I2C_CR2(i2c) |= 1 << 13; // Set the START bit in the CR2 register to generate a start condition
}

void nack_en(uint32_t i2c) {
    I2C_CR1(i2c) |= I2C_CR_NACKIE(i2c);
}

void set_i2c_fastmode_timing(uint32_t i2c) {  // This function will set the timing for I2C fast mode (400 kHz). You will need to calculate the appropriate timing values based on the clock frequency of your microcontroller and the desired I2C speed. The specific calculations can be found in the STM32 reference manual.
    I2C_TIMINGR(i2c) = 0xB03FDB;
}

void i2c_setup() { // This function will set up the I2C peripheral. You will need to configure the GPIO pins for I2C, set the clock frequency, and enable the I2C peripheral. The specific configuration will depend on your hardware and requirements.
    rcc_periph_clock_enable(RCC_I2C1);
    rcc_periph_clock_enable(RCC_GPIOB);  
    
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO9 | GPIO8); // Configure GPIO pins for I2C (e.g., PF0 for SCL and PF1 for SDA)
    gpio_set_af(GPIOB, GPIO_AF4, GPIO9 | GPIO8); // Set alternate function for I2C pins

    rcc_set_peripheral_clk_sel(I2C1_BASE, RCC_D2CCIP2R_I2C123SEL_PCLK1);

    rcc_periph_reset_pulse(RST_I2C1);

    i2c_peripheral_disable(I2C1); // Ensure I2C is disabled before configuration   
    
    i2c_enable_analog_filter(I2C1);
    i2c_set_digital_filter(I2C1, 0);

    /*Enable Interrupts*/
    set_i2c_fastmode_timing(I2C1);
    i2c_peripheral_enable(I2C1); // Enable the I2C peripheral
    i2c_enable_autoend(I2C1);

    i2c_txie_en(I2C1); // Enable TXIS interrupt
    i2c_tcie_en(I2C1);
    i2c_stopie_en(I2C1);
}

void i2c_write(uint8_t device_addr, uint8_t reg_addr,  uint8_t* data, size_t len) { //this function will write data onto a register of an I2C device

    size_t reg_addr_size = sizeof(reg_addr); // Assuming reg_addr is a single byte
    size_t data_len = sizeof(data);
    i2c_set_bytes_to_transfer(I2C1, reg_addr_size); // single register to be sent
    i2c_set_7bit_address(I2C1, device_addr); // Shift address for write operation
    i2c_set_write_transfer_dir(I2C1); // Automatically send stop condition after transfer is complete.
    i2c_send_strt(I2C1); // Generate start condition

    while (!i2c_check_txis(I2C1)); // Wait until the transmit data register is empty
    i2c_send_data(I2C1, reg_addr); // Send the register address
    while (!i2c_transfer_complete(I2C1));

    for (size_t i = 0; i < data_len; i++) {
        while (!i2c_check_txis(I2C1)); // Wait until the transmit data register is empty
        i2c_send_data(I2C1, data); // Send the data byte
    }
    while (!i2c_transfer_complete(I2C1));
    i2c_send_stop(I2C1);
}
