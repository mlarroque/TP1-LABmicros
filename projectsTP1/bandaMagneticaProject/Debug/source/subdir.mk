################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/App.c \
../source/SysTick.c \
../source/doorManagement.c \
../source/gpio.c \
../source/magnetCardDecode.c \
../source/magnetCardLector.c \
../source/magnetLectorHAL.c \
../source/timer.c 

OBJS += \
./source/App.o \
./source/SysTick.o \
./source/doorManagement.o \
./source/gpio.o \
./source/magnetCardDecode.o \
./source/magnetCardLector.o \
./source/magnetLectorHAL.o \
./source/timer.o 

C_DEPS += \
./source/App.d \
./source/SysTick.d \
./source/doorManagement.d \
./source/gpio.d \
./source/magnetCardDecode.d \
./source/magnetCardLector.d \
./source/magnetLectorHAL.d \
./source/timer.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O1 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/magnetCardDecode.o: ../source/magnetCardDecode.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"source/magnetCardDecode.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


