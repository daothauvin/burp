/*
	The game
*/
#define _GNU_SOURCE
#include "game.h"


static char* setupName(char* filename, int id,char res[6]) {
    memset(res, '\0', 6);

    char fname[3];
    memset(fname, '\0', 3);
    strcpy(fname, res);

    if (strlen(filename) < 3) {
        snprintf(res, 6, "ROB_%d", id);
        return res;
    } else if (strlen(filename) == 3) {
        for (size_t i = 0; i < 3; i++) {
            fname[i] = toupper(filename[i]);
        }
        snprintf(res, 6, "%c%c%c_%d", fname[0], fname[1], fname[2], id);
        return res;
    } else {
        int compt = 0;
        for (size_t i = 0; i < strlen(filename); i++) {
            if (tolower(filename[i]) != 'a' && tolower(filename[i]) != 'e' && tolower(filename[i]) != 'i'
            && tolower(filename[i]) != 'o' && tolower(filename[i]) != 'u' && tolower(filename[i]) != 'y') {
                fname[compt] = toupper(filename[i]);
                compt++;
                if (compt == 3) break;
            }
        }
        if (compt != 3) {
            for (size_t i = 0; i < 3; i++) {
                fname[i] = toupper(filename[i]);
            }
            snprintf(res, 6, "%c%c%c_%d", fname[0], fname[1], fname[2], id);
            return res;
        }
        snprintf(res, 6, "%c%c%c_%d", fname[0], fname[1], fname[2], id);
        return res;    
    }
}

void game(Tree syntax_tree[4],char* robot_names[4])
{

	struct warning_message* message;
	char warning[100];
	arena *a = create_arena();
	char name[6];
	//                        X        Y      Angle  Spd   Id Name
	robot* r0 = create_robot(6.0,     6.0,     0.0,  0.0,  0, setupName(robot_names[0],0,name));
	robot* r1 = create_robot(6.0,     9995.0,  0.0,  0.0,  1, setupName(robot_names[1],1,name));
	robot* r2 = create_robot(9995.0,  9995.0,  0.0,  0.0,  2, setupName(robot_names[2],2,name));
	robot* r3 = create_robot(9995.0,  6.0,     0.0,  0.0,  3, setupName(robot_names[3],3,name));
	robot* robots[number_of_robots] = {r0,r1,r2,r3};
	for(int i = 0;i < number_of_robots;i++) {
		add_robot(a,robots[i]);
	}

	
	int line[4] = {0};
	int previousline[4] = {0};

	init();
	init_next(a,line,syntax_tree);
	anim_begin();

	for(int i = 0;i < get_nb_robot_arena(a); i++) {
		add_action(getNextCommand(i),i);
	}

	updateArena(a);
	while (cycle(a, line, syntax_tree)){
		
		for(int i = 0;i < get_nb_robot_arena(a); i++) {
			int id = get_robot_id(get_robot_index(a,i));
			add_action(getNextCommand(id),id);
		}
		memcpy(previousline,line,4*sizeof(int));
		if(!waitForInput())
			break;
		
		message = getWarnings();
		while(message != NULL) {
			snprintf(warning,100,"Robot %d - Line %d : %s",
				message->num_robot,previousline[message->num_robot],
				message->message);
			add_log(warning);
			message = message->next_message;
		}
		
		freeWarnings();
		updateArena(a);
	}
	

	
	if(get_nb_robot_arena(a) == 1) {

		
		end_screen(get_robot_index(a,0));
	}
	for(int j = 0;j < number_of_robots;j++) {
		for(int i = 0;i < get_nb_robot_arena(a); i++) {
			if(get_robot_index(a,i) == robots[j]) {
				robots[j] = NULL;
				break;
			}
		}
	}

	freeArena(&a);
	for(int j = 0;j < number_of_robots;j++) {
		if(NULL != robots[j])
			destroy_robot(&robots[j]);
	}
	
	quit();
}