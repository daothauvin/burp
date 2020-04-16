/*
	The game
*/

#include "game.h"

void game(void* syntax_tree[4]){	
	Arene a = create_arene();
	init();
	Robot r1 = create_robot();
	Robot r2 = create_robot();
	Robot r3 = create_robot();
	Robot r4 = create_robot();
	initialize_robot(r1,0,0,0,0,0);
	initialize_robot(r2,0,9999.0,0,0,1);
	initialize_robot(r3,9999.0,9999.0,0,0,1);
	initialize_robot(r4,9999.0,0,0,0,4);
	add_robot(a,r1);
	add_robot(a,r2);
	add_robot(a,r3);
	add_robot(a,r4);
	
	int line[4] = {0};

	while (cycle(a, line, syntax_tree)){
		updateArena(a);
		waitForInput();
	}
	quit();
}