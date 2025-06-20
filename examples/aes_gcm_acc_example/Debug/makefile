################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := main
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
BA_SIZE_DISPLAY += \
rv-size-display \

BA_OBJCOPY_OUTPUT += \
main.dat \


# All Target
all: main-build

# Main-build Target
main-build: main.elf secondary-outputs

# Tool invocations
main.elf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: RISC-V ELF GNU C linker'
	riscv32-unknown-elf-gcc -march=$(ARCH) -mabi=$(ABI) -mlittle-endian -O0 -g3 -nostartfiles -T "../main.ld" -o "main.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

rv-size-display: main.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Showing the size of executable'
	riscv32-unknown-elf-size -B "main.elf"
	@echo 'Finished building: $@'
	@echo ' '

main.dat: main.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: RISC-V ELF GNU objcopy'
	riscv32-unknown-elf-objcopy -O binary "main.elf"  "main.dat"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) main.dat main.elf rv-size-display
	-@echo ' '

secondary-outputs: $(BA_SIZE_DISPLAY) $(BA_OBJCOPY_OUTPUT)

.PHONY: all clean dependents main-build

-include ../makefile.targets
