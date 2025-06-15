/* Bit Field       Type Reset Description
7-5 RESERVED    R-0  0h    Reserved
                   0h = Reserved
4   DLYCMP_EN   R/W  0h    Driver Delay Compensation Enable
                   0h = Disable
                   1h = Enable
3-0 DLY_TARGET  R/W  0h    Delay Target for Driver Delay Compensation
                   0h = 0 us
                   1h = 0.4 us
                   2h = 0.6 us
                   3h = 0.8 us
                   4h = 1 us
                   5h = 1.2 us
                   6h = 1.4 us
                   7h = 1.6 us
                   8h = 1.8 us
                   9h = 2 us
                   Ah = 2.2 us
                   Bh = 2.4 us
                   Ch = 2.6 us
                   Dh = 2.8 us
                   Eh = 3 us
                   Fh = 3.2 us


                    */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers/motor/motor.h"

void Control_Register_10_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "RESERVED", "RESERVED", "DLYCMP_EN", 
        "DLY_TARGET", "DLY_TARGET", "DLY_TARGET", "DLY_TARGET"
    };

    const char *descriptions[][16] = {
        {"Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved"}, // RESERVED (7-5)
        {"Disable", "Enable"}, // DLYCMP_EN (4)
        {"0 us", "0.4 us", "0.6 us", "0.8 us", "1 us", "1.2 us", "1.4 us", "1.6 us", "1.8 us", "2 us", "2.2 us", "2.4 us", "2.6 us", "2.8 us", "3 us", "3.2 us"} // DLY_TARGET (3-0)
    };

    printf("------------------Control Register 10 Decoder: 0x%02X\n", byte);
    // Interpret RESERVED bits (7-5)
    unsigned char reservedValue = (byte >> 5) & 0x07; // Extract bits 7-5
    printf("Bits 7-5: %s - %s\n", fields[0], descriptions[0][reservedValue]);

    // Interpret DLYCMP_EN bit (4)
    unsigned char dlycmpEnValue = (byte >> 4) & 0x01; // Extract bit 4
    printf("Bit 4: %s - %s\n", fields[3], descriptions[1][dlycmpEnValue]);

    // Interpret DLY_TARGET bits (3-0)
    unsigned char dlyTargetValue = byte & 0x0F; // Extract bits 3-0
    printf("Bits 3-0: %s - %s\n", fields[4], descriptions[2][dlyTargetValue]);
}
