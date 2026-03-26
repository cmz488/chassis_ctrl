cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME parade_car)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Task/TaskBase.h
        OLED/Src/OLED.c
        OLED/Src/OLED_Data.c
        BlueSerial/Src/Serial.c
        LED/Src/LED.c
        LED/Inc/LED.h
        key/Src/key.c
        key/Inc/key.h
        Task/Src/KeyScan.cpp
        Task/Inc/KeyScan.h
        MPU6050/Src/mpu6050.c
        MPU6050/Inc/mpu6050.h
        MPU6050/Src/MyI2C.c
        Bsp/src/bsp_dwt.cpp
        Task/Src/Mpu6050Task.cpp
        Task/Inc/Mpu6050Task.h
        PWM/Src/Motor.c
        PWM/Src/PWM.c
        PWM/Inc/Motor.h
        Encoder/Src/Encoder.c
        Task/Src/ChassisRun.cpp
        Task/Inc/ChassisRun.h
        ChassisCtrl/Src/ChassisCtrl.cpp
        ChassisCtrl/Inc/ChassisCtrl.h
        PID/Src/AnglePid.cpp
        PID/Inc/AnglePid.h
        PID/Src/speed_pid.cpp
        Task/Src/Debug.cpp
        Task/Inc/Debug.h)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
        Task
        Task/Inc
        OLED/Inc
        BlueSerial/Inc
        LED/Inc
        key/Inc
        MPU6050/Inc
        BSP/Inc
        PWM/Inc
        Encoder/Inc
        ChassisCtrl/Inc
        PID/Inc
        PID
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
