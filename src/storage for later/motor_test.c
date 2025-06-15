#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "slate.h"
#include "drivers/motor/motor.h"

#define NUM_MOTORS 4 // Adjust as needed

void report_motor_faults(slate_t* slate) {
    for (int i = 0; i < NUM_MOTORS; ++i) {
        uint8_t fault = motor_read_register(&slate->motors[i], 0x0); // Example fault register
        printf("Motor %d fault register: 0x%02x\n", i, fault);
    }
}

void run_speed_test(slate_t* slate) {
    int speeds[] = {1<<10, 1<<12, 1<<14}; // Low, medium, high
    printf("Running motors at low, medium, high speed, then coasting...\n");
    for (int s = 0; s < 3; ++s) {
        for (int i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: speed %d\n", i, speeds[s]);
            int err = motor_set_speed(&slate->motors[i], speeds[s]);
            if (err) printf("Error setting speed for motor %d: %d\n", i, err);
        }
        sleep_ms(2000);
        report_motor_faults(slate);
    }
    printf("Coasting all motors...\n");
    for (int i = 0; i < NUM_MOTORS; ++i) {
        int err = motor_set_speed(&slate->motors[i], 0);
        if (err) printf("Error coasting motor %d: %d\n", i, err);
    }
    sleep_ms(2000);
    report_motor_faults(slate);

    printf("Spinning up again and braking...\n");
    for (int i = 0; i < NUM_MOTORS; ++i) {
        int err = motor_set_speed(&slate->motors[i], speeds[2]);
        if (err) printf("Error spinning up motor %d: %d\n", i, err);
    }
    sleep_ms(2000);
    for (int i = 0; i < NUM_MOTORS; ++i) {
        int err = motor_brake(&slate->motors[i]);
        if (err) printf("Error braking motor %d: %d\n", i, err);
    }
    sleep_ms(2000);
    report_motor_faults(slate);
}

void run_stall_test(slate_t* slate) {
    int speeds[] = {1<<10, 1<<12, 1<<14};
    printf("Prepare to stall each motor at low, medium, high speed.\n");
    for (int s = 0; s < 3; ++s) {
        for (int i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: speed %d. Prevent rotation now, then press any key.\n", i, speeds[s]);
            int err = motor_set_speed(&slate->motors[i], speeds[s]);
            if (err) printf("Error setting speed for motor %d: %d\n", i, err);
            getchar();
            report_motor_faults(slate);
            // Compare to expected behavior here (manual for now)
            int stop_err = motor_set_speed(&slate->motors[i], 0);
            if (stop_err) printf("Error stopping motor %d: %d\n", i, stop_err);
        }
    }
}

void run_disconnect_test(slate_t* slate) {
    printf("Disconnect one motor at a time as prompted.\n");
    for (int i = 0; i < NUM_MOTORS; ++i) {
        printf("Please disconnect motor %d, then press any key.\n", i);
        getchar();
        report_motor_faults(slate);
        // Compare to expected behavior here (manual for now)
    }
}

void run_reverse_brake_test(slate_t* slate) {
    printf("Spinning motors fast, braking, and reversing direction 3 times.\n");
    for (int t = 0; t < 3; ++t) {
        for (int i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: spin forward fast.\n", i);
            int err = motor_set_speed(&slate->motors[i], 1<<14);
            if (err) printf("Error spinning motor %d: %d\n", i, err);
        }
        sleep_ms(1500);
        for (int i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: brake.\n", i);
            int err = motor_brake(&slate->motors[i]);
            if (err) printf("Error braking motor %d: %d\n", i, err);
        }
        sleep_ms(1000);
        for (int i = 0; i < NUM_MOTORS; ++i) {
            printf("Motor %d: spin reverse fast.\n", i);
            int err = motor_set_speed(&slate->motors[i], -(1<<14));
            if (err) printf("Error spinning motor %d reverse: %d\n", i, err);
        }
        sleep_ms(1500);
        report_motor_faults(slate);
    }
}