################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cs_pg_example.c \
../src/start.c \
../src/sys.c 

S_UPPER_SRCS += \
../src/entry.S 

C_DEPS += \
./src/cs_pg_example.d \
./src/start.d \
./src/sys.d 

OBJS += \
./src/cs_pg_example.o \
./src/entry.o \
./src/start.o \
./src/sys.o 

S_UPPER_DEPS += \
./src/entry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: RISC-V ELF GNU C compiler'
	riscv32-unknown-elf-gcc -MMD -MT  "$@" -march=$(ARCH) -mabi=$(ABI) -mlittle-endian -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: RISC-V ELF GNU C compiler'
	riscv32-unknown-elf-gcc -MMD -MT  "$@" -march=$(ARCH) -mabi=$(ABI) -mlittle-endian -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/cs_pg_example.d ./src/cs_pg_example.o ./src/entry.d ./src/entry.o ./src/start.d ./src/start.o ./src/sys.d ./src/sys.o

.PHONY: clean-src

