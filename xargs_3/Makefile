SOURCE = ./src
HEADERS = $(SOURCE)/headers
TARGET_DIR = ./bin
TARGET = xargs
objects = main.o args.o tokenize.o
all: $(objects)
	gcc -o $(TARGET_DIR)/$(TARGET) $(objects)
main.o: $(SOURCE)/main.c
	gcc -c $< -I $(HEADERS)
args.o: $(SOURCE)/args.c
	gcc -c $< -I $(HEADERS)
tokenize.o: $(SOURCE)/tokenize.c
	gcc -c $< -I $(HEADERS)
clean:
	rm *.o