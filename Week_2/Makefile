TARGET = resolver

SRCS = main.c service.c service.h

CC = gcc
CFLAGS = -Wall -Wextra

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
