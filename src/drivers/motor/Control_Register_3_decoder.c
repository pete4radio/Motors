/*     Bit Field              Type Reset Description
    7   RESERVED           R-0  0h    Reserved
                            0h = Reserved
    6   RESERVED           R/W  1h    Reserved
                            0h = Reserved
                            1h = Reserved
    5   RESERVED           R/W  0h    Reserved
                            0h = Reserved
                            1h = Reserved
    4   PWM_100_DUTY_SEL   R/W  0h    Frequency of PWM at 100% Duty Cycle
                            0h = 20KHz
                            1h = 40KHz
    3   OVP_SEL            R/W  0h    Overvoltage Level Setting
                            0h = VM overvoltage level is 34-V
                            1h = VM overvoltage level is 22-V
    2   OVP_EN             R/W  1h    Overvoltage Enable Bit
                            0h = Overvoltage protection is disabled
                            1h = Overvoltage protection is enabled
    1   RESERVED           R/W  1h    Reserved
                            0h = Reserved
                            1h = Reserved
    0   OTW_REP            R/W  0h    Overtemperature Warning Reporting Bit
                            0h = Over temperature reporting on nFAULT is disabled
                            1h = Over temperature reporting on nFAULT is enabled */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "motor.h"

void Control_Register_3_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "RESERVED", "RESERVED", "PWM_100_DUTY_SEL", 
        "OVP_SEL", "OVP_EN", "RESERVED", "OTW_REP"
    };

    const char *descriptions[][2] = {
        {"Reserved", "Reserved"}, // RESERVED (7, 6, 5, 1)
        {"20KHz", "40KHz"}, // PWM_100_DUTY_SEL (4)
        {"VM overvoltage level is 34-V", "VM overvoltage level is 22-V"}, // OVP_SEL (3)
        {"Overvoltage protection is disabled", "Overvoltage protection is enabled"}, // OVP_EN (2)
        {"Over temperature reporting on nFAULT is disabled", "Over temperature reporting on nFAULT is enabled"} // OTW_REP (0)
    };

        printf("------------------Control Register 3 Decoder:\n");
    // Interpret each bit
    for (int i = 7; i >= 0; i--) {
        int bitValue = (byte >> i) & 1; // Extract the value of the bit
        if (i == 7 || i == 6 || i == 5 || i == 1) {
            printf("Bit %d: %s - %s\n", i, fields[i], descriptions[0][bitValue]);
        } else if (i == 4) {
            printf("Bit %d: %s - %s\n", i, fields[i], descriptions[1][bitValue]);
        } else if (i == 3) {
            printf("Bit %d: %s - %s\n", i, fields[i], descriptions[2][bitValue]);
        } else if (i == 2) {
            printf("Bit %d: %s - %s\n", i, fields[i], descriptions[3][bitValue]);
        } else if (i == 0) {
            printf("Bit %d: %s - %s\n", i, fields[i], descriptions[4][bitValue]);
        }
    }
}
