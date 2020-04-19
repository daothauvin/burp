/*
	Interprete a branch of the syntax tree given by syntax_analyse
	use the commands file of the game model
*/

#include "interpreter.h"


/*
	Print the node [node], 
	this function is given to g_node_children_foreach to print every nodes with print
*/
static void printnode(Tree node, gpointer data);

/*
return 1 if the [ data ] given is a data that can be a leaf of the syntax tree
( INF, INF_EG, EG, DIFF, SUP_EG, CARDINAL, SELF, SPEED, PLUS, MINUS, TIME, DIV, MOD for now ) 
Allow to find numbers
*/
static short isTag(gpointer data);

/*
	print the number of the line [ line ]
*/
static int numberline(Tree line);

/*
	Put in [ data ] the [ node ] if he corresponds to the line given in [ data ], 
	this function is given to g_node_children_foreach to find a given line in  getLine and interprete
*/
static void searchline(Tree node, gpointer data);

static int expression(Tree tree, Arene arene,Robot robot);

static short isTag(gpointer data) {
	return 
		//size one bytes
		memcmp(INF,data,sizeof(INF)) == 0 
		|| memcmp(PLUS,data,sizeof(PLUS)) == 0 
		|| memcmp(EG,data,sizeof(EG)) == 0
		|| memcmp(MINUS,data,sizeof(MINUS)) == 0 
		|| memcmp(TIME,data,sizeof(TIME)) == 0 
		|| memcmp(DIV,data,sizeof(DIV)) == 0 
		|| memcmp(MOD,data,sizeof(MOD)) == 0
		//size two bytes
		|| (sizeof(data) > 1
		&& ( memcmp(INF_EG,data,sizeof(INF_EG)) == 0
		|| memcmp(DIFF,data,sizeof(DIFF)) == 0 
		|| memcmp(SUP_EG,data,sizeof(SUP_EG)) == 0
		//size four bytes 
		|| (sizeof(data) > 3 
		&& ( memcmp(SELF,data,sizeof(SELF)) == 0 
		|| memcmp(SPEED,data,sizeof(SPEED)) == 0
		//size height bytes
		|| (sizeof(data) > 7 
		&& memcmp(CARDINAL,data,sizeof(CARDINAL)) == 0) ))));
}

void printTree(Tree tree) {
	int i = 0;
	g_node_children_foreach (tree,G_TRAVERSE_ALL,&printnode,&i);
	printf("number of node : %d\n",i);
}

static void printnode(Tree node, gpointer data) {
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
	g_node_children_foreach (node,G_TRAVERSE_ALL,&printnode,data);
}

static int numberline(Tree line) {
	return *((int*) g_node_first_child(line) -> data);
}

static void searchline(Tree node, gpointer data) {
	GNode *search = data;
	if(search -> next != NULL) {
		return;
	}
	if(numberline(node) == *((int*) search -> data)) {
		search -> next = node;
	}
}

char* getLine(Tree tree,int line) {
	char* message = "NONE";
	Tree node = g_node_new (&line);
	g_node_children_foreach (tree, G_TRAVERSE_ALL,searchline,node);
	if(node -> next != NULL) {
		message = g_node_nth_child (node -> next,1) -> data;
		node -> next = NULL;
	}
	g_node_destroy(node);
	return message;

}

/*

	The following functions execute the burp language interpretation for the diverse symbol categories,
	each return the result of the execution

*/
static short condition(Tree node, Arene arene, Robot robot) {
	//printf("%p %p %p\n",node,arene,robot);
	int x = expression(g_node_nth_child(node, 0),arene,robot);
	int y = expression(g_node_nth_child(node, 2),arene,robot);
	char* cond = g_node_nth_child(node, 1) -> data;
	if(memcmp(cond,INF,sizeof(INF)) == 0) {
		return x < y;
	}
	else if(memcmp(cond,EG,sizeof(EG)) == 0) {
		return x == y;
	}
	else if(memcmp(cond,SUP,sizeof(SUP)) == 0) {
		return x > y;
	}
	else if(memcmp(cond,DIFF,sizeof(DIFF)) == 0) {
		return x != y;
	}
	else if(memcmp(cond,SUP_EG ,sizeof(SUP_EG)) == 0) {
		return x >= y;
	}
	else if(memcmp(cond,INF_EG,sizeof(INF_EG)) == 0) {
		return x <= y;
	}
	abort();
}

static int operator(Tree node, Arene arene, Robot robot) {
	int x = expression(g_node_nth_child(node, 0),arene,robot);
	int y = expression(g_node_nth_child(node, 2),arene,robot);
	char* op = g_node_nth_child(node, 1) -> data;
	if(memcmp(op,PLUS,sizeof(PLUS)) == 0) {
		return x + y;
	}
	else if(memcmp(op,MINUS,sizeof(MINUS)) == 0) {
		return x - y;
	}
	else if(memcmp(op,PLUS,sizeof(MINUS)) == 0) {
		return x - y;
	}
	else if(memcmp(op,TIME,sizeof(TIME)) == 0) {
		return x * y;
	}
	else if(memcmp(op,DIV,sizeof(DIV)) == 0) {
		return x / y;
	}
	else if(memcmp(op,MOD,sizeof(MOD)) == 0) {
		return x % y;
	}
	return -1;
	
}

static int commands(Tree node,Arene arene,Robot robot) {
	char* data = node -> data;
	//printf("data : %ld %s\n",strlen(data),data);
	if(memcmp(IF,data,sizeof(IF)) == 0 && condition(g_node_nth_child(node, 0),arene,robot)) {
			return expression(g_node_nth_child(node, 1),arene,robot);
	}
	else if(memcmp(WAIT,data,sizeof(WAIT)) == 0) {
		
		int delay = expression(g_node_nth_child(node, 0),arene,robot);
		wait_robot(robot,delay);
		
	}
	else if(memcmp(GOTO,data,sizeof(GOTO)) == 0) {
		int delay = expression(g_node_nth_child(node, 0),arene,robot);
		return go_to(delay);
		
	}
	else if(memcmp(POKE,data,sizeof(POKE)) == 0) {
		int addr = expression(g_node_nth_child(node, 0),arene,robot);
		int value = expression(g_node_nth_child(node, 1),arene,robot);
		poke(robot,addr,value);
	}
	else if(memcmp(SHOOT,data,sizeof(SHOOT)) == 0) {
		double angle = expression(g_node_nth_child(node, 0),arene,robot);
		double distance = expression(g_node_nth_child(node, 1),arene,robot);
		shoot(robot,arene,angle,distance);
	}
	else if(memcmp(ENGINE,data,sizeof(ENGINE)) == 0) {
		double angle = expression(g_node_nth_child(node, 0),arene,robot);
		double speed = expression(g_node_nth_child(node, 1),arene,robot);
		engine(robot,angle,speed);
		
	}
	return -1;
}



static int expression(Tree tree, Arene arene,Robot robot) {
	Tree node = tree;
	char* data = node -> data;
	if(memcmp(OPERATOR,data,sizeof(OPERATOR)) == 0) {
		return operator(tree,arene,robot);
	}
	else if(memcmp(GPSX,data,sizeof(GPSX)) == 0) {
		int num = expression(g_node_nth_child(node, 0),arene,robot);
		return gpsx(arene,num);
	}
	else if(memcmp(GPSY,data,sizeof(GPSY)) == 0) {
		int num = expression(g_node_nth_child(node, 0),arene,robot);
		return gpsy(arene,num);
	}
	else if(memcmp(SELF,data,sizeof(SELF)) == 0) {
		return self(robot);
	}
	else if(memcmp(RAND,data,sizeof(RAND)) == 0) {
		int max = expression(g_node_nth_child(node, 0),arene,robot);
		return randoms(max);
	}
	else if(memcmp(PEEK,data,sizeof(PEEK)) == 0) {
		int addr = expression(g_node_nth_child(node, 0),arene,robot);
		return peek(robot,addr);
		//peek(robot,addr);
	}
	else if(memcmp(STATE,data,sizeof(STATE)) == 0) {
		int num = expression(g_node_nth_child(node, 0),arene,robot);
		return state(arene,num);
	}
	else if(memcmp(SPEED,data,sizeof(SPEED)) == 0) {
		return speed(robot);
	}
	else if(memcmp(ANGLE,data,sizeof(ANGLE)) == 0) {
		double x1 = expression(g_node_nth_child(node, 0),arene,robot);
		double y1 = expression(g_node_nth_child(node, 1),arene,robot);
		double x2 = expression(g_node_nth_child(node, 2),arene,robot);
		double y2 = expression(g_node_nth_child(node, 3),arene,robot);
		return angle(x1,y1,x2,y2);
	}
	
	else if(memcmp(TARGETX,data,sizeof(TARGETX)) == 0) {
		double x1 = expression(g_node_nth_child(node, 0),arene,robot);
		double angle = expression(g_node_nth_child(node, 1),arene,robot);
		double length = expression(g_node_nth_child(node, 2),arene,robot);
		return targetx(x1,angle,length);
	}
	else if(memcmp(TARGETY,data,sizeof(TARGETY)) == 0) {
		double y1 = expression(g_node_nth_child(node, 0),arene,robot);
		double angle = expression(g_node_nth_child(node, 1),arene,robot);
		double length = expression(g_node_nth_child(node, 2),arene,robot);
		return targety(y1,angle,length);
	}
	else if(memcmp(DISTANCE,data,sizeof(DISTANCE)) == 0) {
		double x1 = expression(g_node_nth_child(node, 0),arene,robot);
		double y1 = expression(g_node_nth_child(node, 1),arene,robot);
		double x2 = expression(g_node_nth_child(node, 2),arene,robot);
		double y2 = expression(g_node_nth_child(node, 3),arene,robot);
		return distance(x1,y1,x2,y2);
	}

	else if(memcmp(CARDINAL,data,sizeof(CARDINAL)) == 0) {
		return cardinal(arene);
	}
	else {
		return *((int*) data);
	}
	return -1;
}

int interprete(int line, Tree tree, Arene arena,Robot robot) {
	Tree node = g_node_new (&line);
	g_node_children_foreach (tree, G_TRAVERSE_ALL,searchline,node);
	if(node -> next != NULL) {
		int res = commands(g_node_nth_child (node -> next,1),arena,robot);
		node -> next = NULL;
		
		if(res != -1) {
			g_node_destroy(node);
			return res;
		}
	}
	g_node_destroy(node);
	return line + 1;
}

