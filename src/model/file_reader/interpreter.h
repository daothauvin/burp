#ifndef INTERPRETER_H
#define INTERPRETER_H
//for the tree
#include <gmodule.h>
#include <string.h>
#include <stdio.h>
#include "syntax_tree.h"
#include "../game/commands.h"
#include "../game/robot.h"
#include "../game/arene.h"

/*
    interprete the line [ line ] of the script,
    corresponding at the file where come from the syntax tree [ tree ] 
    controlling the robot [ robot ] in the context [ arena ] 
*/
int interprete(int line, Tree tree, Arene arena,Robot robot);

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