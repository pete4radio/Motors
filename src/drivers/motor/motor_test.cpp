#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "slate.h"
#include "drivers/motor/motor.h"
#include "hardware/gpio.h"
#include "drivers/motor/motor.h"

#define NUM_MOTORS 4 

void enable_motors(slate_t* slate) {
    uint8_t nmotors = 0;
    while (nmotors < NUM_MOTORS) {  // For testing, stop here if can't access motor chips
        for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
            if (motor_enable(&slate->motors[i]) == PICO_OK) {
                nmotors++;
                printf("Motor %d enabled successfully.\n", i);
            } else {
                printf("Failed to enable motor %d.\n", i);
            } 
        }
     sleep_ms(1000); // Wait a bit before trying again
    }        
}

void disable_motors(slate_t* slate) {
    for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
        motor_disable(&slate->motors[i]);
        printf("Motor %d disabled.\n", i);
    }
}


uint8_t report_motor_faults(slate_t* slate) {
    uint8_t fault_count = 0;
    for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
        if (gpio_get(slate->motors[i].FAULT_pin_) != 1) {
            printf("Motor %d fault GPIO aserted low!\n", i);
            fault_count++;
        } else {
            printf("Motor %d is functioning normally.\n", i);
        }
        // if Sleep is asserted low, let's think of that as a software fault
        if (gpio_get(slate->motors[i].SLEEP_pin_) != 1) {
            printf("Motor %d Sleep pin asserted low!\n", i);
            fault_count++;
        } else {
            printf("Motor %d Sleep pin is functioning normally.\n", i);
        }
        // if BRAKE pin is asserted high, let's think of that as a software fault
        if (gpio_get(slate->motors[i].BRAKE_pin_) != 0) {
            printf("Motor %d Brake pin asserted high!\n", i);
            fault_count++;
        } else {
            printf("Motor %d Brake pin is functioning normally.\n", i);
        }

        // if DRVOFF pin is asserted low, let's think of that as a software fault
        if (gpio_get(slate->motors[i].DRVOFF_pin_) != 1) {
            printf("Motor %d DRVOFF pin asserted low!\n", i);
            fault_count++;
        } else {
            printf("Motor %d DRVOFF pin is functioning normally.\n", i);
        }

        uint8_t fault = motor_read_register(&slate->motors[i], 0x0); // Example fault register
        printf("Motor %d fault register: 0x%02x\n", i, fault);
    }
return fault_count;
}

// see slso motor.cpp motor-reset_fault
void reset_motor_faults(slate_t* slate) {
    for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
        if (gpio_get(slate->motors[i].FAULT_pin_) == 0) {
            printf("Resetting faults for motor %d...\n", i);
            gpio_put(slate->motors[i].SLEEP_pin_, 1); // Reset fault via sleep pin
            sleep_us(30); // Allow time for reset
            gpio_put(slate->motors[i].SLEEP_pin_, 0); // Re-enable motor
        } else {
            printf("Motor %d has no faults to reset.\n", i);
        }
        printf("Motor %d faults reset.  Checking...\n", i);
        sleep_ms(100); // Wait for reset to take effect
        report_motor_faults(slate);
    }
}   

void run_speed_test(slate_t* slate) {
    int speeds[] = {1<<10, 1<<12, 1<<14}; // Low, medium, high
    printf("Running motors at low, medium, high speed, then coasting...\n");
    for (uint8_t s = 0; s < 3; ++s) {
        for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: speed %d\n", i, speeds[s]);
            uint8_t err = motor_set_speed(&slate->motors[i], speeds[s]);
            if (err) printf("Error setting speed for motor %d: %d\n", i, err);
        }
        sleep_ms(2000);
        report_motor_faults(slate);
    }
    printf("Coasting all motors...\n");
    for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
        uint8_t err = motor_set_speed(&slate->motors[i], 0);
        if (err) printf("Error coasting motor %d: %d\n", i, err);
    }
    sleep_ms(2000);
    report_motor_faults(slate);

    printf("Spinning up again and braking...\n");
    for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
        uint8_t err = motor_set_speed(&slate->motors[i], speeds[2]);
        if (err) printf("Error spinning up motor %d: %d\n", i, err);
    }
    sleep_ms(2000);
    for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
        uint8_t err = motor_brake(&slate->motors[i]);
        if (err) printf("Error braking motor %d: %d\n", i, err);
    }
    sleep_ms(2000);
    report_motor_faults(slate);
}

void run_stall_test(slate_t* slate) {
    int speeds[] = {1<<10, 1<<12, 1<<14};
    printf("Prepare to stall each motor at low, medium, high speed.\n");
    for (uint8_t s = 0; s < 3; ++s) {
        for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: speed %d. Prevent rotation now, then press any key.\n", i, speeds[s]);
            uint8_t err = motor_set_speed(&slate->motors[i], speeds[s]);
            if (err) printf("Error setting speed for motor %d: %d\n", i, err);
            getchar();
            report_motor_faults(slate);
            // Compare to expected behavior here (manual for now)
            uint8_t stop_err = motor_set_speed(&slate->motors[i], 0);
            if (stop_err) printf("Error stopping motor %d: %d\n", i, stop_err);
        }
    }
}

void run_disconnect_test(slate_t* slate) {
    printf("Disconnect one motor at a time as prompted.\n");
    for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
        printf("Please disconnect motor %d, then press any key.\n", i);
        getchar();
        report_motor_faults(slate);
        // Compare to expected behavior here (manual for now)
    }
}

void run_reverse_brake_test(slate_t* slate) {
    printf("Spinning motors fast, braking, and reversing direction 3 times.\n");
    for (uint8_t t = 0; t < 3; ++t) {
        for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: spin forward fast.\n", i);
            uint8_t err = motor_set_speed(&slate->motors[i], 1<<14);
            if (err) printf("Error spinning motor %d: %d\n", i, err);
        }
        sleep_ms(1500);
        for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: brake.\n", i);
            uint8_t err = motor_brake(&slate->motors[i]);
            if (err) printf("Error braking motor %d: %d\n", i, err);
        }
        sleep_ms(1000);
        for (uint8_t i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: spin reverse fast.\n", i);
            uint8_t err = motor_set_speed(&slate->motors[i], -(1<<14));
            if (err) printf("Error spinning motor %d reverse: %d\n", i, err);
        }
        sleep_ms(1500);
        report_motor_faults(slate);
    }
}
void run_motor_tests(slate_t* slate) {
    printf("Starting motor tests...\n");
    
    enable_motors(slate);
    sleep_ms(1000);
    
    if (uint8_t nfaults = report_motor_faults(slate)) {
        printf("Motor faults detected after enable: %d. Resetting...\n", nfaults);
        reset_motor_faults(slate);
    } else {
        printf("No motor faults detected after enable.\n");
    }   
    
    run_speed_test(slate);
    if (uint8_t nfaults = report_motor_faults(slate)) {
        printf("Motor faults detected after speed test: %d. Resetting...\n", nfaults);
        reset_motor_faults(slate);
    } else {
        printf("No motor faults detected after speed test.\n");
    }   

    run_stall_test(slate);
    if (uint8_t nfaults = report_motor_faults(slate)) {
        printf("Motor faults detected after stall test: %d. Resetting...\n", nfaults);
        reset_motor_faults(slate);
    } else {
        printf("No motor faults detected after stall test.\n");
    }

    run_disconnect_test(slate);
    if (uint8_t nfaults = report_motor_faults(slate)) {
        printf("Motor faults detected after disconnect test: %d. Resetting...\n", nfaults);
        reset_motor_faults(slate);
    } else {
        printf("No motor faults detected after disconnect test.\n");
    }

    run_reverse_brake_test(slate);
    if (uint8_t nfaults = report_motor_faults(slate)) {
        printf("Motor faults detected after brake test: %d. Resetting...\n", nfaults);
        reset_motor_faults(slate);
    } else {
        printf("No motor faults detected after brake test.\n");
    }
    
    disable_motors(slate);
    
    printf("Motor tests completed.\n");
}