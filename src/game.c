/*
	The game
*/
#define _GNU_SOURCE
#include "game.h"

void game(Tree syntax_tree[4])
{

	
	struct warning_message* message;
	char warning[100];
	arena *a = create_arena();
	//                        X        Y      Angle  Spd   Id
	robot* r0 = create_robot(6.0,     6.0,     0.0,  0.0,  0);
	robot* r1 = create_robot(6.0,     9995.0,  0.0,  0.0,  1);
	robot* r2 = create_robot(9995.0,  9995.0,  0.0,  0.0,  2);
	robot* r3 = create_robot(9995.0,  6.0,     0.0,  0.0,  3);

	add_robot(a,r0);
	add_robot(a,r1);
	add_robot(a,r2);
	add_robot(a,r3);
	
	int line[4] = {0};
	int previousline[4] = {0};
	init();
	init_next(a,line,syntax_tree);
	for(int i = 0;i < get_nb_robot_arena(a); i++) {
		add_action(getNextCommand(i),i);
	}
	updateArena(a);
	// anim_begin();
	while (cycle(a, line, syntax_tree)){
		point p;
		get_robot_pos(r0,&p);
		char slt[1000];
		snprintf(slt,1000,"ps x : %f , ps y : %f",p.x,p.y);
		add_log(slt);
		updateArena(a);

		for(int i = 0;i < get_nb_robot_arena(a); i++) {
			add_action(getNextCommand(i),i);
		}
		memcpy(previousline,line,4*sizeof(int));
		if(!waitForInput())
			break;
		
		message = getWarnings();
		while(message != NULL) {
			snprintf(warning,100,"Robot %d - Line %d : %s",message->num_robot,previousline[message->num_robot],message->message);
			add_log(warning);
			message = message->next_message;
		}
		
		freeWarnings();
	}
	quit();
}