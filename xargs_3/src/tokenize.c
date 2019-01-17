#include "args.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define IS_SPACE(c) ((isascii(c) && isblank(c)) || c == '\n')

static struct line_buf{
	char* buf;
	size_t capacity;
	size_t size;
};

static void append_and_enlarge_line(struct line_buf* _line, char c);

void tokenize(struct cmd* _cmd, FILE* f){
	struct line_buf line = {.buf = NULL, .size = 0, .capacity=0};
	enum read_char_state
	{
		NORM = 0,
		SPACE = 1
	};
	enum read_char_state state = SPACE;
	char c;
	while((c = getc(f)) != EOF){
		switch(state){
			case SPACE:{
				if(IS_SPACE(c)) continue;
				else{
					state = NORM;
					line.size = 0;
				}
			}
			case NORM:{
				if(IS_SPACE(c)){
					append_and_enlarge_line(&line, '\0');
					push_argv(_cmd, line.buf);
					state = SPACE;
					continue;
				}
				append_and_enlarge_line(&line, c);
			}
		}
	}
	if(state == NORM){
		append_and_enlarge_line(&line, '\0');
		push_argv(_cmd, line.buf);
	}
	push_term(_cmd);
}

static void append_and_enlarge_line(struct line_buf* _line, char c){
	if(_line->capacity == 0){
		_line->buf = malloc(1);
		_line->capacity++;
	}else if(_line->size == _line->capacity){
		_line->buf = realloc(_line->buf, (_line->capacity*=2));
	}
	_line->buf[_line->size++] = c;
}