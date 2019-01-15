#include "ncurses.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static struct file_meta** _meta;
static int len;
static int off = 0;
extern long sentence_next(struct file_meta* _meta, int scr_w);
extern long sentence_prev(struct file_meta* _meta, int scr_w);
extern void screen_init();
extern void screen_exit();
extern void print_file(struct file_meta* _meta);
extern void resize_action();
extern int cols, rows;

void process(int argc, char* argv[]){
	len = argc;
	_meta = calloc(argc, sizeof(struct file_meta*));
	for(int i=0; i<argc;i++){
		if(meta_crt(&_meta[i], argv[i]) == OPEN_ERROR){
			perror("can't open file");
			exit(EXIT_FAILURE);
		}
	}
	meta_buf(_meta[0]);
	screen_init();
	print_file(_meta[0]);
	int k;
	while((k = getch()) != 'q'){
		switch((unsigned int)k){
			case 'j':{
				_meta[0]->offset = sentence_next(_meta[0], cols);
				fprintf(stderr, "offset: %ld\n", _meta[0]->offset);
				print_file(_meta[0]);
				break;
			}
			case 'k':{
				_meta[0]->offset = sentence_prev(_meta[0], cols);
				fprintf(stderr, "offset: %ld\n", _meta[0]->offset);
				print_file(_meta[0]);
				break;
			}
			case KEY_RESIZE:{
				resize_action();
				fprintf(stderr, "resize\n");
				print_file(_meta[0]);
				break;
			}
		}
	}
	screen_exit();
}