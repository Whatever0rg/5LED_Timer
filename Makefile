BOARD?=arduino:avr:nano
PORT?=/dev/ttyUSB0
BUILD=build

.PHONY: defaulft lint all flash clean

default: lint compile flash clean

lint:
	-cpplint --extensions=ino --filter=-legal/copyright *.ino

compile:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD) ./

flash:
	arduino-cli upload --fqbn $(BOARD) --port $(PORT) --input-dir $(BUILD)

clean:
	rm -r build

debug:
	arduino-cli monitor -p /dev/ttyUSB0 -b arduino:avr:nano
