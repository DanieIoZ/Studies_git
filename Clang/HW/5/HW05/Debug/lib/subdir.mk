################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/st7735.c \
../lib/stm32_adafruit_lcd.c \
../lib/stm32_adafruit_sd.c 

OBJS += \
./lib/st7735.o \
./lib/stm32_adafruit_lcd.o \
./lib/stm32_adafruit_sd.o 

C_DEPS += \
./lib/st7735.d \
./lib/stm32_adafruit_lcd.d \
./lib/stm32_adafruit_sd.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DNUCLEO_F446RE -DSTM32F4 -DSTM32F446RETx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -I"/home/arash/workspace/prjCPL_LCD/inc" -I"/home/arash/workspace/prjCPL_LCD/lib" -I"/home/arash/workspace/prjCPL_LCD/CMSIS/core" -I"/home/arash/workspace/prjCPL_LCD/CMSIS/device" -I"/home/arash/workspace/prjCPL_LCD/HAL_Driver/Inc/Legacy" -I"/home/arash/workspace/prjCPL_LCD/HAL_Driver/Inc" -I"/home/arash/workspace/prjCPL_LCD/Utilities/STM32F4xx-Nucleo" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


