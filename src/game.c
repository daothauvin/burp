/*
	The game
*/

#include "game.h"

void game(void *syntax_tree[4])
{
	arena *a = create_arena();
	init();
	Robot r1 = create_robot();
	Robot r2 = create_robot();
	Robot r3 = create_robot();
	Robot r4 = create_robot();
	initialize_robot(r1,5000,5000,0,100,0);
	initialize_robot(r2,0,10000.0,0,0,1);
	initialize_robot(r3,10000.0,10000.0,0,0,2);
	initialize_robot(r4,10000.0,0,0,0,3);
	add_robot(a,r1);
	add_robot(a,r2);
	add_robot(a,r3);
	add_robot(a,r4);
	
	int line[4] = {0};

	while (cycle(a, line, syntax_tree)){
		
		updateArena(a);
		for(int i = 0;i < a ->nb_robots; i++) {
			add_action(getNextCommand(i),i);
		}
		
		if(!waitForInput())
			break;
		//printf("one turn\n");
	}
	quit();
}