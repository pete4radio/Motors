/*     Bit Field         Type Reset Description
    7-6 FGOUT_SEL     R/W  0h    Electrical Frequency Generation Output Mode Bits
                        0h = FGOUT frequency is 3x commutation frequency
                        1h = FGOUT frequency is 1x of commutation frequency
                        2h = FGOUT frequency is 0.5x of commutation frequency
                        3h = FGOUT frequency is 0.25x of commutation frequency
    5   RESERVED      R-0  0h    Reserved
                        0h = Reserved
    4   MTR_LOCK_RETRY R/W  0h    Motor Lock Retry Time Settings
                        0h = 500 ms
                        1h = 5000 ms
    3-2 MTR_LOCK_TDET R/W  0h    Motor Lock Detection Time Settings
                        0h = 300 ms
                        1h = 500 ms
                        2h = 1000 ms
                        3h = 5000 ms
    1-0 MTR_LOCK_MODE R/W  0h    Motor Lock Fault Options
                        0h = Motor lock causes a latched fault
                        1h = Motor lock causes an automatic retrying fault
                        2h = Motor lock is report only but no action is taken
                        3h = Motor lock is not reported and no action is taken
                      */   

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers/motor/motor.h"

void Control_Register_8_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "FGOUT_SEL", "FGOUT_SEL", "FGOUT_SEL", "FGOUT_SEL", 
        "RESERVED", "MTR_LOCK_RETRY", "MTR_LOCK_TDET", "MTR_LOCK_MODE"
    };

    const char *descriptions[][4] = {
        {"FGOUT frequency is 3x commutation frequency", "FGOUT frequency is 1x of commutation frequency", 
         "FGOUT frequency is 0.5x of commutation frequency", "FGOUT frequency is 0.25x of commutation frequency"}, // FGOUT_SEL (7-6)
        {"Reserved", "Reserved"}, // RESERVED (5)
        {"500 ms", "5000 ms"}, // MTR_LOCK_RETRY (4)
        {"300 ms", "500 ms", "1000 ms", "5000 ms"}, // MTR_LOCK_TDET (3-2)
        {"Motor lock causes a latched fault", "Motor lock causes an automatic retrying fault", 
         "Motor lock is report only but no action is taken", "Motor lock is not reported and no action is taken"} // MTR_LOCK_MODE (1-0)
    };

    printf("------------------Control Register 8 Decoder:\n");
    // Interpret each bit or group of bits
    printf("Bits 7-6: %s - %s\n", fields[0], descriptions[0][(byte >> 6) & 0x03]); // FGOUT_SEL
    printf("Bit 5: %s - %s\n", fields[4], descriptions[1][(byte >> 5) & 0x01]); // RESERVED
    printf("Bit 4: %s - %s\n", fields[5], descriptions[2][(byte >> 4) & 0x01]); // MTR_LOCK_RETRY
    printf("Bits 3-2: %s - %s\n", fields[6], descriptions[3][(byte >> 2) & 0x03]); // MTR_LOCK_TDET
    printf("Bits 1-0: %s - %s\n", fields[7], descriptions[4][byte & 0x03]); // MTR_LOCK_MODE
}
