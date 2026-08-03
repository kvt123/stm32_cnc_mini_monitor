################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ST7789-STM32_STD_Lib/ST7789/fonts.c \
../ST7789-STM32_STD_Lib/ST7789/st7789.c 

OBJS += \
./ST7789-STM32_STD_Lib/ST7789/fonts.o \
./ST7789-STM32_STD_Lib/ST7789/st7789.o 

C_DEPS += \
./ST7789-STM32_STD_Lib/ST7789/fonts.d \
./ST7789-STM32_STD_Lib/ST7789/st7789.d 


# Each subdirectory must supply rules for building sources it contributes
ST7789-STM32_STD_Lib/ST7789/%.o ST7789-STM32_STD_Lib/ST7789/%.su ST7789-STM32_STD_Lib/ST7789/%.cyclo: ../ST7789-STM32_STD_Lib/ST7789/%.c ST7789-STM32_STD_Lib/ST7789/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/CMSIS/Device/ST/STM32F10x/Include" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/CMSIS/Include" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Libraries/STM32F10x_StdPeriph_Driver/inc" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/BSP" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Driver" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Lib/sdlib" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/STM32F103-SDCARD/Middleware/FatFs/src" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/ST7789-STM32_STD_Lib/ST7789" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/Interrupt" -I"/home/khanhtranvan/STM32CubeIDE/workspace_2.1.1/mini_sd_test/APP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ST7789-2d-STM32_STD_Lib-2f-ST7789

clean-ST7789-2d-STM32_STD_Lib-2f-ST7789:
	-$(RM) ./ST7789-STM32_STD_Lib/ST7789/fonts.cyclo ./ST7789-STM32_STD_Lib/ST7789/fonts.d ./ST7789-STM32_STD_Lib/ST7789/fonts.o ./ST7789-STM32_STD_Lib/ST7789/fonts.su ./ST7789-STM32_STD_Lib/ST7789/st7789.cyclo ./ST7789-STM32_STD_Lib/ST7789/st7789.d ./ST7789-STM32_STD_Lib/ST7789/st7789.o ./ST7789-STM32_STD_Lib/ST7789/st7789.su

.PHONY: clean-ST7789-2d-STM32_STD_Lib-2f-ST7789

