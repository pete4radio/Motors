# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
include(${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
# ====================================================================================
set(PICO_BOARD MOTOR CACHE STRING "Board type")
set(RP2350A)
set(RP2350B 1)
set(PICO_PLATFORM "rp2350" CACHE STRING "Platform type")
include(pico_sdk_import.cmake)

project(samwise-adcs-motor C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

file(GLOB top CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB adm1176 CONFIGURE_DEPENDS "src/drivers/adm1176/*.cpp")
file(GLOB init CONFIGURE_DEPENDS "src/init/*.cpp")
file(GLOB watchdog CONFIGURE_DEPENDS "src/drivers/watchdog/*.cpp")
file(GLOB motor CONFIGURE_DEPENDS "src/drivers/motor/*.cpp")

add_executable(samwise-adcs-motor ${top} ${adm1176} ${init} ${watchdog} ${motor})

pico_set_program_name(samwise-adcs-motor "samwise_adcs_motor")
pico_set_program_version(samwise-adcs-motor "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(samwise-adcs-motor 0)
pico_enable_stdio_usb(samwise-adcs-motor 1)

# Add the standard library to the build
target_link_libraries(samwise-adcs-motor
        pico_stdlib 
		pico_util
		pico_time
		hardware_i2c
		hardware_pwm
		hardware_spi
		hardware_gpio)

# Add the standard include files to the build
target_include_directories(samwise-adcs-motor PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)
# The below was in there and I don't think I need or want it, but here it is
# ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required

target_include_directories(samwise-adcs-motor PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

pico_add_extra_outputs(samwise-adcs-motor)
