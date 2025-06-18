#include "motor.h"

#include "pico/printf.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

motor_t motor_init(int FAULT_pin, 
					int SLEEP_pin, 
					int DRVOFF_pin,
					int SCS_pin,
					int BRAKE_pin,
					int PWM_pin,
					int FGOUT_pin){

	gpio_set_function(PWM_pin, GPIO_FUNC_PWM);
	int slice_num = pwm_gpio_to_slice_num(PWM_pin);

	motor_t motor = (motor_t) {
		.FAULT_pin_ = FAULT_pin,
		.SLEEP_pin_ = SLEEP_pin,
		.DRVOFF_pin_ = DRVOFF_pin,
		.SCS_pin_ = SCS_pin,
		.BRAKE_pin_ = BRAKE_pin,
		.PWM_pin_ = PWM_pin,
		.FGOUT_pin_ = FGOUT_pin,
		.pwm_slice_ = slice_num, 
		.set_speed_ = 0,
	};

	gpio_init(motor.FAULT_pin_); // Sets function SIO
	gpio_set_dir(motor.FAULT_pin_, GPIO_IN);
	gpio_disable_pulls(motor.FAULT_pin_);

	// Set freq to 20hz
	pwm_set_clkdiv(slice_num, 1.83f);
	pwm_set_wrap(slice_num, 1<<12);
	// SPI Driver
	gpio_init(motor.SCS_pin_);
    gpio_set_dir(motor.SCS_pin_, GPIO_OUT);
	gpio_pull_down(motor.SCS_pin_);
    gpio_put(motor.SCS_pin_, 1);

	return motor;
}

uint8_t motor_enable(motor_t* motor){
	pwm_set_enabled(motor->pwm_slice_, true);

	// Set the DRVOFF pin to high
	gpio_init(motor->DRVOFF_pin_); // Sets function SIO
	gpio_set_dir(motor->DRVOFF_pin_, GPIO_OUT);		
	gpio_pull_up(motor->DRVOFF_pin_);
	gpio_put(motor->DRVOFF_pin_, 1);

	// No Brake
	gpio_init(motor->BRAKE_pin_); // Sets function SIO
	gpio_set_dir(motor->BRAKE_pin_, GPIO_OUT);
	gpio_pull_up(motor->BRAKE_pin_);
	gpio_put(motor->BRAKE_pin_, 0);
	
	// Initialize registers by putting it into sleep
	gpio_init(motor->SLEEP_pin_); // Sets function SIO
	gpio_set_dir(motor->SLEEP_pin_, GPIO_OUT);
	gpio_pull_up(motor->SLEEP_pin_);
	gpio_put(motor->SLEEP_pin_, 0); // Put motor driver to sleep which resets registers.
	sleep_ms(10);
	gpio_put(motor->SLEEP_pin_, 1); // Wake up the motor driver
	sleep_ms(10);
	
	// unlock registers for writing
	motor_write_register(motor, CR1, 0b011); // Unlock registers for writing
	// Set the SDO_MODE to push-pull, as the CPU pullup is too weak to be certain
	motor_write_register(motor, CR2A, 0b1 << 5); // Set SDO_MODE to push-pull
	// check that it got set and we can read it back
	if (motor_read_register(motor, CR2A) && 0b1 << 5) {
		printf("Motor driver SDO_MODE set to push-pull.\n");
	} else {
		printf("Failed to set SDO_MODE to push-pull.\n");
		return PICO_ERROR_GENERIC;
	}

	// See if the chip is responding on SPI
	if(	uint8_t Register_5 = motor_read_register(motor, CR5) == 0x46){
		printf("Motor driver is responding on SPI.\n");
	} else {
		printf("Motor driver %d is not responding on SPI. Register 5: %x\n", motor, Register_5);
		return PICO_ERROR_GENERIC;
	}

	// Unlock registers for writing
	//motor_write_register(motor, 0x3, 0b011);

	//motor_write_register(motor, 0x4, 0x2);

	pwm_set_enabled(motor->pwm_slice_, true);

	// Set the DRVOFF pin to high
	gpio_init(motor->DRVOFF_pin_); // Sets function SIO
	gpio_set_dir(motor->DRVOFF_pin_, GPIO_OUT);		
	gpio_pull_up(motor->DRVOFF_pin_);
	gpio_put(motor->DRVOFF_pin_, 1);

	// No Brake
	gpio_init(motor->BRAKE_pin_); // Sets function SIO
	gpio_set_dir(motor->BRAKE_pin_, GPIO_OUT);
	gpio_pull_up(motor->BRAKE_pin_);
	gpio_put(motor->BRAKE_pin_, 0);

	//  reset faults
	motor_reset_fault(motor);

	return PICO_OK;
}

uint8_t motor_disable(motor_t* motor) {
	pwm_set_enabled(motor->pwm_slice_, false);
	gpio_put(motor->SLEEP_pin_, 0);
	return PICO_OK;
}

uint8_t motor_set_speed(motor_t* motor, uint16_t speed) {
	pwm_set_gpio_level(motor->PWM_pin_, speed);
	pwm_set_enabled(motor->pwm_slice_, true);
	return PICO_OK;
}

uint8_t motor_brake(motor_t* motor) {
	// Set the PWM to 0 and enable the brake pin
	pwm_set_gpio_level(motor->PWM_pin_, 0);
	gpio_put(motor->BRAKE_pin_, 1);
	return PICO_OK;
}

uint8_t motor_coast(motor_t* motor) {
	// Set the PWM to 0 and disable the brake pin
	pwm_set_gpio_level(motor->PWM_pin_, 0);
	gpio_put(motor->BRAKE_pin_, 0);
	return PICO_OK;
}

uint8_t motor_read_register(motor_t* motor, uint8_t reg_addr) {
	uint8_t tx_buf[2] = {0,0};
	uint8_t rx_buf[2] = {0,0};

	// Construct the read xcommand (MSB = 1 for read)
	tx_buf[0] = 0;
	tx_buf[0] |= (1 << 7);  // Read from register
	tx_buf[0] |= (reg_addr << 1);

	uint8_t parity_count = 0;
	for (int i=0; i < 8; i++) {
		if (tx_buf[0] & (1 << i)){
			parity_count++;
		}
	}
	if (parity_count % 2 == 1) {
		tx_buf[0] |= 1;
	}

	tx_buf[1] = 0x00;  // Dummy byte

	gpio_put(motor->SCS_pin_, 0);
	spi_write_read_blocking(spi0, tx_buf, rx_buf, 2);
	gpio_put(motor->SCS_pin_, 1);

	sleep_us(400);

	return rx_buf[1];  // Second byte contains the register value
}

uint8_t motor_write_register(motor_t* motor, uint8_t reg_addr, uint8_t data) {
	uint8_t tx_buf[2] = {0,0};
	uint8_t rx_buf[2] = {0,0};

	tx_buf[0] = 0;
	// Construct the write command (MSB = 0 for write - so do nothing)
	tx_buf[0] |= (reg_addr << 1);

	tx_buf[1] = data; 

	uint8_t parity_count = 0;
	for (int i=0; i < 8; i++) {
		if (tx_buf[0] & (1 << i)){
			parity_count++;
		}
        if (tx_buf[1] & (1 << i)) {
            parity_count++;
        }
	}
	if (parity_count % 2 == 1) {
		tx_buf[0] |= 1;
	}
	

	gpio_put(motor->SCS_pin_, 0);
	spi_write_read_blocking(spi0, tx_buf, rx_buf, 2);
	gpio_put(motor->SCS_pin_, 1);

	sleep_us(400);

    return rx_buf[0];  // Second byte contains the previous value
}

uint8_t motor_reset_fault(motor_t* motor) {
    gpio_put(motor->SLEEP_pin_, 0);
	sleep_us(30);
    gpio_put(motor->SLEEP_pin_, 1);
	return PICO_OK;
}
