################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/HAL/Mototrs/Servo_Motors/servo_motor.c 

OBJS += \
./Drivers/HAL/Mototrs/Servo_Motors/servo_motor.o 

C_DEPS += \
./Drivers/HAL/Mototrs/Servo_Motors/servo_motor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HAL/Mototrs/Servo_Motors/servo_motor.o: ../Drivers/HAL/Mototrs/Servo_Motors/servo_motor.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/abdullah/Desktop/EMBEDDED K/Smart_Vehicle_Parking/Smart_Vehicle_Parking/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/HAL/Mototrs/Servo_Motors/servo_motor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

