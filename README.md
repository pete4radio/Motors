# Motors
SAMWISE Motors but compiles/debugs under RPi extension

### Overview

This program is designed to run on a Raspberry Pi Pico (or compatible
RP2350-based board) to initialize and monitor a motor control system. It
interfaces with motor drivers and a power monitor (ADM1176), providing
basic diagnostics and telemetry via serial output.

### Functional Requirements

1.  ****System Initialization****

    -   Initialize standard I/O for serial communication.
    -   Initialize the main system and all hardware peripherals.

2.  ****Motor Control (Commented/Optional)****

    -   (Commented) Enable specific motors for operation.
    -   (Commented) Set motor speed and stop motors as needed.
    -   (Commented) Read and print motor driver registers for
        diagnostics.

3.  ****Power Monitoring****

    -   Periodically (infinite loop) read battery voltage and current
        using the ADM1176 power monitor.
    -   Print the measured voltage and current to the serial terminal.

4.  ****Diagnostics (Commented/Optional)****

    -   (Commented) Read and print various motor driver registers for
        fault and status information.
    -   (Commented) Print additional battery voltage readings and
        perform motor speed cycling for testing.

5.  ****Error Handling****

    -   If the watchdog feed pin is not compatible with the "B" platform,
        halt compilation with an error.

6.  ****Test Mode****

    -   When [TEST] is
        defined, run the main telemetry and monitoring loop.

### Non-Functional Requirements

-   ****Platform Compatibility:****\
    Must check for correct pin assignments at compile time.
-   ****Serial Output:****\
    All status and telemetry must be output via the standard serial
    interface.
-   ****Maintainability:****\
    Code should be modular, with hardware-specific logic abstracted into
    drivers and initialization modules.
-   ****Safety:****\


### Out of Scope

-   Advanced motor control algorithms (beyond basic enable/disable and
    speed set).
-   User interface beyond serial output.
-   Persistent storage or configuration management.

### Acceptance Criteria

-   In test mode, the program continuously prints battery voltage and
    current.
-   Compilation fails if the Platform is not the RP2350B as it can't see the GPIO for the WDT.