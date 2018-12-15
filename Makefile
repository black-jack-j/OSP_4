SOURCE = ./src
HEADERS = $(SOURCE)/headers
TARGET_DIR = ./bin
TARGET = less
LIBS = curses 
all:
	gcc ./src/*.c -l $(LIBS) -I $(HEADERS) -o $(TARGET_DIR)/$(TARGET)
