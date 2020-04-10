#include "cycle.h"

static char* current[4] = {"None"};
static char* previous[4] = {"None"};
static char* next[4] = {"None"};

char* getCurrentCommand(int idRobot) {
	return current[idRobot];
}

char* getPreviousCommand(int idRobot) {
	return previous[idRobot];
}

char* getNextCommand(int idRobot) {
	return current[idRobot];
}

short cycle(Arene a,int line[4],void* syntax_tree[4]) {

	for(int i = 0; i < 4;i++) {
		previous[i] = current[i];
	}
	//lire script pour action suivante
	for(int i = 0; i < a -> nb_robots ;i++) {
		current[a -> list_robots[i] ->id] = getLine(syntax_tree[a -> list_robots[i] ->id],line[a -> list_robots[i] ->id]);
		line[a -> list_robots[i] ->id] = interprete(line[a -> list_robots[i] ->id],syntax_tree[i],a,a -> list_robots[i]);
		next[a -> list_robots[i] ->id] = getLine(syntax_tree[a -> list_robots[i] ->id],line[a -> list_robots[i] ->id]);
	}

	for(int i = 0; i < 4;i++) {
		current[i] = current[i];
	}

	//modifie positions : robot + missile
	for(int i = 0; i < a -> nb_robots ;i++) {
		update_pos_robot(a -> list_robots[i]);
	}
	for(int i = 0; i < a -> nb_missiles; i++) {
		update_pos_missile(a -> list_missile[i]);
	}

	//test collision
	for(int i = 0; i < a -> nb_robots; i++) {
		for(int j = i+1; j < a -> nb_robots; j++) {
			if(check_collision_robots(a -> list_robots[i],a -> list_robots[j])) {
				inflict_damage_from_collision(a -> list_robots[i],a -> list_robots[j]);
			}
		}
	}

	for(int i = 0; i < a -> nb_robots; i++) {
		for(int j = 0; j < a -> nb_missiles; j++) {
			collision_with_missiles(a -> list_robots[i],a -> list_missile[j]);
		}
	}

	//tue les robots morts
	for(int i = 0; i < a -> nb_robots ;i++) {
		if(a -> list_robots [i] -> health_points <= 0) {
			remove_robot(a,a -> list_robots[i]);
		}
	}
	
	for(int i = 0; i < a -> nb_missiles; i++) {
		if(will_explode(a -> list_missile[i]) < 0) {
			Point p = explode(a -> list_missile[i]);
			for(int i = 0; i < a -> nb_robots ;i++) {
				inflict_damage_from_missile(a -> list_robots[i],p);
			}
			remove_missile(a,a -> list_missile[i]);
		}
	}
	
	return a -> nb_robots != 0;

}
