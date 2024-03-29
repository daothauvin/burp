#include "cycle.h"

static char* next[4] = {"None"};

char* getNextCommand(int idRobot) {
	return next[idRobot];
}


void init_next(arena* a,int line[4],Tree syntax_tree[4]) {
	for(int i = 0; i < get_nb_robot_arena(a) ;i++) {
		next[get_robot_id(get_robot_index(a,i))] = getLine(
			syntax_tree[get_robot_id(get_robot_index(a,i))],
			line[get_robot_id(get_robot_index(a,i))]
		);
	}
}

short cycle(arena* a,int line[4],Tree syntax_tree[4]) {


	//tue les robots morts
	for (int i = 0; i < get_nb_robot_arena(a); i++)
	{
		if(get_robot_health_points(get_robot_index(a, i)) <= 0)
		{
			remove_robot(a, get_robot_index(a, i));
			i--;
		}
	}


	//lire script pour action suivante
	for(int i = 0; i < get_nb_robot_arena(a) ;i++) {
		if(get_waiting_time_robot(get_robot_index(a,i)) == 0) {
			line[get_robot_id(get_robot_index(a,i))] = interprete(
				line[get_robot_id(get_robot_index(a,i))],
				syntax_tree[get_robot_id(get_robot_index(a,i))],a,get_robot_index(a,i)
			);
		}
		if(get_waiting_time_robot(get_robot_index(a,i)) < 2) {
			next[get_robot_id(get_robot_index(a,i))] = getLine(
				syntax_tree[get_robot_id(get_robot_index(a,i))],
				line[get_robot_id(get_robot_index(a,i))]
			);
		}
	}

	//modifie positions : robot + missile
	for (int i = 0; i < get_nb_robot_arena(a); i++)
	{
		update_pos_robot(get_robot_index(a, i));
	}

	for (int i = 0; i < get_nb_missiles_arena(a); i++)
	{
		update_pos_missile(get_missile_index(a, i));
	}

	//test collision
	for(int i = 0; i < get_nb_robot_arena(a); i++) {
		for(int j = i+1; j < get_nb_robot_arena(a); j++) {
			if(check_collision_robots(
				get_robot_index(a,i),get_robot_index(a,j))) {
				inflict_damage_from_collision(
					get_robot_index(a,i),get_robot_index(a,j)
				);
			}
		}
	}

	for(int i = 0; i < get_nb_robot_arena(a); i++) {
		for(int j = 0; j < get_nb_missiles_arena(a); j++) {
			collision_with_missiles(
				get_robot_index(a,i),
				get_missile_index(a,j)
			);
		}
	}


	for (int i = 0; i < get_nb_missiles_arena(a); i++)
	{
		if (will_explode(get_missile_index(a,i)) == true)
		{
			point p;
			if(!explode(get_missile_index(a,i),&p)){
				continue;
			}
			for (int i = 0; i < get_nb_robot_arena(a); i++)
			{
				inflict_damage_from_missile(get_robot_index(a, i), p);
			}
			remove_missile(a, get_missile_index(a,i));
			i--;
		}
	}

	return get_nb_robot_arena(a) != 1;
}
