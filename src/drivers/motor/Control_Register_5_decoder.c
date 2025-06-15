/*     Bit Field     Type Reset Description
    7 RESERVED    R/W  0h    Reserved
                    0h = Reserved
                    1h = Reserved
    6 ILIM_RECIR  R/W  0h    Current Limit Recirculation Settings
                    0h = Current recirculation through FETs (Brake Mode)
                    1h = Current recirculation through diodes (Coast Mode)
    5 RESERVED    R/W  0h    Reserved
                    0h = Reserved
                    1h = Reserved
    4 RESERVED    R/W  0h    Reserved
                    0h = Reserved
                    1h = Reserved
    3 EN_AAR      R/W  0h    Active Asynchronous Rectification Enable Bit
                    0h = AAR mode is disabled
                    1h = AAR mode is enabled
    2 EN_ASR      R/W  0h    Active Synchronous Rectification Enable Bit
                    0h = ASR mode is disabled
                    1h = ASR mode is enabled
    1-0 CSA_GAIN  R/W  0h    Current Sense Amplifier's Gain Settings
                    0h = CSA gain is 0.15 V/A
                    1h = CSA gain is 0.3 V/A
                    2h = CSA gain is 0.6 V/A
                    3h = CSA gain is 1.2 V/A
                    */ 
#include <stdio.h>
#include <stdio.h>

void Control_Register_5_decoder(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "RESERVED", "ILIM_RECIR", "RESERVED", "RESERVED", 
        "EN_AAR", "EN_ASR", "CSA_GAIN", "CSA_GAIN"
    };

    const char *descriptions[][4] = {
        {"Reserved", "Reserved"}, // RESERVED (7, 5, 4)
        {"Current recirculation through FETs (Brake Mode)", "Current recirculation through diodes (Coast Mode)"}, // ILIM_RECIR (6)
        {"AAR mode is disabled", "AAR mode is enabled"}, // EN_AAR (3)
        {"ASR mode is disabled", "ASR mode is enabled"}, // EN_ASR (2)
        {"CSA gain is 0.15 V/A", "CSA gain is 0.3 V/A", "CSA gain is 0.6 V/A", "CSA gain is 1.2 V/A"} // CSA_GAIN (1-0)
    };

    // Interpret each bit or group of bits
    printf("Bit 7: %s - %s\n", fields[0], descriptions[0][(byte >> 7) & 0x01]); // RESERVED
    printf("Bit 6: %s - %s\n", fields[1], descriptions[1][(byte >> 6) & 0x01]); // ILIM_RECIR
    printf("Bit 5: %s - %s\n", fields[2], descriptions[0][(byte >> 5) & 0x01]); // RESERVED
    printf("Bit 4: %s - %s\n", fields[3], descriptions[0][(byte >> 4) & 0x01]); // RESERVED
    printf("Bit 3: %s - %s\n", fields[4], descriptions[2][(byte >> 3) & 0x01]); // EN_AAR
    printf("Bit 2: %s - %s\n", fields[5], descriptions[3][(byte >> 2) & 0x01]); // EN_ASR
    printf("Bits 1-0: %s - %s\n", fields[6], descriptions[4][byte & 0x03]); // CSA_GAIN
}

int main() {
    unsigned char byte = 0b10101010; // Example byte
    Control_Register_5_decoder(byte);
    return 0;
}