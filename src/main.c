#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

size_t BUFF_SIZE = 256;

extern struct ifile_list LIST;
extern void add_ifile(char* path);
extern void print_ifiles();

int main(int argc, char* argv[]){
	if(argc < 2){
		fprintf(stderr, "file name expected\n");
		return 1;
	}
	for(int i = 1; i < argc; i++){
		add_ifile(argv[i]);
	}
	print_ifiles();
	return 0;
}