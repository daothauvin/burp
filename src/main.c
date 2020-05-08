#include "game.h"
#include "model/file_reader/syntax_analyse.h"
/// \cond
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
/// \endcond
int main(int argc, char *argv[]) {
	char* name_files[4];
	for(int i = 0;i<4;i++) {
		name_files[i] = argv[i+1];
		char* name = strrchr(name_files[i],'/') + 1;
		if(name != NULL) name_files[i] = name;
	}
	srand(time(NULL));
	if(argc == 5) {
		Tree tab[4];
		for(int i = 0; i < 4; i ++) {
			int fd = open(argv[i+1],O_RDONLY);
			if(fd <= 0 ) {
				for(int j = 0;j < i;j++) {
					freeTree(tab[j]);
				}
				fprintf(stderr,"%s : %s\n",argv[i+1],strerror(errno));
				freeSyntaxAnalyseContest();
				exit(0);
			} 
			close(fd);
			tab[i] = init_file_tree(argv[i+1]);
			if(tab[i] == NULL) {	
				for(int j = 0;j < i;j++) {
					freeTree(tab[j]);
				}
				
				fprintf(stderr,"%s : %s\n",argv[i+1],message_error());
				freeSyntaxAnalyseContest();
				exit(0);
			}
		} 
	
		game(tab,name_files);

		for(int i = 0;i < 4;i++) {
			freeTree(tab[i]);
		}
		freeSyntaxAnalyseContest();
	}
}
