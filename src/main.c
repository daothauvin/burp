#include <stdio.h>
#include "game.h"
#include "model/file_reader/syntax_analyse.h"
#include <errno.h>
#include <string.h>
int main(int argc, char *argv[]) {
	
	if(argc == 5) {
		Tree tab[4];
		for(int i = 0; i < 4; i ++) {
			int fd = open(argv[i+1],O_RDONLY);
			if(fd <= 0 ) {
				fprintf(stderr,"%s : %s",argv[i+1],strerror(errno));
				exit(0);
			} 
			close(fd);
			tab[i] = init_file_tree(argv[i+1]);
			if(tab[i] == NULL) {	
				fprintf(stderr,"%s : %s\n",argv[i+1],message_error());
				exit(0);
			}
		} 
	
		game(tab);
	}
}
