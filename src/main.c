#include "file.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

size_t BUFF_SIZE = 256;

int main(int argc, char* argv[]){
	errno = 0;
	if(argc < 2){
		fprintf(stderr, "file name expected\n");
		return 1;
	}
	struct f_stat* fstat = get_stat(argv[1]);
	if(errno){
		perror("Error while getting file stats");
		exit(EXIT_FAILURE);
	}
	printf("file size: %ld\n", fstat->_stat->st_size);
	if(read_file(fstat) < 0){
		perror("File read failure");
		exit(EXIT_FAILURE);
	}
	return 0;
}