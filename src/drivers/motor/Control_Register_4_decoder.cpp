/*     Bit Field     Type Reset Description
    7   DRV_OFF   R/W  0h    Driver OFF Bit
                    0h = No Action
                    1h = Enter Low Power Standby Mode
    6   OCP_CBC   R/W  0h    OCP PWM Cycle Operation Bit
                    0h = OCP clearing in PWM input cycle change is disabled
                    1h = OCP clearing in PWM input cycle change is enabled
    5-4 OCP_DEG   R/W  1h    OCP Deglitch Time Settings
                    0h = OCP deglitch time is 0.2 μs
                    1h = OCP deglitch time is 0.6 μs
                    2h = OCP deglitch time is 1.25 μs
                    3h = OCP deglitch time is 1.6 μs
    3   OCP_RETRY R/W  0h    OCP Retry Time Settings
                    0h = OCP retry time is 5 ms
                    1h = OCP retry time is 500 ms
    2   OCP_LVL   R/W  0h    Overcurrent Level Setting
                    0h = OCP level is 16 A
                    1h = OCP level is 24 A
    1-0 OCP_MODE  R/W  0h    OCP Fault Options
                    0h = Overcurrent causes a latched fault
                    1h = Overcurrent causes an automatic retrying fault
                    2h = Overcurrent is report only but no action is taken
                    3h = Overcurrent is not reported and no action is taken
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drivers/motor/motor.h"

void Control_Register_4_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "DRV_OFF", "OCP_CBC", "OCP_DEG", "OCP_DEG", "OCP_RETRY", "OCP_LVL", "OCP_MODE", "OCP_MODE"
    };

    const char *descriptions[][4] = {
        {"No Action", "Enter Low Power Standby Mode"}, // DRV_OFF (7)
        {"OCP clearing in PWM input cycle change is disabled", "OCP clearing in PWM input cycle change is enabled"}, // OCP_CBC (6)
        {"OCP deglitch time is 0.2 μs", "OCP deglitch time is 0.6 μs", "OCP deglitch time is 1.25 μs", "OCP deglitch time is 1.6 μs"}, // OCP_DEG (5-4)
        {"OCP retry time is 5 ms", "OCP retry time is 500 ms"}, // OCP_RETRY (3)
        {"OCP level is 16 A", "OCP level is 24 A"}, // OCP_LVL (2)
        {"Overcurrent causes a latched fault", "Overcurrent causes an automatic retrying fault", "Overcurrent is report only but no action is taken", "Overcurrent is not reported and no action is taken"} // OCP_MODE (1-0)
    };

    printf("------------------Control Register 4 Decoder: 0x%02X\n", byte);
    // Interpret each bit or group of bits
    printf("Bit 7: %s - %s\n", fields[0], descriptions[0][(byte >> 7) & 0x01]); // DRV_OFF
    printf("Bit 6: %s - %s\n", fields[1], descriptions[1][(byte >> 6) & 0x01]); // OCP_CBC
    printf("Bits 5-4: %s - %s\n", fields[2], descriptions[2][(byte >> 4) & 0x03]); // OCP_DEG
    printf("Bit 3: %s - %s\n", fields[4], descriptions[3][(byte >> 3) & 0x01]); // OCP_RETRY
    printf("Bit 2: %s - %s\n", fields[5], descriptions[4][(byte >> 2) & 0x01]); // OCP_LVL
    printf("Bits 1-0: %s - %s\n", fields[6], descriptions[5][byte & 0x03]); // OCP_MODE
}
