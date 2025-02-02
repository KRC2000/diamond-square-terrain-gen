# Compiler and linker
C = gcc
CFLAGS = -g
LDFLAGS = -L./ -lraylib -lm 
# LDFLAGS = -Lraylib-5.0_linux_amd64/lib -lm -lraylib --static 
# Project-specific settings
TARGET = main
SRCS = $(wildcard src/*.c)
HDRS = $(wildcard src/*.h)
OBJS = $(SRCS:src/%.c=build/%.o)

# Build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(C) -o $@ $(OBJS) $(LDFLAGS)

# Compile source files to object files
build/%.o: src/%.c $(HDRS)
	mkdir -p build
	$(C) -c $(CFLAGS) $< -o $@

run: $(TARGET)
	alacritty --hold --command ./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf build

.PHONY: all clean run
