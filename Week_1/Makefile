TARGET = run

SRCS = main.c user.c user.h logging.c logging.h accountManage.c accountManage.h

CC = gcc
CFLAGS = -Wall -Wextra

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
