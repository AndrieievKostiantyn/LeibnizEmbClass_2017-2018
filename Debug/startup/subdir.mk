################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f411xe.s 

OBJS += \
./startup/startup_stm32f411xe.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/inc" -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/CMSIS/core" -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/CMSIS/device" -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/StdPeriph_Driver/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


