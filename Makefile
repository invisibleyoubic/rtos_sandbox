BUILD_DIR:=build
TOOLCHAIN:=cmake/arm-none-eabi.cmake

CMAKE:=cmake

.PHONY: all
all: build

.PHONY: conf
conf:
	$(CMAKE) \
		-B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
		-DCMAKE_BUILD_TYPE=Debug

.PHONY: build
build: conf
	$(CMAKE) --build $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# .PHONY: upload_ocd
# upload_ocd: build
# 	openocd \
# 		-f interface/stlink.cfg \
# 		-f target/stm32f4x.cfg \
# 		-c "program $(BUILD_DIR)/rtos_sandbox.elf verify reset exit"

.PHONY: upload_usb
upload_usb: build
	sudo dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D build/rtos_sandbox.bin

.PHONY: size
size: build
	arm-none-eabi-size $(BUILD_DIR)/blackpill.elf