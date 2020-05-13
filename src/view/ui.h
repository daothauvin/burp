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
#include <sys/time.h>

#define LOG_SIZE 60

void  init();                           // Initialise the interface
int   quit();                           // End the inteface

void anim_begin();                      // Launch the begin animation
void end_screen(robot* robot);                // Launch the end screen and print the winner

void add_log(char* message);            // Add a message in the log
void add_action(char* action, int id);  // Add an action for a robot in the info tab

void updateArena(arena* arena);         // Update position and value of interface with arena data

