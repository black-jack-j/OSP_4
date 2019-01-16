#ifndef LAB4_ARGS
#define LAB4_ARGS

struct cmd
{
	int argc;
	char** argv;
	int argv_alloc;
	char* argbuf;
	int offset;
};

struct cmd* new_cmd();
void push_term(struct cmd* _cmd);
void push_argv(struct cmd* _cmd, char* argv);
int exec_cmd(struct cmd* _cmd);

#endif