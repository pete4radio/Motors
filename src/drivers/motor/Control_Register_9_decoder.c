/*     Bit Field       Type Reset Description
    7-3 RESERVED    R-0  0h    Reserved
                    0h = Reserved
    2-0 ADVANCE_LVL R/W  0h    Phase Advance Setting
                    0h = 0°
                    1h = 4°
                    2h = 7°
                    3h = 11°
                    4h = 15°
                    5h = 20°
                    6h = 25°
                    7h = 30°

*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers/motor/motor.h"

void Control_Register_9_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "RESERVED", "RESERVED", "RESERVED", 
        "ADVANCE_LVL", "ADVANCE_LVL", "ADVANCE_LVL", "ADVANCE_LVL"
    };

    const char *descriptions[][8] = {
        {"Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved"}, // RESERVED (7-3)
        {"0°", "4°", "7°", "11°", "15°", "20°", "25°", "30°"} // ADVANCE_LVL (2-0)
    };

    printf("------------------Control Register 9 Decoder:\n");
    // Interpret RESERVED bits (7-3)
    unsigned char reservedValue = (byte >> 3) & 0x1F; // Extract bits 7-3
    printf("Bits 7-3: %s - %s\n", fields[0], descriptions[0][reservedValue]);

    // Interpret ADVANCE_LVL bits (2-0)
    unsigned char advanceLvlValue = byte & 0x07; // Extract bits 2-0
    printf("Bits 2-0: %s - %s\n", fields[4], descriptions[1][advanceLvlValue]);
}
