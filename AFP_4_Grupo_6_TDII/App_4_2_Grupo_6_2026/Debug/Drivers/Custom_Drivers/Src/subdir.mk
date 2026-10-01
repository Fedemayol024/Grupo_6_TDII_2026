################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Custom_Drivers/Src/driver_boton.c \
../Drivers/Custom_Drivers/Src/driver_boton_pal.c \
../Drivers/Custom_Drivers/Src/driver_led.c \
../Drivers/Custom_Drivers/Src/driver_led_pal.c \
../Drivers/Custom_Drivers/Src/driver_time.c \
../Drivers/Custom_Drivers/Src/nb_delay.c \
../Drivers/Custom_Drivers/Src/pal_tick_stm32.c 

OBJS += \
./Drivers/Custom_Drivers/Src/driver_boton.o \
./Drivers/Custom_Drivers/Src/driver_boton_pal.o \
./Drivers/Custom_Drivers/Src/driver_led.o \
./Drivers/Custom_Drivers/Src/driver_led_pal.o \
./Drivers/Custom_Drivers/Src/driver_time.o \
./Drivers/Custom_Drivers/Src/nb_delay.o \
./Drivers/Custom_Drivers/Src/pal_tick_stm32.o 

C_DEPS += \
./Drivers/Custom_Drivers/Src/driver_boton.d \
./Drivers/Custom_Drivers/Src/driver_boton_pal.d \
./Drivers/Custom_Drivers/Src/driver_led.d \
./Drivers/Custom_Drivers/Src/driver_led_pal.d \
./Drivers/Custom_Drivers/Src/driver_time.d \
./Drivers/Custom_Drivers/Src/nb_delay.d \
./Drivers/Custom_Drivers/Src/pal_tick_stm32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Custom_Drivers/Src/%.o Drivers/Custom_Drivers/Src/%.su Drivers/Custom_Drivers/Src/%.cyclo: ../Drivers/Custom_Drivers/Src/%.c Drivers/Custom_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F439xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Carlitoz MF/Documents/Microcontroladores/Tecnicas_Digitales2-2026/AFP_4_Grupo_6_TDII_2026/App_4_2_Grupo_6_2026/Drivers/Custom_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Custom_Drivers-2f-Src

clean-Drivers-2f-Custom_Drivers-2f-Src:
	-$(RM) ./Drivers/Custom_Drivers/Src/driver_boton.cyclo ./Drivers/Custom_Drivers/Src/driver_boton.d ./Drivers/Custom_Drivers/Src/driver_boton.o ./Drivers/Custom_Drivers/Src/driver_boton.su ./Drivers/Custom_Drivers/Src/driver_boton_pal.cyclo ./Drivers/Custom_Drivers/Src/driver_boton_pal.d ./Drivers/Custom_Drivers/Src/driver_boton_pal.o ./Drivers/Custom_Drivers/Src/driver_boton_pal.su ./Drivers/Custom_Drivers/Src/driver_led.cyclo ./Drivers/Custom_Drivers/Src/driver_led.d ./Drivers/Custom_Drivers/Src/driver_led.o ./Drivers/Custom_Drivers/Src/driver_led.su ./Drivers/Custom_Drivers/Src/driver_led_pal.cyclo ./Drivers/Custom_Drivers/Src/driver_led_pal.d ./Drivers/Custom_Drivers/Src/driver_led_pal.o ./Drivers/Custom_Drivers/Src/driver_led_pal.su ./Drivers/Custom_Drivers/Src/driver_time.cyclo ./Drivers/Custom_Drivers/Src/driver_time.d ./Drivers/Custom_Drivers/Src/driver_time.o ./Drivers/Custom_Drivers/Src/driver_time.su ./Drivers/Custom_Drivers/Src/nb_delay.cyclo ./Drivers/Custom_Drivers/Src/nb_delay.d ./Drivers/Custom_Drivers/Src/nb_delay.o ./Drivers/Custom_Drivers/Src/nb_delay.su ./Drivers/Custom_Drivers/Src/pal_tick_stm32.cyclo ./Drivers/Custom_Drivers/Src/pal_tick_stm32.d ./Drivers/Custom_Drivers/Src/pal_tick_stm32.o ./Drivers/Custom_Drivers/Src/pal_tick_stm32.su

.PHONY: clean-Drivers-2f-Custom_Drivers-2f-Src

