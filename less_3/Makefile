SOURCE = ./src
HEADERS = $(SOURCE)/headers
TARGET_DIR = ./bin
TARGET = less
LIBS = curses 
objects = less.o file.o v_screen.o workflow.o

target: $(objects)
	gcc -o $(TARGET_DIR)/$(TARGET) $(objects) -lncurses

less.o: $(SOURCE)/less.c
	gcc -c $< -I $(HEADERS)

file.o: $(SOURCE)/file.c
	gcc -c $< -I $(HEADERS)

v_screen.o: $(SOURCE)/v_screen.c
	gcc -c $< -I $(HEADERS)

workflow.o: $(SOURCE)/workflow.c
	gcc -c $< -I $(HEADERS)