################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103-SDCARD/Middleware/FatFs/src/diskio.c \
../STM32F103-SDCARD/Middleware/FatFs/src/ff.c \
../STM32F103-SDCARD/Middleware/FatFs/src/ff_gen_drv.c 

OBJS += \
./STM32F103-SDCARD/Middleware/FatFs/src/diskio.o \
./STM32F103-SDCARD/Middleware/FatFs/src/ff.o \
./STM32F103-SDCARD/Middleware/FatFs/src/ff_gen_drv.o 

C_DEPS += \
./STM32F103-SDCARD/Middleware/FatFs/src/diskio.d \
./STM32F103-SDCARD/Middleware/FatFs/src/ff.d \
./STM32F103-SDCARD/Middleware/FatFs/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103-SDCARD/Middleware/FatFs/src/%.o STM32F103-SDCARD/Middleware/FatFs/src/%.su STM32F103-SDCARD/Middleware/FatFs/src/%.cyclo: ../STM32F103-SDCARD/Middleware/FatFs/src/%.c STM32F103-SDCARD/Middleware/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/CMSIS/Device/ST/STM32F10x/Include" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/CMSIS/Include" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/STM32F10x_StdPeriph_Driver/inc" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/BSP" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Driver" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Lib/sdlib" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Middleware/FatFs/src" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/ST7789-STM32_STD_Lib/ST7789" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Interrupt" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/APP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32F103-2d-SDCARD-2f-Middleware-2f-FatFs-2f-src

clean-STM32F103-2d-SDCARD-2f-Middleware-2f-FatFs-2f-src:
	-$(RM) ./STM32F103-SDCARD/Middleware/FatFs/src/diskio.cyclo ./STM32F103-SDCARD/Middleware/FatFs/src/diskio.d ./STM32F103-SDCARD/Middleware/FatFs/src/diskio.o ./STM32F103-SDCARD/Middleware/FatFs/src/diskio.su ./STM32F103-SDCARD/Middleware/FatFs/src/ff.cyclo ./STM32F103-SDCARD/Middleware/FatFs/src/ff.d ./STM32F103-SDCARD/Middleware/FatFs/src/ff.o ./STM32F103-SDCARD/Middleware/FatFs/src/ff.su ./STM32F103-SDCARD/Middleware/FatFs/src/ff_gen_drv.cyclo ./STM32F103-SDCARD/Middleware/FatFs/src/ff_gen_drv.d ./STM32F103-SDCARD/Middleware/FatFs/src/ff_gen_drv.o ./STM32F103-SDCARD/Middleware/FatFs/src/ff_gen_drv.su

.PHONY: clean-STM32F103-2d-SDCARD-2f-Middleware-2f-FatFs-2f-src

