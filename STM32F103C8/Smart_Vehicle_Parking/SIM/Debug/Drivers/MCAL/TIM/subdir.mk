################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MCAL/TIM/stm32f103c8_tim_driver.c 

OBJS += \
./Drivers/MCAL/TIM/stm32f103c8_tim_driver.o 

C_DEPS += \
./Drivers/MCAL/TIM/stm32f103c8_tim_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MCAL/TIM/stm32f103c8_tim_driver.o: ../Drivers/MCAL/TIM/stm32f103c8_tim_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/abdullah/Desktop/EMBEDDED K/Smart_Vehicle_Parking/Smart_Vehicle_Parking/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MCAL/TIM/stm32f103c8_tim_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

