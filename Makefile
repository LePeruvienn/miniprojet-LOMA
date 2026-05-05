# Wrapper for CMake

# New Makefile to that is an wrapper for cmake build system

BIN = bin
BUILD = build

compile: $(BUILD)
	cmake --build $(BUILD)

$(BUILD):
	cmake -B $(BUILD)

clean:
	rm -rf $(BUILD) $(BIN)
