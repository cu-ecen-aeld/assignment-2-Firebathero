CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = writer.c
OBJS = $(SRCS:.c=.o)
TARGET = writer

#Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)


# Cross-compilation support
cross_compile: CROSS_COMPILE=aarch64-none-linux-gnu-
cross_compile: clean all

