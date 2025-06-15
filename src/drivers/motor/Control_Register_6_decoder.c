/*     Bit Field       Type Reset Description
    7-6 RESERVED    R-0  0h    Reserved
                    0h = Reserved
    5   RESERVED    R/W  0h    Reserved
                    0h = Reserved
                    1h = Reserved
    4   BUCK_PS_DIS R/W  0h    Buck Power Sequencing Disable Bit
                    0h = Buck power sequencing is enabled
                    1h = Buck power sequencing is disabled
    3   BUCK_CL     R/W  0h    Buck Current Limit Setting
                    0h = Buck regulator current limit is set to 600 mA
                    1h = Buck regulator current limit is set to 150 mA
    2-1 BUCK_SEL    R/W  0h    Buck Voltage Selection
                    0h = Buck voltage is 3.3 V
                    1h = Buck voltage is 5.0 V
                    2h = Buck voltage is 4.0 V
                    3h = Buck voltage is 5.7 V
    0   BUCK_DIS    R/W  0h    Buck Disable Bit
                    0h = Buck regulator is enabled
                    1h = Buck regulator is disabled
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void Control_Register_6_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "RESERVED", "BUCK_PS_DIS", "BUCK_CL", 
        "BUCK_SEL", "BUCK_SEL", "BUCK_SEL", "BUCK_DIS"
    };

    const char *descriptions[][4] = {
        {"Reserved", "Reserved"}, // RESERVED (7-6, 5)
        {"Buck power sequencing is enabled", "Buck power sequencing is disabled"}, // BUCK_PS_DIS (4)
        {"Buck regulator current limit is set to 600 mA", "Buck regulator current limit is set to 150 mA"}, // BUCK_CL (3)
        {"Buck voltage is 3.3 V", "Buck voltage is 5.0 V", "Buck voltage is 4.0 V", "Buck voltage is 5.7 V"}, // BUCK_SEL (2-1)
        {"Buck regulator is enabled", "Buck regulator is disabled"} // BUCK_DIS (0)
    };

    printf("------------------Control Register 6 Decoder:\n");
    // Interpret each bit or group of bits
    printf("Bits 7-6: %s - %s\n", fields[0], descriptions[0][(byte >> 6) & 0x03]); // RESERVED
    printf("Bit 5: %s - %s\n", fields[1], descriptions[0][(byte >> 5) & 0x01]); // RESERVED
    printf("Bit 4: %s - %s\n", fields[2], descriptions[1][(byte >> 4) & 0x01]); // BUCK_PS_DIS
    printf("Bit 3: %s - %s\n", fields[3], descriptions[2][(byte >> 3) & 0x01]); // BUCK_CL
    printf("Bits 2-1: %s - %s\n", fields[4], descriptions[3][(byte >> 1) & 0x03]); // BUCK_SEL
    printf("Bit 0: %s - %s\n", fields[7], descriptions[4][byte & 0x01]); // BUCK_DIS
}

int main() {
    unsigned char byte = 0b10101010; // Example byte
    Control_Register_6_decoder(byte);
    return 0;
}