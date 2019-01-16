#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include "args.h"

extern void tokenize(struct cmd* _cmd, FILE* f);

int main(int argc, char* argv[]){
	char* command;
	struct cmd* cmd = new_cmd();
	if (argc < 2) push_argv(cmd, "/bin/echo");
	else {
		for(int i=1; i<argc;i++){
			push_argv(cmd, argv[i]);
		}
	}
	tokenize(cmd, stdin);
	exec_cmd(cmd);
	return 0;
}