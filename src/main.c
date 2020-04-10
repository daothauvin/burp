#include <stdio.h>
#include "game.h"
#include "model/file_reader/syntax_analyse.h"

int main(int argc, char *argv[]) {
	
	if(argc == 5) {
		void* tab[4] = {init_file_tree(argv[1]),init_file_tree(argv[2]),init_file_tree(argv[3]),init_file_tree(argv[4])};
		game(tab);
	}
}
