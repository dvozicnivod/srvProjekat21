################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./adc_misc.obj" \
"./main.obj" \
"./util.obj" \
"./ETF5438A_HAL/hal_board.obj" \
"./ETF5438A_HAL/hal_led.obj" \
"./ETF5438A_HAL/ringbuffer.obj" \
"./ETF5438A_HAL/uart.obj" \
"./F5XX_6XX_Core_Lib/hal_PMM.obj" \
"./F5XX_6XX_Core_Lib/hal_UCS.obj" \
"./FreeRTOS_Source/event_groups.obj" \
"./FreeRTOS_Source/list.obj" \
"./FreeRTOS_Source/queue.obj" \
"./FreeRTOS_Source/tasks.obj" \
"./FreeRTOS_Source/timers.obj" \
"./FreeRTOS_Source/portable/CCS/MSP430X/port.obj" \
"./FreeRTOS_Source/portable/CCS/MSP430X/portext.obj" \
"./FreeRTOS_Source/portable/MemMang/heap_1.obj" \
"../lnk_msp430f5438a.cmd" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include ETF5438A_HAL/subdir_vars.mk
-include F5XX_6XX_Core_Lib/subdir_vars.mk
-include FreeRTOS_Source/subdir_vars.mk
-include FreeRTOS_Source/portable/CCS/MSP430X/subdir_vars.mk
-include FreeRTOS_Source/portable/MemMang/subdir_vars.mk
-include subdir_rules.mk
-include ETF5438A_HAL/subdir_rules.mk
-include F5XX_6XX_Core_Lib/subdir_rules.mk
-include FreeRTOS_Source/subdir_rules.mk
-include FreeRTOS_Source/portable/CCS/MSP430X/subdir_rules.mk
-include FreeRTOS_Source/portable/MemMang/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
sim-template.out \

EXE_OUTPUTS__QUOTED += \
"sim-template.out" \

BIN_OUTPUTS += \
sim-template.hex \

BIN_OUTPUTS__QUOTED += \
"sim-template.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "sim-template.out"

# Tool invocations
sim-template.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=none --advice:power=all --define=__MSP430F5438A__ --define=__SMALL_CODE_MODEL__ --define=__SMALL_DATA_MODEL__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 -z -m"sim-template.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccs820/ccsv8/ccs_base/msp430/include" -i"C:/ti/ccs820/ccsv8/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/lib" -i"C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="sim-template_linkInfo.xml" --use_hw_mpy=none --rom_model -o "sim-template.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

sim-template.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "sim-template.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "adc_misc.obj" "main.obj" "util.obj" "ETF5438A_HAL\hal_board.obj" "ETF5438A_HAL\hal_led.obj" "ETF5438A_HAL\ringbuffer.obj" "ETF5438A_HAL\uart.obj" "F5XX_6XX_Core_Lib\hal_PMM.obj" "F5XX_6XX_Core_Lib\hal_UCS.obj" "FreeRTOS_Source\event_groups.obj" "FreeRTOS_Source\list.obj" "FreeRTOS_Source\queue.obj" "FreeRTOS_Source\tasks.obj" "FreeRTOS_Source\timers.obj" "FreeRTOS_Source\portable\CCS\MSP430X\port.obj" "FreeRTOS_Source\portable\CCS\MSP430X\portext.obj" "FreeRTOS_Source\portable\MemMang\heap_1.obj" 
	-$(RM) "adc_misc.d" "main.d" "util.d" "ETF5438A_HAL\hal_board.d" "ETF5438A_HAL\hal_led.d" "ETF5438A_HAL\ringbuffer.d" "ETF5438A_HAL\uart.d" "F5XX_6XX_Core_Lib\hal_PMM.d" "F5XX_6XX_Core_Lib\hal_UCS.d" "FreeRTOS_Source\event_groups.d" "FreeRTOS_Source\list.d" "FreeRTOS_Source\queue.d" "FreeRTOS_Source\tasks.d" "FreeRTOS_Source\timers.d" "FreeRTOS_Source\portable\CCS\MSP430X\port.d" "FreeRTOS_Source\portable\MemMang\heap_1.d" 
	-$(RM) "FreeRTOS_Source\portable\CCS\MSP430X\portext.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

