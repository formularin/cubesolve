BUILD := build
METHODS := $(BUILD)/methods
OBJECTS := $(BUILD)/cube.o $(BUILD)/main.o $(BUILD)/moves.o $(BUILD)/utils.o $(METHODS)/op_op.o
HEADERS := include/cube.hpp include/moves.hpp include/utils.hpp include/methods/op_op.hpp
CC := g++
CV := -std=c++11

all: compile
compile: setup $(OBJECTS)
	$(CC) $(CV) $(OBJECTS) -o bin/cubesolve

# object file targets:
$(BUILD)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CV) $< -c -o $@
$(METHODS)/%.o: src/methods/%.cpp $(HEADERS)
	$(CC) $(CV) $< -c -o $@

clean:
	rm $(BUILD)/*.o bin/cubesolve

setup:
	mkdir -p build bin build/methods

install:
	@install -m 0755 bin/cubesolve /usr/local/bin