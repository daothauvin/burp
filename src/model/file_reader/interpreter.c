/*
	Interprete a branch of the syntax tree given by syntax_analyse
	use the commands file of the game model
*/

#include "interpreter.h"

static void printnode(GNode *node, gpointer data);

/*

	Test

*/
//return 0 if a number, or 1 if a tag given in syntax_analyse and can have no child in the syntax tree 
//( INF, INF_EG, EG, DIFF, SUP_EG, EG, CARDINAL, SELF, SPEED, PLUS, MINUS, TIME, DIV, MOD for now ) 
static short isTag(void* data) {
	return 
		memcmp(INF,data,sizeof(INF)) == 0 || memcmp(INF_EG,data,sizeof(INF_EG)) == 0 || memcmp(EG,data,sizeof(EG)) == 0 || memcmp(DIFF,data,sizeof(DIFF)) == 0 || memcmp(SUP_EG,data,sizeof(SUP_EG)) == 0 || memcmp(EG,data,sizeof(EG)) == 0
		|| memcmp(PLUS,data,sizeof(PLUS)) == 0 || memcmp(MINUS,data,sizeof(MINUS)) == 0 || memcmp(TIME,data,sizeof(TIME)) == 0 || memcmp(DIV,data,sizeof(DIV)) == 0 || memcmp(MOD,data,sizeof(MOD)) == 0
		|| memcmp(CARDINAL,data,sizeof(CARDINAL)) == 0 || memcmp(SELF,data,sizeof(SELF)) == 0 || memcmp(SPEED,data,sizeof(SPEED)) == 0;
}

void print(void* tree) {
	int i = 0;
	g_node_children_foreach (tree,G_TRAVERSE_ALL,&printnode,&i);
	printf("number of node : %d\n",i);
}

static void printnode(GNode *node, gpointer data) {
	int* number = data;
	*number += 1;
	char* nodedata = node -> data;
	if(G_NODE_IS_LEAF(node) && !isTag(nodedata)) {
	
		int* nodeint = node -> data;
		printf("- currrent:int = %d\n",*nodeint);
	}else {
		printf("- currrent:tag = %s\n",nodedata);
		
	}
	char* fatherdata = (node -> parent) -> data;
	printf("  father:tag = %s\n",fatherdata);

	//printf("father: %s\n",);
	g_node_children_foreach (node,G_TRAVERSE_ALL,&printnode,data);
}

/*

	Interpretation

*/

static int numberline(void* line) {
	return *((int*) g_node_first_child(line) -> data);
}

static void searchline(GNode *node, gpointer data) {
	GNode *search = data;
	if(memcmp(LINE,search -> data,sizeof(LINE)) == 0) {
		return;
	}
	if(numberline(node) == *((int*) search -> data)) {
		search -> data = node -> data;
		search -> next = node -> next;
		search -> prev = node -> prev;
		search -> parent = node -> parent;
		search -> children = node -> children;
	}
}

int interprete(int line, void* tree, void* arena) {
	while(1) {
		GNode* node = g_node_new (&line);
		g_node_children_foreach (tree, G_TRAVERSE_ALL,searchline,node);
		if(memcmp(LINE,node -> data,sizeof(LINE)) == 0) {
			printf("found\n");
			return line+1;
		}
		else {
			printf("not found\n");
			line++;
		}
	}
	return 0;
}

static void commands(void* line,void* arena) {
	char* data = line -> data;
	if(memcmp(WAIT,data,sizeof(WAIT)) == 0) {
		
	}
	else if(memcmp(GOTO,data,sizeof(GOTO)) == 0) {
		
	}
	else if(memcmp(IF,data,sizeof(IF)) == 0) {
		
	}
	else if(memcmp(POKE,data,sizeof(POKE)) == 0) {
		
	}
	else if(memcmp(THEN,data,sizeof(THEN)) == 0) {
		
	}
	else if(memcmp(ENGINE,data,sizeof(ENGINE)) == 0) {
		
	}
	else if(memcmp(SHOOT,data,sizeof(SHOOT)) == 0) {
		
	}
}

static int expression(void* tree, void* arena) {
	char* data = line -> data;
	if(memcmp(GPSX,data,sizeof(GPSX)) == 0) {
		
	}
	else if(memcmp(STATE,data,sizeof(STATE)) == 0) {
		
	}
	else if(memcmp(GPSY,data,sizeof(GPSY)) == 0) {
		
	}
	else if(memcmp(ANGLE,data,sizeof(ANGLE)) == 0) {
		
	}
	else if(memcmp(TARGETX,data,sizeof(TARGETX)) == 0) {
		
	}
	else if(memcmp(TARGETY,data,sizeof(TARGETY)) == 0) {
		
	}
	else if(memcmp(DISTANCE,data,sizeof(DISTANCE)) == 0) {
		
	}
	else if(memcmp(OPERATOR,data,sizeof(OPERATOR)) == 0) {
		
	}
	else if(memcmp(SPEED,data,sizeof(SPEED)) == 0) {
		
	}
	else if(memcmp(SELF,data,sizeof(SELF)) == 0) {
		
	}
	else if(memcmp(CARDINAL,data,sizeof(CARDINAL)) == 0) {
		
	}
	else if(memcmp(RAND,data,sizeof(RAND)) == 0) {
		
	}
	else if(memcmp(PEEK,data,sizeof(PEEK)) == 0) {
		
	}
	else {
	//int
	}
}