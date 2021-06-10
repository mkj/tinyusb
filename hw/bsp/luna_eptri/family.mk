SERIALPORT ?= /dev/ttyACM0
BAUDRATE   ?= 115200

CFLAGS += \
  -flto \
  -march=rv32i \
  -mabi=ilp32 \
  -nostdlib \
  -DCFG_TUSB_MCU=OPT_MCU_LUNA_EPTRI

# Cross Compiler for RISC-V
CROSS_COMPILE = riscv-none-embed-

# XXX
CROSS_COMPILE = riscv64-unknown-elf-

# All source paths should be relative to the top level.
LD_FILE = $(FAMILY_PATH)/riscv_simplesoc.ld

SRC_C += src/portable/luna/eptri/dcd_eptri.c

SRC_S += $(FAMILY_PATH)/crt0-simplesoc.S

INC += \
	$(TOP)/$(FAMILY_PATH)/include

# For freeRTOS port source
FREERTOS_PORT = RISC-V

program: $(BUILD)/$(PROJECT).bin
	echo -e "\nserialboot" | script -q /dev/null -c \
		"flterm --speed $(BAUDRATE) --kernel $< --kernel-addr 0x00040000 $(SERIALPORT)"

reprogram: $(BUILD)/$(PROJECT).bin
	apollo reconfigure
	echo -e "\nserialboot" | script -q /dev/null -c \
		"flterm --speed $(BAUDRATE) --kernel $< --kernel-addr 0x00040000 $(SERIALPORT)"
