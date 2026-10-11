CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g

TARGET = cemulator

SRCS = $(wildcard src/*.c)

OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf obj $(TARGET)

.PHONY: all clean run