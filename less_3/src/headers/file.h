#ifndef LAB4_FILE
#define LAB4_FILE

	#define OPEN_ERROR -1
	#define CLOSE_ERROR -1
	#define READ_ERROR -1
	struct file_meta {
		int fd;
		long offset;
		long size;
		char* buf;
		const char* name;
	};


	int meta_crt(struct file_meta** _new, const char* filename);
	int meta_del(struct file_meta* _meta);
	int meta_buf(struct file_meta* meta);
	void meta_debuf(struct file_meta* _meta);
#endif