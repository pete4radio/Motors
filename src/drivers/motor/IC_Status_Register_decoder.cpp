// Prints the status of the motor controller IC based on the status register value
#include <stdio.h>
#include <stdint.h>
// IC_Status_Register_decoder.c
/* Bit Field     Type Reset Description
7   MTR_LOCK  R    0h    Motor Lock Status Bit
                   0h = No motor lock is detected
                   1h = Motor lock is detected
6   BK_FLT    R    0h    Buck Fault Bit
                   0h = No buck regulator fault condition is detected
                   1h = Buck regulator fault condition is detected
5   SPI_FLT   R    0h    SPI Fault Bit
                   0h = No SPI fault condition is detected
                   1h = SPI Fault condition is detected
4   OCP       R    0h    Over Current Protection Status Bit
                   0h = No overcurrent condition is detected
                   1h = Overcurrent condition is detected
3   NPOR      R    0h    Supply Power On Reset Bit
                   0h = Power on reset condition is detected on VM
                   1h = No power-on-reset condition is detected on VM
2   OVP       R    0h    Supply Overvoltage Protection Status Bit
                   0h = No overvoltage condition is detected on VM
                   1h = Overvoltage condition is detected on VM
1   OT        R    0h    Overtemperature Fault Status Bit
                   0h = No overtemperature warning / shutdown is detected
                   1h = Overtemperature warning / shutdown is detected
0   FAULT     R    0h    Device Fault Bit
                   0h = No fault condition is detected
                   1h = Fault condition is detected */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "motor.h"

void IC_Status_Register_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "FAULT", "OT", "OVP", "NPOR", "OCP", "SPI_FLT", "BK_FLT", "MTR_LOCK"
    };

    const char *descriptions[][2] = {
        {"No fault condition is detected", "Fault condition is detected"},
        {"No overtemperature warning / shutdown is detected", "Overtemperature warning / shutdown is detected"},
        {"No overvoltage condition is detected on VM", "Overvoltage condition is detected on VM"},
        {"Power on reset condition is detected on VM", "No power-on-reset condition is detected on VM"},
        {"No overcurrent condition is detected", "Overcurrent condition is detected"},
        {"No SPI fault condition is detected", "SPI Fault condition is detected"},
        {"No buck regulator fault condition is detected", "Buck regulator fault condition is detected"},
        {"No motor lock is detected", "Motor lock is detected"}
    };

        printf("------------------IC_Status_Register 1 Decoder: 0x%02X\n", byte);
    // Iterate through each bit in the byte
    for (int i = 0; i < 8; i++) {
        int bitValue = (byte >> i) & 1; // Extract the value of the bit
        printf("Bit %d: %s - %s\n", i, fields[i], descriptions[i][bitValue]);
    }
}
