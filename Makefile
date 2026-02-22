CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
SRC = $(wildcard src/*.c)
TARGET = vigor

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f src/*.o $(TARGET)


