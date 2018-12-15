#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"
#include <unistd.h>
#include <sys/types.h>

struct f_stat* get_stat(char* fname){
	struct stat* _stat = malloc(sizeof(struct stat));
	stat(fname, _stat);
	struct f_stat* reply = malloc(sizeof(struct f_stat));
	reply->name = fname;
	reply->_stat = _stat;
	reply->offset = 0;
	return reply;
}

int read_file(struct f_stat* file){
	if(file == NULL) return -1;
	file->buf = malloc(file->_stat->st_size);
	size_t blksize = file->_stat->st_blksize || 16384;
	size_t offset = 0;
	int fd = open(file->name, O_RDONLY);
	int byte_read;
	while((byte_read = read(fd, file->buf+offset, blksize)) > 0){
		offset+=byte_read;
	}
	if(byte_read < 0) return -1;
	else {
		close(fd);
		return offset;
	}
}