################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cashier.cpp \
../customer.cpp \
../main.cpp \
../node.cpp \
../queue.cpp \
../serviceSimulator.cpp 

OBJS += \
./cashier.o \
./customer.o \
./main.o \
./node.o \
./queue.o \
./serviceSimulator.o 

CPP_DEPS += \
./cashier.d \
./customer.d \
./main.d \
./node.d \
./queue.d \
./serviceSimulator.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


