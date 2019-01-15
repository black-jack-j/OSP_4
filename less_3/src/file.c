#include "file.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int meta_crt(struct file_meta** _new, const char* filename){
	int fd = open(filename, O_RDONLY);
	if(fd < 0 ) return OPEN_ERROR;
	*_new = calloc(1, sizeof(struct file_meta));
	struct stat temp;
	fstat(fd, &temp);
	(*_new)->fd = fd;
	(*_new)->offset = 0;
	(*_new)->name = filename;
	(*_new)->size = temp.st_size;
	(*_new)->buf = NULL;
	return 0;
}

int meta_del(struct file_meta* _meta){
	int fd = _meta->fd;
	free(_meta->buf);
	free(_meta);
	if(close(fd) < 0) return CLOSE_ERROR;
	else return 0;
}

int meta_buf(struct file_meta* _meta){
	struct stat temp;
	fstat(_meta->fd, &temp);
	_meta->buf = calloc(_meta->size, sizeof(char));
	long off = 0;
	int rd;
	while((rd = read(_meta->fd, _meta->buf+off, temp.st_blksize)) > 0) off+=rd;
	if(rd < 0) return READ_ERROR;
	else return 0;
}

void meta_debuf(struct file_meta* _meta){
	lseek(_meta->fd, 0, SEEK_SET);
	free(_meta->buf);
}