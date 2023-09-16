CC = gcc
CFLAGS = -Wall -O2 -shared -fPIC
SRC_DIR = src
SOURCES = $(SRC_DIR)/get_gps.c
OBJECTS = $(SOURCES:.c=.o)
TARGET_DIR = $(SRC_DIR)

TARGET = $(TARGET_DIR)/get_gps.so

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lgps  # Link with the get_gps.so library

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)