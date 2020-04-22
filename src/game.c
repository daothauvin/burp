/*
	The game
*/

#include "game.h"

void game(Tree syntax_tree[4])
{
	arena *a = create_arena();
	init();
	robot* r1 = create_robot(5000,5000,0,100,0);
	robot* r2 = create_robot(0,10000.0,0,0,1);
	robot* r3 = create_robot(10000.0,10000.0,0,0,2);
	robot* r4 = create_robot(10000.0,0,0,0,3);
	add_robot(a,r1);
	add_robot(a,r2);
	add_robot(a,r3);
	add_robot(a,r4);
	
	int line[4] = {0};

	while (cycle(a, line, syntax_tree)){
		
		updateArena(a);
		for(int i = 0;i < get_nb_robot_arena(a); i++) {
			add_action(getNextCommand(i),i);
		}
		
		if(!waitForInput())
			break;
		//printf("one turn\n");
	}
	quit();
}