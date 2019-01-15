#include <stdio.h>
#include <stdlib.h>

extern void process(int argc, char* argv[]);

int main(int argc, char *argv[])
{
	if(argc - 1 == 0){
		fprintf(stderr, "no file specified\n");
		exit(EXIT_FAILURE);
	}
	process(argc-1, argv+1);
	return 0;
}