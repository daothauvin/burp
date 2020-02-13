#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H
#include <gmodule.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//names of the commands
typedef enum commands {WAIT, POKE, GOTO, IF_THEN, ENGINE, SHOOT} command_name; 

//expressions name 
typedef enum expressions {PEEK, RAND, CARDINAL, SELF, SPEED, STATE, GPSX, GPSY, ANGLE, TARGETX, TARGETY, DISTANCE} expression_name; 

typedef enum operators {PLUS, MIN, TIME, DIV, MOD} operator_name;

//comparaisons 
typedef enum comparaisons { INF, INF_EG, EG, DIFF,SUP_EG, SUP } comparaison_name;

void init(char* pathname);
#endif