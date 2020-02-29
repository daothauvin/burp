#ifndef SYNTAX_ANALYSE_H
#define SYNTAX_ANALYSE_H
//for the tree
#include <gmodule.h>
//for scanner
#include <glib.h>
#include <glib/gprintf.h>
//arbre de syntaxe
#include "syntax_tree.h"

#include "string.h"

//do the syntax analyse of pathname and return it ( return NULL if error -> if message_error also at NULL then bug in the file opening )
void* init(char* pathname);

//NULL if no error else a message of error
char* message_error();

#endif