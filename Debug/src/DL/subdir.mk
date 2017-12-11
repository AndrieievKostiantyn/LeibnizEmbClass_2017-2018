################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DL/drvGPIO.c \
../src/DL/drvIWDG.c \
../src/DL/drvKeyboard.c \
../src/DL/drvRCC.c \
../src/DL/drvSysClock.c \
../src/DL/drvTrafficLight.c 

OBJS += \
./src/DL/drvGPIO.o \
./src/DL/drvIWDG.o \
./src/DL/drvKeyboard.o \
./src/DL/drvRCC.o \
./src/DL/drvSysClock.o \
./src/DL/drvTrafficLight.o 

C_DEPS += \
./src/DL/drvGPIO.d \
./src/DL/drvIWDG.d \
./src/DL/drvKeyboard.d \
./src/DL/drvRCC.d \
./src/DL/drvSysClock.d \
./src/DL/drvTrafficLight.d 


# Each subdirectory must supply rules for building sources it contributes
src/DL/%.o: ../src/DL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F4 -DSTM32 -DNUCLEO_F411RE -DSTM32F411RETx -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F411xE -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/inc" -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/CMSIS/core" -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/CMSIS/device" -I"D:/Developer/Electrical_Engineering/LeibnizEmbClass_2017-2018/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


