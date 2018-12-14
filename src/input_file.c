#include "input_file.h"
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
struct ifile
{
	struct ifile* prev;
	struct ifile* next;
	bool empty;
	char* name;
	int fd;
};

struct ifile_list
{
	bool def;
	struct ifile* curr;
};

struct ifile_list ILIST = { .def=false, .curr=NULL };

bool is_initialized()
{
	return ILIST.def;
} 

static struct ifile* new_ifile()
{
	struct ifile* reply = malloc(sizeof(struct ifile));
	reply->prev = NULL;
	reply->next = NULL;
	reply->empty = true;
}

void init_ifile()
{
	if (is_initialized()) return;
	ILIST.def = true;
	ILIST.curr = new_ifile();
}

static void append_ifile(char* path)
{
	struct ifile* tmp = ILIST.curr;
	while(!tmp->empty && tmp->next != NULL) tmp = tmp->next;
	if(!tmp->empty)
	{
		tmp->next = new_ifile();
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	int fd;
	if((fd = open(path, O_RDONLY)) < 0)
	{
		//throw exception
	}
	else{
		tmp->name = path;
		tmp->fd = fd;
		tmp->empty = false;
	}
}

void add_ifile(char* path)
{
	if(!is_initialized())
	{
		init_ifile();
	}
	append_ifile(path);
}

void print_ifiles()
{
	struct ifile* tmp = ILIST.curr;
	if(!is_initialized()) return;
	while (tmp->prev != NULL) tmp = tmp->prev;
	while (tmp != NULL){
		printf("name: %s, fd: %d\n", tmp->name, tmp->fd);
		tmp = tmp->next;
	}
}