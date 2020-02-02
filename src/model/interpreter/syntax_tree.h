#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H
#include <gmodule.h>
//need a way to use glib

//names of the commands
typedef enum commands {WAIT, POKE, GOTO, IF_THEN, ENGINE, SHOOT} command_name; 

//expressions name 
//Remark : operators have been fuse with expressions' name for using operators as functions in our syntax tree
typedef enum expressions {INT, PEEK, RAND, CARDINAL, SELF, SPEED, STATE, GPSX, GPSY, ANGLE, TARGETX, TARGETY, DISTANCE, PLUS, MIN, TIME, DIV, MOD} expression_name; 

//comparaisons
typedef enum comparaisons { INF, INF_EG, EG, DIFF,SUP_EG, SUP } comparaison;

typedef struct function* function;

typedef struct command {
	command_name name;
	function f; 
	/*
		verification about f will be done at interpetation :
		Ex : GOTO number -> we will verify that nb_arguments = 1 of f and the argument is a number
	*/
} *command;

typedef struct expression {
	expression_name name;
	function f; /* Same thing */
} *expression;

//function that take expressions at arguments -> used by command and expression -> to know number and type of arguments look at the name of the command
struct function {
	int nb_arguments;
	GArray* arguments; //arguments have expression type
};






typedef struct condition {
	expression e1;
	comparaison c;
	expression e2;
} *condition;


typedef struct line 
{
	int number;
	command com;
} *line;

typedef struct program 
{
	line current;
	struct program* next_line; /* can be NULL */
} *program;


#endif