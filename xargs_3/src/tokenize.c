#include "args.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define IS_SPACE(c) ((isascii(c) && isblank(c)) || c == '\n')

static int append_and_enlarge_line(char** str, char c, int size, int capacity);
static void new_empty_argv(struct cmd* _cmd);

void tokenize(struct cmd* _cmd, FILE* f){
	enum read_char_state
	{
		NORM = 0,
		SPACE = 1
	};
	enum read_char_state state = SPACE;
	char c, prev;
	int argc;
	int i = 0;
	int size = 0;
	while((c = getc(f)) != EOF){
		switch(state){
			case SPACE:{
				if(IS_SPACE(c)) continue;
				else{
					state = NORM;
					new_empty_argv(_cmd);
					argc = _cmd->argc;
					i = 0;
					size = 0;
				}
			}
			case NORM:{
				if(IS_SPACE(c)){
					append_and_enlarge_line(_cmd->argv+argc-1, '\0', i, size);
					_cmd->argv[argc-1] = realloc(_cmd->argv[argc-1], i+1);
					state = SPACE;
					continue;
				}
				size = append_and_enlarge_line(_cmd->argv+argc-1, c, i++, size);
			}
		}
	}
	if(state == NORM){
		append_and_enlarge_line(_cmd->argv+argc-1, '\0', i, size);
		_cmd->argv[argc-1] = realloc(_cmd->argv[argc-1], i+1);
	}
}

static int append_and_enlarge_line(char** str, char c, int size, int capacity){
	if(capacity == 0){
		*str = malloc(1);
		capacity++;
	}else if(size == capacity){
		*str = realloc(*str, (capacity*=2));
	}
	(*str)[size] = c;
	return capacity;
}

static void new_empty_argv(struct cmd* _cmd){
	if(_cmd->argv_alloc == 0){
		_cmd->argv = malloc(sizeof(char*));
		_cmd->argv_alloc = 1;
	}else if(_cmd->argc == _cmd->argv_alloc){
		_cmd->argv = realloc(_cmd->argv, _cmd->argv_alloc*2*sizeof(char*));
		_cmd->argv_alloc*=2;
	}
	_cmd->argv[_cmd->argc++] = NULL;
}