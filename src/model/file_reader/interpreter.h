#ifndef INTERPRETER_H
#define INTERPRETER_H
//for the tree
#include <gmodule.h>
#include <string.h>
#include <stdio.h>
#include "syntax_tree.h"
#include "../game/commands.h"

int interprete(int line, void* tree, void* arena,void* robot);

char* getLine(void* tree,int line);

//for test
void print(void* tree);


#endif