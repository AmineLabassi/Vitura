# Updated Makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I/usr/include/SDL
LDFLAGS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm

# Targets
TARGET = game
OBJECTS = main.o enigme.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
