#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

size_t BUFF_SIZE = 256;

int main(int argc, char* argv[]){
	int fd;
	char* buf = (char*)calloc(BUFF_SIZE, sizeof(char));
	ssize_t rb;
	if((fd = open(argv[1], O_RDONLY)) < 0) 
	{
		printf("'open' invokation error\n");
		return -1;
	}
	if((rb = read(fd, buf, BUFF_SIZE)) < 0)
	{
		printf("'read' invokation error\n");
		return -1;
	}else if(rb == 0)
	{
		printf("empty file\n");
		printf("Hello, World\n");
	}else
	{
		buf[rb] = '\0';
		printf("%s\n", buf);
	}
	close(fd);
	return 0;
}