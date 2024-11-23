cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "arm-none-eabi.cmake")

project(mcxn947)

set(TARGET ${CMAKE_PROJECT_NAME}.axf)

add_executable(${TARGET}
	"device/startup_mcxn947_cm33_core0.c"
	"device/system_MCXN947_cm33_core0.c"

	"src/main.c"
)

target_compile_definitions(${TARGET} PRIVATE
	__USE_CMSIS
	CPU_MCXN947VDF
	CPU_MCXN947VDF_cm33
	CPU_MCXN947VDF_cm33_core0
)

target_include_directories(${TARGET} PRIVATE
	"CMSIS_6/CMSIS/Core/Include"
	"device"
)

target_compile_options(${TARGET} PRIVATE
	-Os -g
	-std=c17
	-Wall
	-Wextra
	-Wpedantic

	-mthumb
	-mcpu=cortex-m33
	-mfpu=fpv5-sp-d16
	-mfloat-abi=hard

	-fno-common
	-fno-builtin
	-ffunction-sections
	-fdata-sections

	-specs=nosys.specs
)

target_link_options(${TARGET} PRIVATE
	-T ${CMAKE_SOURCE_DIR}/mcxn947.ld
	-Wl,-Map=minimal.map
	-Wl,--cref
	-Wl,--gc-sections
	-Wl,--sort-section=alignment

	-mthumb
	-mcpu=cortex-m33
	-mfpu=fpv5-sp-d16
	-mfloat-abi=hard

	-nostdlib
	-specs=nosys.specs
)

add_custom_command(
	TARGET ${TARGET} POST_BUILD
	COMMAND ${CMAKE_OBJDUMP} -j .text -D ${TARGET} > ${CMAKE_PROJECT_NAME}.dump
	COMMAND ${CMAKE_SIZE} ${TARGET}
)
