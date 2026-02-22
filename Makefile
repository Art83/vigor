CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
SRC = $(wildcard src/*.c)
TARGET = vigor
PREFIX = /usr/local

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Deployment
install: all
	@echo "Installing $(TARGET) to $(PREFIX)/bin"
	install -m 755 $(TARGET) $(PREFIX)/bin/
uninstall:
	@echo "Removing $(TARGET) from $(PREFIX)/bin"
	rm -f $(PREFIX)/bin/$(TARGET)


clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean install uninstall
