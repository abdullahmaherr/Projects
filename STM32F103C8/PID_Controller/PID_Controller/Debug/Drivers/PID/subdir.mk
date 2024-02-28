################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/PID/pid.c 

OBJS += \
./Drivers/PID/pid.o 

C_DEPS += \
./Drivers/PID/pid.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/PID/pid.o: ../Drivers/PID/pid.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/abdullah/Desktop/PID_Controller/PID_Controller/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/PID/pid.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

