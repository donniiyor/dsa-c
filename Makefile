CC = clang

CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -g -Iinclude
LDFLAGS =

TARGET = app

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: run clean
