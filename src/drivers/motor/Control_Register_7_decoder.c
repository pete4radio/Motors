/*     Bit Field       Type Reset Description
    7-5 RESERVED    R-0  0h    Reserved
                    0h = Reserved
    4   HALL_HYS    R/W  0h    Hall Comparator Hysteresis Settings
                    0h = 5 mV
                    1h = 50 mV
    3   BRAKE_MODE  R/W  0h    Brake Mode Setting
                    0h = Device operation is braking in brake mode
                    1h = Device operation is coasting in brake mode
    2   COAST       R/W  0h    Coast Bit
                    0h = Device coast mode is disabled
                    1h = Device coast mode is enabled
    1   BRAKE       R/W  0h    Brake Bit
                    0h = Device brake mode is disabled
                    1h = Device brake mode is enabled
    0   DIR         R/W  0h    Direction Bit
                    0h = Motor direction is set to clockwise direction
                    1h = Motor direction is set to anti-clockwise direction */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers/motor/motor.h"

void Control_Register_7_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "RESERVED", "RESERVED", "HALL_HYS", 
        "BRAKE_MODE", "COAST", "BRAKE", "DIR"
    };

    const char *descriptions[][2] = {
        {"Reserved", "Reserved"}, // RESERVED (7-5)
        {"5 mV", "50 mV"}, // HALL_HYS (4)
        {"Device operation is braking in brake mode", "Device operation is coasting in brake mode"}, // BRAKE_MODE (3)
        {"Device coast mode is disabled", "Device coast mode is enabled"}, // COAST (2)
        {"Device brake mode is disabled", "Device brake mode is enabled"}, // BRAKE (1)
        {"Motor direction is set to clockwise direction", "Motor direction is set to anti-clockwise direction"} // DIR (0)
    };

    printf("------------------Control Register 7 Decoder:\n");
    // Interpret each bit or group of bits
    printf("Bits 7-5: %s - %s\n", fields[0], descriptions[0][(byte >> 5) & 0x07]); // RESERVED
    printf("Bit 4: %s - %s\n", fields[3], descriptions[1][(byte >> 4) & 0x01]); // HALL_HYS
    printf("Bit 3: %s - %s\n", fields[4], descriptions[2][(byte >> 3) & 0x01]); // BRAKE_MODE
    printf("Bit 2: %s - %s\n", fields[5], descriptions[3][(byte >> 2) & 0x01]); // COAST
    printf("Bit 1: %s - %s\n", fields[6], descriptions[4][(byte >> 1) & 0x01]); // BRAKE
    printf("Bit 0: %s - %s\n", fields[7], descriptions[5][byte & 0x01]); // DIR
}
