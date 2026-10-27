
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = phonebook
SOURCES = main.c PhoneBook.c
HEADERS = PhoneBook.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
