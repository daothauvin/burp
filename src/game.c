/*
	The game
*/

#include "game.h"

void game(Tree syntax_tree[4])
{
	arena *a = create_arena();

	//                        X        Y      Angle  Spd   Id
	robot* r0 = create_robot(0.0,     0.0,     0.0,  0.0,  0);
	robot* r1 = create_robot(0.0,     9999.0,  0.0,  0.0,  1);
	robot* r2 = create_robot(9999.0,  9999.0,  0.0,  0.0,  2);
	robot* r3 = create_robot(9999.0,  0.0,     0.0,  0.0,  3);

	add_robot(a,r0);
	add_robot(a,r1);
	add_robot(a,r2);
	add_robot(a,r3);
	
	int line[4] = {0};
	init();
	updateArena(a);
	// anim_begin();
	while (cycle(a, line, syntax_tree)){
		updateArena(a);
		for(int i = 0;i < get_nb_robot_arena(a); i++) {
			add_action(getNextCommand(i),i);
		}
		if(!waitForInput())
			break;
	}
	quit();
}