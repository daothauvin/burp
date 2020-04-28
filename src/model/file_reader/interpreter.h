#ifndef INTERPRETER_H
#define INTERPRETER_H
//for the tree
#include <gmodule.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "syntax_tree.h"
#include "../game/commands.h"
#include "../game/robot.h"
#include "../game/arene.h"
#include <fcntl.h>


struct warning_message {
	char message[60];
	int num_robot;
	struct warning_message* next_message;
};


struct warning_message* getWarnings();

void freeWarnings();

/*
    interprete the line [ line ] of the script,
    corresponding at the file where come from the syntax tree [ tree ] 
    controlling the robot [ robot ] in the context [ arena ] 
*/
int interprete(int line, Tree tree, arena *arena,robot *robot);

/*
  Return the command in a printable way of the command 
  executed at line [ line ] with the syntax tree [ tree ]
*/
char* getLine(Tree tree,int line);

/*
   Print syntax tree [ tree ] ( for debuging )
*/
void printTree(Tree tree);

#endif