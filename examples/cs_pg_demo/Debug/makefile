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


BUILD_ARTIFACT_NAME := cs_pg_example
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
BA_SIZE_DISPLAY += \
rv-size-display \

BA_OBJCOPY_OUTPUT += \
cs_pg_example.dat \


# All Target
all: main-build

# Main-build Target
main-build: cs_pg_example.elf secondary-outputs

# Tool invocations
cs_pg_example.elf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: RISC-V ELF GNU C linker'
	riscv32-unknown-elf-gcc -march=rv32ima_zicsr_zifencei_zca -mabi=ilp32 -mlittle-endian -O0 -g3 -nostartfiles -T "../cs_pg_example.ld" -o "cs_pg_example.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

rv-size-display: cs_pg_example.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Showing the size of executable'
	riscv32-unknown-elf-size -B "cs_pg_example.elf"
	@echo 'Finished building: $@'
	@echo ' '

cs_pg_example.dat: cs_pg_example.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: RISC-V ELF GNU objcopy'
	riscv32-unknown-elf-objcopy -O binary "cs_pg_example.elf"  "cs_pg_example.dat"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) cs_pg_example.dat cs_pg_example.elf rv-size-display
	-@echo ' '

secondary-outputs: $(BA_SIZE_DISPLAY) $(BA_OBJCOPY_OUTPUT)

.PHONY: all clean dependents main-build

-include ../makefile.targets
