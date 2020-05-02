/** 
 *         - ui.c & ui.h supply functions to use the textual interface -
 */

#ifndef UI_H
#define UI_H
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "../model/game/robot.h"
#include "../model/game/missile.h"
#include "../model/game/arene.h"
#include "../define.h"
#include "../game.h"
#include <sys/time.h>

#define LOG_SIZE 60

void  init();         // Initialise the interface
void  anim_begin();   // Launch the begin animation
short waitForInput(); // Check for user keyboard input
int   quit();         // End the inteface

void add_log(char* message); // Add a message in the log
void add_action(char* action, int id); // Add an action for a robot in the info tab

void updateArena(arena* arena); // Update position and value of interface with arena data

#endif