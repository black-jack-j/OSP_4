#include "args.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


struct cmd* new_cmd(){
	struct cmd* _cmd = malloc(sizeof(struct cmd));
	long size = sysconf(_SC_ARG_MAX);
	_cmd->offset = 0;
	_cmd->argbuf = calloc(size, sizeof(char));
	_cmd->argv_alloc = 0;
	_cmd->argc = 0;
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
		_cmd->argv = realloc(_cmd->argv, _cmd->argv_alloc*2);
		_cmd->argv_alloc*=2;
	}
	strcpy(_cmd->argbuf+_cmd->offset, argv);
	_cmd->argv[_cmd->argc++] = _cmd->argbuf+_cmd->offset;
	_cmd->offset+=(strlen(argv)+1);
}

int exec_cmd(struct cmd* _cmd){
	return execvp(_cmd->argv[0], _cmd->argv);
}