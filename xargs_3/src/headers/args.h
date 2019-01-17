#ifndef LAB4_ARGS
#define LAB4_ARGS

struct cmd
{
	int argc;
	char** argv;
	int argv_alloc;
	int offset;
	char* argbuf;
	long arg_max;
	int called;
};

struct cmd* new_cmd();
void push_term(struct cmd* _cmd);
void push_argv(struct cmd* _cmd, char* argv);
int exec_cmd(struct cmd* _cmd);

#endif