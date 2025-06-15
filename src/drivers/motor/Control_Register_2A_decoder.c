// Control Register 2A Decoder
/*     Bit Field     Type Reset Description
    7-6 RESERVED  R/W  2h    Reserved
                    0h = Reserved
                    1h = Reserved
                    2h = Reserved
                    3h = Reserved
    5   SDO_MODE  R/W  0h    SDO Mode Setting
                    0h = SDO IO in Open Drain Mode
                    1h = SDO IO in Push Pull Mode
    4-3 SLEW      R/W  0h    Slew Rate Settings
                    0h = Slew rate is 25 V/μs
                    1h = Slew rate is 50 V/μs
                    2h = Slew rate is 125 V/μs
                    3h = Slew rate is 200 V/μs
    2-1 PWM_MODE  R/W  0h    Device Mode Selection
                    0h = Asynchronous rectification with analog Hall
                    1h = Asynchronous rectification with digital Hall
                    2h = Synchronous rectification with analog Hall
                    3h = Synchronous rectification with digital Hall
    0   CLR_FLT   W1C  0h    Clear Fault
                    0h = No clear fault command is issued
                    1h = To clear the latched fault bits. This bit automatically resets after being written.

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void Control_Register_2A_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "RESERVED", "SDO_MODE", "SLEW", "SLEW", "PWM_MODE", "PWM_MODE", "CLR_FLT"
    };

    const char *descriptions[][4] = {
        {"Reserved", "Reserved", "Reserved", "Reserved"}, // RESERVED (7-6)
        {"SDO IO in Open Drain Mode", "SDO IO in Push Pull Mode"}, // SDO_MODE (5)
        {"Slew rate is 25 V/μs", "Slew rate is 50 V/μs", "Slew rate is 125 V/μs", "Slew rate is 200 V/μs"}, // SLEW (4-3)
        {"Asynchronous rectification with analog Hall", "Asynchronous rectification with digital Hall", 
         "Synchronous rectification with analog Hall", "Synchronous rectification with digital Hall"}, // PWM_MODE (2-1)
        {"No clear fault command is issued", "To clear the latched fault bits"} // CLR_FLT (0)
    };

    printf("------------------Control Register 2A Decoder:\n");
    // Interpret RESERVED bits (7-6)
    unsigned char reservedValue = (byte >> 6) & 0x03; // Extract bits 7-6
    printf("Bits 7-6: %s - %s\n", fields[0], descriptions[0][reservedValue]);

    // Interpret SDO_MODE bit (5)
    unsigned char sdoModeValue = (byte >> 5) & 0x01; // Extract bit 5
    printf("Bit 5: %s - %s\n", fields[2], descriptions[1][sdoModeValue]);

    // Interpret SLEW bits (4-3)
    unsigned char slewValue = (byte >> 3) & 0x03; // Extract bits 4-3
    printf("Bits 4-3: %s - %s\n", fields[3], descriptions[2][slewValue]);

    // Interpret PWM_MODE bits (2-1)
    unsigned char pwmModeValue = (byte >> 1) & 0x03; // Extract bits 2-1
    printf("Bits 2-1: %s - %s\n", fields[5], descriptions[3][pwmModeValue]);

    // Interpret CLR_FLT bit (0)
    unsigned char clrFltValue = byte & 0x01; // Extract bit 0
    printf("Bit 0: %s - %s\n", fields[7], descriptions[4][clrFltValue]);
}
