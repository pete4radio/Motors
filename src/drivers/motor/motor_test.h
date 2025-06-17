#ifndef MOTOR_TEST_H
#define MOTOR_TEST_H

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "slate.h"
#include "drivers/motor/motor.h"

// Define the number of motors
#define NUM_MOTORS 4

// Function prototypes
uint8_t report_motor_faults(slate_t* slate);
void reset_motor_faults(slate_t* slate);
void enable_motors(slate_t* slate);
void disable_motors(slate_t* slate);
void run_speed_test(slate_t* slate);
void run_stall_test(slate_t* slate);
void run_disconnect_test(slate_t* slate);
void run_reverse_brake_test(slate_t* slate);
void run_motor_tests(slate_t* slate);

#endif // MOTOR_TEST_H