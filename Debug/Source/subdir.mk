################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/FindEliza.cpp \
../Source/Finder.cpp \
../Source/ImageHandler.cpp 

OBJS += \
./Source/FindEliza.o \
./Source/Finder.o \
./Source/ImageHandler.o 

CPP_DEPS += \
./Source/FindEliza.d \
./Source/Finder.d \
./Source/ImageHandler.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/opt/opencv3 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


