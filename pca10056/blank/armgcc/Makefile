PROJECT_NAME     := test_example_pca10056
TARGETS          := nrf52840_xxaa
OUTPUT_DIRECTORY := _build

SDK_ROOT := ../../../../../..
PROJ_DIR := ../../..

$(OUTPUT_DIRECTORY)/nrf52840_xxaa.out: \
  LINKER_SCRIPT  := test_example_gcc_nrf52.ld

# Source files common to all targetss
SRC_FILES += \
  $(SDK_ROOT)/components/libraries/fifo/app_fifo.c \
  $(SDK_ROOT)/components/boards/boards.c \
  $(SDK_ROOT)/components/libraries/log/src/nrf_log_backend_serial.c \
  $(SDK_ROOT)/components/libraries/log/src/nrf_log_frontend.c \
  $(SDK_ROOT)/components/libraries/util/app_error.c \
  $(SDK_ROOT)/components/libraries/util/app_error_weak.c \
  $(SDK_ROOT)/components/libraries/util/app_util_platform.c \
  $(SDK_ROOT)/components/libraries/util/nrf_assert.c \
  $(SDK_ROOT)/components/libraries/strerror/nrf_strerror.c \
  $(SDK_ROOT)/components/libraries/memobj/nrf_memobj.c \
  $(PROJ_DIR)/unity_fw/simple_uart.c \
  $(PROJ_DIR)/unity_fw/app_test_runner.c \
  $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_uarte.c \
  $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_uart.c \
  $(PROJ_DIR)/unity_fw/unity.c 
  # $(SDK_ROOT)/components/toolchain/systemz_nrf52840.c \
  $(SDK_ROOT)/components/toolchain/gcc/gcc_startup_nrf52840.S \
  # $(SDK_ROOT)/external/segger_rtt/RTT_Syscalls_GCC.c \
  # $(SDK_ROOT)/external/segger_rtt/SEGGER_RTT.c \
  # $(SDK_ROOT)/external/segger_rtt/SEGGER_RTT_printf.c \
 # $(SDK_ROOT)/components/drivers_nrf/common/nrf_drv_common.c 
  # $(SDK_ROOT)/components/drivers_nrf/uart/nrf_drv_uart.c \
# Include folders common to all targets
INC_FOLDERS += \
  $(PROJ_DIR)/unity_fw \
  $(PROJ_DIR) \
  ../config 

INC_FOLDERS += $(SDK_ROOT)/components/libraries
INC_FOLDERS += $(SDK_ROOT)/components/libraries/fifo
INC_FOLDERS += $(SDK_ROOT)/components/libraries/balloc
INC_FOLDERS += $(SDK_ROOT)/components/libraries/memobj
INC_FOLDERS += $(SDK_ROOT)/components/libraries/strerror
INC_FOLDERS += $(SDK_ROOT)/components/libraries/delay
INC_FOLDERS += $(SDK_ROOT)/components/libraries/pwr_mgmt
INC_FOLDERS += $(SDK_ROOT)/components/libraries/button
INC_FOLDERS += $(SDK_ROOT)/components/libraries/bsp
INC_FOLDERS += $(SDK_ROOT)/components/libraries/uart
INC_FOLDERS += $(SDK_ROOT)/components/libraries/atomic
INC_FOLDERS += $(SDK_ROOT)/components/libraries/sortlist
INC_FOLDERS += $(SDK_ROOT)/components/libraries/pwm
INC_FOLDERS += $(SDK_ROOT)/components/libraries/block_dev
INC_FOLDERS += $(SDK_ROOT)/components/libraries/block_dev/sdc
INC_FOLDERS += $(SDK_ROOT)/components/libraries/sdcard
INC_FOLDERS += $(SDK_ROOT)/components/libraries/log
INC_FOLDERS += $(SDK_ROOT)/components/libraries/log/src
INC_FOLDERS += $(SDK_ROOT)/components/libraries/timer
INC_FOLDERS += $(SDK_ROOT)/components/libraries/experimental_section_vars
INC_FOLDERS += $(SDK_ROOT)/components/libraries/util
INC_FOLDERS += $(SDK_ROOT)/components
INC_FOLDERS += $(SDK_ROOT)/components/boards
INC_FOLDERS += $(SDK_ROOT)/components/toolchain/cmsis/include/
INC_FOLDERS += $(SDK_ROOT)/components/toolchain/cmsis
INC_FOLDERS += $(SDK_ROOT)/components/toolchain/gcc
INC_FOLDERS += $(SDK_ROOT)/components/toolchain
INC_FOLDERS += $(SDK_ROOT)/components/ble
INC_FOLDERS += $(SDK_ROOT)/components/ble/ble_link_ctx_manager
INC_FOLDERS += $(SDK_ROOT)/components/ble/ble_services/ble_nus
INC_FOLDERS += $(SDK_ROOT)/components/ble/ble_services
INC_FOLDERS += $(SDK_ROOT)/components/ble/nrf_ble_qwr
INC_FOLDERS += $(SDK_ROOT)/components/ble/nrf_ble_gatt
INC_FOLDERS += $(SDK_ROOT)/components/ble/ble_advertising
INC_FOLDERS += $(SDK_ROOT)/components/ble/common
INC_FOLDERS += $(SDK_ROOT)/components/softdevice
INC_FOLDERS += $(SDK_ROOT)/components/softdevice/common
INC_FOLDERS += $(SDK_ROOT)/components/softdevice/s140
INC_FOLDERS += $(SDK_ROOT)/components/softdevice/s140/headers
INC_FOLDERS += $(SDK_ROOT)/components/libraries/ringbuf/
INC_FOLDERS += $(SDK_ROOT)/components/softdevice/s140/headers/nrf52/
INC_FOLDERS += $(SDK_ROOT)/external
INC_FOLDERS += $(SDK_ROOT)/external/fprintf
INC_FOLDERS += $(SDK_ROOT)/external/fatfs
INC_FOLDERS += $(SDK_ROOT)/external/fatfs/port
INC_FOLDERS += $(SDK_ROOT)/external/fatfs/src/
INC_FOLDERS += $(SDK_ROOT)/modules
INC_FOLDERS += $(SDK_ROOT)/modules
INC_FOLDERS += $(SDK_ROOT)/integration/nrfx
INC_FOLDERS += $(SDK_ROOT)/integration/nrfx/legacy
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx/drivers/include
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx/hal
INC_FOLDERS += $(SDK_ROOT)/modules/nrfx/mdk
# Libraries common to all targets
LIB_FILES += \

# C flags common to all targets
CFLAGS += -DBOARD_PCA10056
CFLAGS += -DCONFIG_GPIO_AS_PINRESET
CFLAGS += -DNRF52840_XXAA
CFLAGS += -DUNITY_EXCLUDE_DOUBLE
CFLAGS += -DUNITY_EXCLUDE_FLOAT
CFLAGS += -DUNITY_ON_TARGET
CFLAGS += -DUNITY_TO_CUNIT
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb -mabi=aapcs
CFLAGS +=  -Wall -Werror -O3 -g3
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# keep every function in separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 

# C++ flags common to all targets
CXXFLAGS += \

# Assembler flags common to all targets
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DBOARD_PCA10056
ASMFLAGS += -DCONFIG_GPIO_AS_PINRESET
ASMFLAGS += -DNRF52840_XXAA
ASMFLAGS += -DUNITY_EXCLUDE_DOUBLE
ASMFLAGS += -DUNITY_EXCLUDE_FLOAT
ASMFLAGS += -DUNITY_ON_TARGET
ASMFLAGS += -DUNITY_TO_CUNIT

# Linker flags
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m4
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys


.PHONY: $(TARGETS) default all clean help flash 

# Default target - first one defined
default: nrf52840_xxaa

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo 	nrf52840_xxaa

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc

include $(TEMPLATE_PATH)/Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

# Flash the program
flash: $(OUTPUT_DIRECTORY)/nrf52840_xxaa.hex
	@echo Flashing: $<
	nrfjprog --program $< -f nrf52 --sectorerase
	nrfjprog --reset -f nrf52

erase:
	nrfjprog --eraseall -f nrf52
