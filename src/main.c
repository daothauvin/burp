#include <stdio.h>
#include "game.h"
#include "model/file_reader/syntax_analyse.h"

int main(int argc, char *argv[]) {
	
	if(argc == 5) {
		void* tab[4];
		tab[0] = init_file_tree(argv[1]);
		for(int i = 0; i < 4; i ++) {
			int fd = open(argv[i+1],O_RDONLY);
			if(fd <= 0 ) {
				fprintf(stderr,"%s : Does not exist",argv[i+1]);
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
