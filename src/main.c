#include <stdio.h>
#include <fcntl.h>

extern struct ifile_list LIST;
extern void add_ifile(char* path);
extern void print_ifiles();

int main(int argc, char* argv[]){
	for(int i = 1; i < argc; i++){
		add_ifile(argv[i]);
	}
	print_ifiles();
	return 0;
}