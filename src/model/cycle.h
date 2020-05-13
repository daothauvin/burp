/*
	cycle management
*/

#include "game/arene.h"
#include "file_reader/interpreter.h"
#include "game/robot.h"
#include "game/missile.h"

/**
*	Realise a cycle of the model.
*	change the result of getNextCommand.
*/
short cycle(arena* a,int line[4],Tree syntax_tree[4]);
/**
*	Return a string that correspond to the next command
*	that will be executed by the robot of id [ idRobot ]
*/
char* getNextCommand(int idRobot);
/**
* Initialise next commands before the execution of cycle.
*/
void init_next(arena* a,int line[4],Tree syntax_tree[4]);
