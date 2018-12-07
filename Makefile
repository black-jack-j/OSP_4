LIBS = curses 

all:
	gcc ./src/*.c -l $(LIBS) -o ./bin/less
