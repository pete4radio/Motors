/* Bit Field     Type   Reset Description
    7-3 RESERVED  R-0    0h    Reserved
                    0h = Reserved
    2-0 REG_LOCK  R/WAPU 0h    Register Lock Bits
                    0h = No effect unless locked or unlocked
                    1h = No effect unless locked or unlocked
                    2h = No effect unless locked or unlocked
                    3h = Write 011b to this register to unlock all registers
                    4h = No effect unless locked or unlocked
                    5h = No effect unless locked or unlocked
                    6h = Write 110b to lock the settings by ignoring further register writes
                    except to these bits and address 0x03h bits 2-0.
                    7h = No effect unless locked or unlocked */

#include <stdio.h>

#include <stdio.h>

void Control_Register_1_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "RESERVED", "RESERVED", "RESERVED", "REG_LOCK", "REG_LOCK", "REG_LOCK", "REG_LOCK"
    };

    const char *descriptions[][8] = {
        {"Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved"},
        {"No effect unless locked or unlocked", "No effect unless locked or unlocked", 
         "No effect unless locked or unlocked", "Write 011b to this register to unlock all registers", 
         "No effect unless locked or unlocked", "No effect unless locked or unlocked", 
         "Write 110b to lock the settings by ignoring further register writes except to these bits and address 0x03h bits 2-0.", 
         "No effect unless locked or unlocked"}
    };

    printf("------------------Control Register 1 Decoder:\n");
    // Interpret RESERVED bits (7-3)
    printf("Bits 7-3: %s - %s\n", fields[0], descriptions[0][0]);

    // Interpret REG_LOCK bits (2-0)
    unsigned char regLockValue = byte & 0x07; // Extract bits 2-0
    printf("Bits 2-0: %s - %s\n", fields[4], descriptions[1][regLockValue]);
}
