/*
	The game
*/

#include "game.h"

void game(void* syntax_tree[4]){	
	Arene a = create_arene();
	init();
	int line[4] = {0};

	while(cycle(a,line,syntax_tree)){
		for(int i = 0; i < a -> nb_robots; i++) 
			updateArena(a);
	}
}