################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/portable/CCS/MSP430X/%.obj: ../FreeRTOS_Source/portable/CCS/MSP430X/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=none --include_path="C:/ti/ccs820/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/ETF5438A_HAL" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/F5XX_6XX_Core_Lib" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/FreeRTOS_Source/include" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/FreeRTOS_Source/portable/CCS/MSP430X" --include_path="C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/include" --advice:power=all --define=__MSP430F5438A__ --define=__SMALL_CODE_MODEL__ --define=__SMALL_DATA_MODEL__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/portable/CCS/MSP430X/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source/portable/CCS/MSP430X" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS_Source/portable/CCS/MSP430X/%.obj: ../FreeRTOS_Source/portable/CCS/MSP430X/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=none --include_path="C:/ti/ccs820/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/ETF5438A_HAL" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/F5XX_6XX_Core_Lib" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/FreeRTOS_Source/include" --include_path="C:/Users/fakultet/Desktop/sim-template/sim-template/FreeRTOS_Source/portable/CCS/MSP430X" --include_path="C:/ti/ccs820/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/include" --advice:power=all --define=__MSP430F5438A__ --define=__SMALL_CODE_MODEL__ --define=__SMALL_DATA_MODEL__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/portable/CCS/MSP430X/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source/portable/CCS/MSP430X" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


