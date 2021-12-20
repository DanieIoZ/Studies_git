################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f401xe.s 

OBJS += \
./startup/startup_stm32f401xe.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"/home/arash/workspace/prjCPL_LCD/inc" -I"/home/arash/workspace/prjCPL_LCD/CMSIS/core" -I"/home/arash/workspace/prjCPL_LCD/CMSIS/device" -I"/home/arash/workspace/prjCPL_LCD/HAL_Driver/Inc/Legacy" -I"/home/arash/workspace/prjCPL_LCD/HAL_Driver/Inc" -I"/home/arash/workspace/prjCPL_LCD/Utilities/STM32F4xx-Nucleo" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

