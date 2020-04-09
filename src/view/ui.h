/** 
 *         - ui.c & ui.h supply functions to use the textual interface -
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "../model/game/robot.h"
#include "../model/game/missile.h"
#include "../model/game/arene.h"
#include "../define.h"


void init();
void anim_begin();

void add_log(char* message);
void add_action(char* action, int id);

void printRobot(Robot robot);
void printInfoRobot(Robot robot);
void printRocket(Missile rocket);

void updateArena(Arene arena);
