/*
	The game
*/

#include "game.h"

void game(void *syntax_tree[4])
{
	arena *a = create_arena();
	init();
	int line[4] = {0};

	while (cycle(a, line, syntax_tree)){
		updateArena(a);
		waitForInput();
	}
	quit();
}