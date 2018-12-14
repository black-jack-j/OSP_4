SOURCE = ./src
HEADERS = $(SOURCE)/headers
TARGET_DIR = ./bin
TARGET = less
all:
	gcc ./src/*.c -I $(HEADERS) -o $(TARGET_DIR)/$(TARGET)