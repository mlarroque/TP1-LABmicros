################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/App.c \
../source/SegmentDisplay.c \
../source/SysTick.c \
../source/dataBase.c \
../source/display.c \
../source/encoder.c \
../source/gpio.c \
../source/queue.c \
../source/stateAccessGranted.c \
../source/stateAddingUser.c \
../source/stateAdminMode.c \
../source/stateBlocked.c \
../source/stateChangeIntensity.c \
../source/stateChangingPIN.c \
../source/stateMenu.c \
../source/stateReceivingID.c \
../source/stateReceivingPIN.c \
../source/stateRemovingUser.c \
../source/timer.c \
../source/userInterface.c 

OBJS += \
./source/App.o \
./source/SegmentDisplay.o \
./source/SysTick.o \
./source/dataBase.o \
./source/display.o \
./source/encoder.o \
./source/gpio.o \
./source/queue.o \
./source/stateAccessGranted.o \
./source/stateAddingUser.o \
./source/stateAdminMode.o \
./source/stateBlocked.o \
./source/stateChangeIntensity.o \
./source/stateChangingPIN.o \
./source/stateMenu.o \
./source/stateReceivingID.o \
./source/stateReceivingPIN.o \
./source/stateRemovingUser.o \
./source/timer.o \
./source/userInterface.o 

C_DEPS += \
./source/App.d \
./source/SegmentDisplay.d \
./source/SysTick.d \
./source/dataBase.d \
./source/display.d \
./source/encoder.d \
./source/gpio.d \
./source/queue.d \
./source/stateAccessGranted.d \
./source/stateAddingUser.d \
./source/stateAdminMode.d \
./source/stateBlocked.d \
./source/stateChangeIntensity.d \
./source/stateChangingPIN.d \
./source/stateMenu.d \
./source/stateReceivingID.d \
./source/stateReceivingPIN.d \
./source/stateRemovingUser.d \
./source/timer.d \
./source/userInterface.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O2 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


