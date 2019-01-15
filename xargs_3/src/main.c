#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
	char* command;
	if (argc < 2) command = "echo";
	else command = argv[1];
	char* line = NULL;
	char cmd[255];
	size_t size;
	while(getline(&line, &size, stdin) != -1){
		sprintf(cmd, "%s %s\n", command, line);
		system(cmd);
	}
	return 0;
}