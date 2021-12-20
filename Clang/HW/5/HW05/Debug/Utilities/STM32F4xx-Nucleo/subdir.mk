################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F4xx-Nucleo/stm32f4xx_nucleo.c 

OBJS += \
./Utilities/STM32F4xx-Nucleo/stm32f4xx_nucleo.o 

C_DEPS += \
./Utilities/STM32F4xx-Nucleo/stm32f4xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F4xx-Nucleo/%.o: ../Utilities/STM32F4xx-Nucleo/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DNUCLEO_F446RE -DSTM32F4 -DSTM32F446RETx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -I"/home/arash/workspace/prjCPL_LCD/inc" -I"/home/arash/workspace/prjCPL_LCD/lib" -I"/home/arash/workspace/prjCPL_LCD/CMSIS/core" -I"/home/arash/workspace/prjCPL_LCD/CMSIS/device" -I"/home/arash/workspace/prjCPL_LCD/HAL_Driver/Inc/Legacy" -I"/home/arash/workspace/prjCPL_LCD/HAL_Driver/Inc" -I"/home/arash/workspace/prjCPL_LCD/Utilities/STM32F4xx-Nucleo" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


