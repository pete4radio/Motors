/*     Bit Field       Type Reset Description
    7   RESERVED    R-0  0h    Reserved
                    0h = Reserved
                    1h = Reserved
    6   OTP_ERR     R    0h    One Time Programmability Error
                    0h = No OTP error is detected
                    1h = OTP Error is detected
    5   BUCK_OCP    R    0h    Buck Regulator Overcurrent Status Bit
                    0h = No buck regulator overcurrent is detected
                    1h = Buck regulator overcurrent is detected
    4   BUCK_UV     R    0h    Buck Regulator Undervoltage Status Bit
                    0h = No buck regulator undervoltage is detected
                    1h = Buck regulator undervoltage is detected
    3   VCP_UV      R    0h    Charge Pump Undervoltage Status Bit
                    0h = No charge pump undervoltage is detected
                    1h = Charge pump undervoltage is detected
    2   SPI_PARITY  R-0  0h    SPI Parity Error Bit
                    0h = No SPI parity error is detected
                    1h = SPI parity error is detected
    1   SPI_SCLK_FLT R   0h    SPI Clock Framing Error Bit
                    0h = No SPI clock framing error is detected
                    1h = SPI clock framing error is detected
    0   SPI_ADDR_FLT R   0h    SPI Address Error Bit
                    0h = No SPI address fault is detected (due to accessing non-user register)
                    1h = SPI address fault is detected */
#include <stdio.h>
#include <stdio.h>

void interpretStatusRegister(unsigned char byte) {
    // Define the bit field descriptions
    const char *fields[] = {
        "SPI_ADDR_FLT", "SPI_SCLK_FLT", "SPI_PARITY", "VCP_UV", 
        "BUCK_UV", "BUCK_OCP", "OTP_ERR", "RESERVED"
    };

    const char *descriptions[][2] = {
        {"No SPI address fault is detected (due to accessing non-user register)", "SPI address fault is detected"},
        {"No SPI clock framing error is detected", "SPI clock framing error is detected"},
        {"No SPI parity error is detected", "SPI parity error is detected"},
        {"No charge pump undervoltage is detected", "Charge pump undervoltage is detected"},
        {"No buck regulator undervoltage is detected", "Buck regulator undervoltage is detected"},
        {"No buck regulator overcurrent is detected", "Buck regulator overcurrent is detected"},
        {"No OTP error is detected", "OTP Error is detected"},
        {"Reserved", "Reserved"}
    };

    // Iterate through each bit in the byte
    for (int i = 0; i < 8; i++) {
        int bitValue = (byte >> i) & 1; // Extract the value of the bit
        printf("Bit %d: %s - %s\n", i, fields[i], descriptions[i][bitValue]);
    }
}

int main() {
    unsigned char byte = 0b10101010; // Example byte
    interpretStatusRegister(byte);
    return 0;
}