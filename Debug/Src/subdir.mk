################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f10x.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f10x.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/CMSIS/Device/ST/STM32F10x/Include" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/CMSIS/Include" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/STM32F10x_StdPeriph_Driver/inc" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/BSP" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Driver" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Lib/sdlib" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Middleware/FatFs/src" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/ST7789-STM32_STD_Lib/ST7789" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Interrupt" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/APP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f10x.cyclo ./Src/system_stm32f10x.d ./Src/system_stm32f10x.o ./Src/system_stm32f10x.su

.PHONY: clean-Src

