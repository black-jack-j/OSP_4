#ifndef LAB_FILE
#define LAB_FILE
	struct f_stat
	{
		struct stat* _stat;
		int offset;
		char* buf;
		char* name;
	};

	struct f_stat* get_stat(char* fname);

	int read_file(struct f_stat* file);
#endif