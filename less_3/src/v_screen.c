#include "file.h"
#include <ncurses.h>

int cols, rows;

void screen_init(){
	initscr();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, rows, cols);
	noecho();
	cbreak();
}

void screen_exit(){
	endwin();
}

void resize_action(){
	getmaxyx(stdscr, rows, cols);
}

void print_file(struct file_meta* _meta){
	clear();
	printw("%s", _meta->buf + _meta->offset);
	refresh();
}
long sentence_prev(struct file_meta* _meta, int scr_w){
	if(_meta->offset == 0) return 0;
	if(_meta->buf[_meta->offset-1] != '\n') return _meta->offset - scr_w;
	int i = 1;
	while(_meta->offset-i-1 != -1 && _meta->buf[_meta->offset-i-1] != '\n') i++;
	return _meta->offset - i;
}

long sentence_next(struct file_meta* _meta, int scr_w){
	int i = 0;
	while(_meta->offset+i != _meta->size && 
		 _meta->buf[_meta->offset+i] != '\n' && i != scr_w-1) i++;
	return _meta->offset+i == _meta->size ? _meta->offset : _meta->offset+i+1;
}
