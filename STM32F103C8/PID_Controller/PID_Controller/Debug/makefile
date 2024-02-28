################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/PID/subdir.mk
-include Drivers/MCAL/USART/subdir.mk
-include Drivers/MCAL/TIMER/subdir.mk
-include Drivers/MCAL/SPI/subdir.mk
-include Drivers/MCAL/RCC/subdir.mk
-include Drivers/MCAL/I2C/subdir.mk
-include Drivers/MCAL/GPIO/subdir.mk
-include Drivers/MCAL/EXTI/subdir.mk
-include Drivers/HAL/LCD/subdir.mk
-include Drivers/HAL/Keypad/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
PID_Controller.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
PID_Controller.list \

OBJCOPY_BIN += \
PID_Controller.bin \


# All Target
all: PID_Controller.elf secondary-outputs

# Tool invocations
PID_Controller.elf: $(OBJS) $(USER_OBJS) C:\Users\abdullah\Desktop\PID_Controller\PID_Controller\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "PID_Controller.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\abdullah\Desktop\PID_Controller\PID_Controller\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="PID_Controller.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

PID_Controller.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "PID_Controller.list"
	@echo 'Finished building: $@'
	@echo ' '

PID_Controller.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "PID_Controller.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
