/*
	cycle management
*/

#include "game/arene.h"
#include "file_reader/interpreter.h"
#include "game/robot.h"
/*

*/
short cycle(arena* a,int line[4],Tree syntax_tree[4]);
char* getNextCommand(int idRobot);
char* getPreviousCommand(int idRobot);
char* getCurrentCommand(int idRobot);
void init_next(arena* a,int line[4],Tree syntax_tree[4]);
