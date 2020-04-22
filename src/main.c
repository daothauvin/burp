#include <stdio.h>
#include "game.h"
#include "model/file_reader/syntax_analyse.h"
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	srand(time(NULL));
	if(argc == 5) {
		Tree tab[4];
		for(int i = 0; i < 4; i ++) {
			int fd = open(argv[i+1],O_RDONLY);
			if(fd <= 0 ) {
				for(int j = 0;j < i;j++) {
					freeTree(tab[j]);
				}
				freeSyntaxAnalyseContest();
				fprintf(stderr,"%s : %s",argv[i+1],strerror(errno));
				exit(0);
			} 
			close(fd);
			tab[i] = init_file_tree(argv[i+1]);
			if(tab[i] == NULL) {	
				for(int j = 0;j < i;j++) {
					freeTree(tab[j]);
				}
				freeSyntaxAnalyseContest();
				fprintf(stderr,"%s : %s\n",argv[i+1],message_error());
				exit(0);
			}
		} 
	
		game(tab);

		for(int i = 0;i < 4;i++) {
			freeTree(tab[i]);
		}
		freeSyntaxAnalyseContest();
	}
}
