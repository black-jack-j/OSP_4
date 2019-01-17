#include "args.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define HEADROOM 2048u
#define P_MAX 4096u

static size_t environment_size();
static size_t arg_size(struct cmd* _cmd);
static size_t max_size();

extern char** environ;

struct cmd* new_cmd(){
	struct cmd* _cmd = malloc(sizeof(struct cmd));
	_cmd->offset = 0;
	_cmd->arg_max = max_size();// - environment_size() - HEADROOM;
	_cmd->argbuf = calloc(_cmd->arg_max, 1);
	_cmd->argv_alloc = 0;
	_cmd->argc = 0;
	_cmd->called = 0;
	return _cmd;
}
void push_term(struct cmd* _cmd){
	if(_cmd->argc == _cmd->argv_alloc){
		_cmd->argv = realloc(_cmd->argv, ++_cmd->argv_alloc);
	}
	_cmd->argv[_cmd->argc] = NULL;
}

void push_argv(struct cmd* _cmd, char* argv){
	if(!_cmd->argv_alloc){
		_cmd->argv = malloc(sizeof(char*));
		_cmd->argv_alloc = 1;
	}else if(_cmd->argc == _cmd->argv_alloc){
		_cmd->argv = realloc(_cmd->argv, _cmd->argv_alloc*2*(sizeof(char*)));
		_cmd->argv_alloc*=2;
	}
	size_t argv_size = arg_size(_cmd);
	if(argv_size + strlen(argv) > _cmd->arg_max){
		pid_t pid;
		switch(pid = fork()){
			case 0:{
				push_term(_cmd);
				exec_cmd(_cmd);
				exit(0);
			}
			default:{
				_cmd->offset = (strlen(_cmd->argv[0])+1);
				_cmd->argc = 1;
				_cmd->called = 1;
				wait(NULL);
			}
		}
	}else _cmd->called = 0;
	strcpy(_cmd->argbuf+_cmd->offset, argv);
	_cmd->argv[_cmd->argc++] = _cmd->argbuf+_cmd->offset;
	_cmd->offset+=(strlen(argv)+1);
}

static size_t max_size(){
	size_t p_max_size = sysconf(_SC_ARG_MAX);
	size_t p_min_size = P_MAX;
	size_t def_size = 1024u * 128u;
	if(def_size > p_max_size){
		return p_max_size;
	}else if(def_size < p_min_size){
		return p_min_size;
	}
	return def_size;
}

int exec_cmd(struct cmd* _cmd){
	return execvp(_cmd->argv[0], _cmd->argv);
}

static size_t environment_size(){
	size_t len = 0;
	char** envp = environ;
	while(*envp) len+= (strlen(*envp++)+1);
	return len; 
}

static size_t arg_size(struct cmd* _cmd){
	size_t len = 0;
	for(int i = 0; i < _cmd->argc; i++){
		len += (strlen(_cmd->argv[i])+1);
	}
	return len;
}