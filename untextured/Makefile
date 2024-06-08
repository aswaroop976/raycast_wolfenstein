# Variables
CC = gcc
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lm
SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXEC = raycast

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up the build
clean:
	rm -f $(OBJS) $(EXEC)

