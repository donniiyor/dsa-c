CC := clang

CFLAGS := \
	-std=c23 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wconversion \
	-Wshadow \
	-Werror \
	-g \
	-Iinclude

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

TARGET := build/app

.PHONY: all clean run format tidy

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p build
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

format:
	clang-format -i src/*.c include/*.h examples/*.c tests/*.c

tidy:
	clang-tidy src/*.c -- -Iinclude

clean:
	rm -rf buildPHONY: run clean
