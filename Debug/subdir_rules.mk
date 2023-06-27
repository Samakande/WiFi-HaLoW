################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -mthumb -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_00_98/source" -I"C:/ti/ccs1230/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/include/c++/9.2.1" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_00_98/source/ti/devices/cc13x2_cc26x2/driverlib" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_00_98/kernel/tirtos7/packages" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_00_98/source/ti/posix/gcc" -I"C:/ti/simplelink_cc13xx_cc26xx_sdk_7_10_00_98/source/ti" -I"C:/Users/Kudzai Samakande/Desktop/RF/Wifi Halow/802.11ah" -I"C:/ti/ccs1230/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/include" -Og -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -specs="nosys.specs" -fno-strict-aliasing --asm -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/Kudzai Samakande/Desktop/RF/Wifi Halow/802.11ah/Debug/syscfg"   -fno-threadsafe-statics $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


