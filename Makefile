BUILD_DIR:=build
TOOLCHAIN:=cmake/arm-none-eabi.cmake
DEBUG:=1
BUILD_TYPE:=Debug

CMAKE:=cmake

BAUD_RATE:=115200
TTY_DEVICE:=/dev/ttyUSB0

ifeq ($(DEBUG),0)
	BUILD_TYPE = Release
endif

.PHONY: all
all: build obj_copy

.PHONY: conf
conf:
	$(CMAKE) \
		-B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

.PHONY: obj_copy
obj_copy:
	arm-none-eabi-objcopy -O binary $(BUILD_DIR)/rtos_sandbox $(BUILD_DIR)/rtos_sandbox.bin

.PHONY: build
build: conf
	$(CMAKE) --build $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: upload_ocd
upload_ocd:
	openocd \
		-f /usr/share/openocd/scripts/interface/stlink.cfg \
		-f /usr/share/openocd/scripts/target/stm32f4x.cfg \
		-c "program build/rtos_sandbox verify reset exit"

.PHONY: reboot
reboot:
	openocd \
		-f /usr/share/openocd/scripts/interface/stlink.cfg \
		-f /usr/share/openocd/scripts/target/stm32f4x.cfg \
		-c "init" \
		-c "reset" \
		-c "exit"

.PHONY: upload_usb
upload_usb: obj_copy
	sudo dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D build/rtos_sandbox.bin

.PHONY: elfsize
elfsize:
	arm-none-eabi-size $(BUILD_DIR)/rtos_sandbox

.PHONY: binsize
binsize: obj_copy
	@echo "size is '$(shell ls -la ${BUILD_DIR}/rtos_sandbox.bin | awk '{print $$5}')' bytes"

.PHONY: disasm
disasm:
	arm-none-eabi-objdump -d $(BUILD_DIR)/rtos_sandbox

.PHONY: uart_monitor
uart_monitor:
	sudo minicom -D $(TTY_DEVICE) -b $(BAUD_RATE)

.PHONY: Debug
debug:
	arm-none-eabi-gdb \
		-iex 'set pagination off' \
		-iex 'set confirm off' \
		-iex 'target remote | openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg -c "gdb_port pipe; log_output openocd.log"' \
		-iex 'mon reset halt' \
		-ex "break main" \
		-ex "c" \
		-ex "tui reg general" \
		-iex 'add-symbol-file $(BUILD_DIR)/rtos_sandbox' \