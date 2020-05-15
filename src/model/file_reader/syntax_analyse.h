#ifndef SYNTAX_ANALYSE_H
#define SYNTAX_ANALYSE_H
//for the tree
#include <gmodule.h>
//for scanner
#include <glib.h>
#include <glib/gprintf.h>

//arbre de syntaxe
#include "syntax_tree.h"

//other
#include <string.h>
#include <gmodule.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>

/**
*    Do the syntax analyse of the file [ pathname ] and return it 
*    return NULL if an error occured, 
*    if message_error is also at NULL then the bug is a file opening error
*/
Tree init_file_tree(char* pathname);

/**
*    if an error occured return it if not, return NULL
*/
char* message_error();

/**
*    Free the context of the syntax analyse, excepted syntax tree
*    Todo after last syntax analyse
*/
void freeSyntaxAnalyseContest();
/**
*    free a syntax tree
*/
void freeTree(Tree t);
#endif