#include "cycle.h"

short cycle(Arene a,int line[4],void* syntax_tree[4]) {

	//lire script pour action suivante
	for(int i = 0; i < a -> nb_robots ;i++) {
		line[a -> list_robots[i] ->id] = interprete(line[a -> list_robots[i] ->id],syntax_tree[i],a,a -> list_robots[i]);
	}
	
	//modifie positions : robot + missile
	for(int i = 0; i < a -> nb_robots ;i++) {
		update_pos_robot(a -> list_missile[i]);
	}
	for(int i = 0; i < a -> nb_missiles; i++) {
		update_pos_missile(a -> list_missile[i]);
		remove_robot(a,a -> list_missile[i]);
	}
	
	for(int i = 0; i < a -> nb_missiles; i++) {
		if(check_distant(a -> list_missile[i]) < 0) {
			Point p = explode(a -> list_missile[i]);
			//fonction d'explosion autour
			remove_missile(a,a -> list_missile[i]);
		}
	}

	//test collision
	for(int i = 0; i < a -> nb_robots; i++) {
		for(int j = i+1; j < a -> nb_robots; j++) {
			if(collision_robots(a -> list_robots[i],a -> list_robots[j])) {
				inflict_damage_from_collision(a -> list_robots[i],a -> list_robots[j]);
			}
		}
	}
	
	for(int i = 0; i < a -> nb_robots; i++) {
		for(int j = 0; j < a -> nb_missiles; j++) {
			if(collision_with_missiles(a -> list_missile[i],a -> list_missile[j])) {
				Point p = explode(a -> list_missile[j]);
				//fonction d'explosion autour
			}

			
		}
	}
	
	//tue les robots morts
	for(int i = 0; i < a -> nb_robots ;i++) {
		if(a -> list_robots [i] -> health_points <= 0) {
			remove_robot(a,a -> list_missile[i]);
		}
	}
	
	
}