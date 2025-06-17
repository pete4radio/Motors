// Description: This code interprets the Status Register 1 of a motor driver.
// Status_Register_1_decoder.c


/*     Bit Field     Type Reset Description
    7   OTW       R    0h    Overtemperature Warning Status Bit
                    0h = No overtemperature warning is detected
                    1h = Overtemperature warning is detected
    6   OTS       R    0h    Overtemperature Shutdown Status Bit
                    0h = No overtemperature shutdown is detected
                    1h = Overtemperature shutdown is detected
    5   OCP_HC    R    0h    Overcurrent Status on High-side switch of OUTC
                    0h = No overcurrent detected on high-side switch of OUTC
                    1h = Overcurrent detected on high-side switch of OUTC
    4   OCL_LC    R    0h    Overcurrent Status on Low-side switch of OUTC
                    0h = No overcurrent detected on low-side switch of OUTC
                    1h = Overcurrent detected on low-side switch of OUTC
    3   OCP_HB    R    0h    Overcurrent Status on High-side switch of OUTB
                    0h = No overcurrent detected on high-side switch of OUTB
                    1h = Overcurrent detected on high-side switch of OUTB
    2   OCP_LB    R    0h    Overcurrent Status on Low-side switch of OUTB
                    0h = No overcurrent detected on low-side switch of OUTB
                    1h = Overcurrent detected on low-side switch of OUTB
    1   OCP_HA    R    0h    Overcurrent Status on High-side switch of OUTA
                    0h = No overcurrent detected on high-side switch of OUTA
                    1h = Overcurrent detected on high-side switch of OUTA
    0   OCP_LA    R    0h    Overcurrent Status on Low-side switch of OUTA
                    0h = No overcurrent detected on low-side switch of OUTA
                    1h = Overcurrent detected on low-side switch of OUTA */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Status_Register_1_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "OCP_LA", "OCP_HA", "OCP_LB", "OCP_HB", "OCL_LC", "OCP_HC", "OTS", "OTW"
    };

    const char *descriptions[][2] = {
        {"No overcurrent detected on low-side switch of OUTA", "Overcurrent detected on low-side switch of OUTA"},
        {"No overcurrent detected on high-side switch of OUTA", "Overcurrent detected on high-side switch of OUTA"},
        {"No overcurrent detected on low-side switch of OUTB", "Overcurrent detected on low-side switch of OUTB"},
        {"No overcurrent detected on high-side switch of OUTB", "Overcurrent detected on high-side switch of OUTB"},
        {"No overcurrent detected on low-side switch of OUTC", "Overcurrent detected on low-side switch of OUTC"},
        {"No overcurrent detected on high-side switch of OUTC", "Overcurrent detected on high-side switch of OUTC"},
        {"No overtemperature shutdown is detected", "Overtemperature shutdown is detected"},
        {"No overtemperature warning is detected", "Overtemperature warning is detected"}
    };
    printf("------------------Status Register 1 Decoder: 0x%02X\n", byte);
    // Iterate through each bit in the byte
    for (int i = 0; i < 8; i++) {
        int bitValue = (byte >> i) & 1; // Extract the value of the bit
        printf("Bit %d: %s - %s\n", i, fields[i], descriptions[i][bitValue]);
    }
}
