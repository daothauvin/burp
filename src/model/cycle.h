/*
	cycle management
*/

#include "game/arene.h"

/*

*/
short cycle(Arene a,int line[4],void* syntax_tree[4]);
char* getNextCommand(int idRobot);
char* getPreviousCommand(int idRobot);
char* getCurrentCommand(int idRobot);
