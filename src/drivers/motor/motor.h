#pragma once

#include "pico/types.h"

typedef struct {
	int FAULT_pin_;
	int SLEEP_pin_;
	int DRVOFF_pin_;
	int SCS_pin_;
	int	BRAKE_pin_;
	int PWM_pin_;
	int FGOUT_pin_;
	int pwm_slice_;
	int set_speed_;
} motor_t;

// Control Register (CRn) offsets
#define CR1 0x03 // Control Register 1, locks
#define CR2A 0x04 // Control Register 2A, SDO push-pull REQUIRED, clear fault
#define CR3 0x05 // Control Register 3, PWM frequency, Overvoltage setting, defaults ok
#define CR4 0x06 // Control Register 4, Enable REQUIRED, current limit
#define CR5 0x07 // Control Register 5, Brake/Coast, async rectification, current sense amplifier gain
#define CR6 0x08 // Control Register 6, Buck voltage and current settings
#define CR7 0x09 // Control Register 7, Brake, coast and direction
#define CR8 0x0A // Control Register 8, Motor lock retry, detection and fault
#define CR9 0x0B // Control Register 9, Phase Advance
#define CR10 0x0C // Control Register 10, Driver delay compensation

// Status Register (SRn) offsets
#define SR1 0x01 // Status Register 1, latched faults
#define SR2 0x02 // Status Register 2, buck regulator faults
#define ICR 0x00 // IC Status Register, real-time faults

motor_t motor_init(int FAULT_pin, 
					int SLEEP_pin, 
					int DRVOFF_pin,
					int SCS_pin,
					int BRAKE_pin,
					int PWM_pin,
					int FGOUT_pin);

void motor_enable(motor_t* motor);
void motor_disable(motor_t* motor);
void motor_set_speed(motor_t* motor, uint16_t speed);
void motor_reset_fault(motor_t* motor);
uint8_t motor_read_register(motor_t* motor, uint8_t reg_addr);
uint8_t motor_write_register(motor_t* motor, uint8_t reg_addr, uint8_t data);

//decoders for registers in the MCT8316ZR
void IC_Status_Register_decoder(uint8_t);
void Status_Register_1_decoder(uint8_t);
void Status_Register_2_decoder(uint8_t);
void Control_Register_1_decoder(uint8_t);
void Control_Register_2_decoder(uint8_t);
void Control_Register_3_decoder(uint8_t);
void Control_Register_4_decoder(uint8_t);
void Control_Register_5_decoder(uint8_t);
void Control_Register_6_decoder(uint8_t);
void Control_Register_7_decoder(uint8_t);
void Control_Register_8_decoder(uint8_t);
void Control_Register_9_decoder(uint8_t);
void Control_Register_10_decoder(uint8_t);
