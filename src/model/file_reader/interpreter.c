/**
*	Interprete a branch of the syntax tree given by syntax_analyse
*	use the commands file of the game model
*/

#include "interpreter.h"


/**
*	Print the node [node], 
*	this function is given to g_node_children_foreach 
*	to print every nodes with print
*/
static void printnode(Tree node, gpointer data);

/**
*	return 1 if the [ data ] given is a data that can be a 
*	leaf of the syntax tree
*	( INF, INF_EG, EG, DIFF, SUP_EG, CARDINAL, 
*	SELF, SPEED, PLUS, MINUS, TIME, DIV, MOD for now ) 
*	Allow to find numbers
*/
static short isTag(gpointer data);

/**
*	print the number of the line [ line ]
*/
static int numberline(Tree line);

/**
*	Put in [ data ] the [ node ] if he corresponds to the line given in [ data ] 
*	This function is given to g_node_children_foreach 
*	to find a given line in getLine and interprete
*/
static void searchline(Tree node, gpointer data);

static int expression(Tree tree, arena* arena,robot* rob);

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
	printf("- currrent:tag = %s\n",(char*)tree -> data);
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


struct warning_message* burp_errors = NULL;
struct warning_message* last_burp_error = NULL;

/**
*	Add a warning to the burp error pipe [pipeError] 
*	where [value] correspond to the incorrect value
*	and [line] the line where it occurs
*	Burp errors : 
*	- unknown robot number ([num_warning] = 0)
*	- robot memory is too high ([num_warning] = 1)
*	- gpsx on dead robot ([num_warning] = 2)
*	- gpsy on dead robot ([num_warning] = 3)
*/
static void addWarning(int num_warning,int value,int robot) {
	struct warning_message* new_error = malloc(sizeof(struct warning_message));
	if(new_error == NULL) return;
	new_error->num_robot=robot;
	new_error->next_message=NULL;
	switch (num_warning)
	{
		case 0:
			snprintf(new_error->message,60,
				"robot number %d is invalid (max: %d)",
				value,number_of_robots - 1);
			break;
		case 1:
			snprintf(new_error->message,60,
				"robot memory %d is invalid (max: %d)",
				value,robot_memory - 1);
			break;
		case 2:
			snprintf(new_error->message,60,"gpsx on dead robot %d",value);
			break;
		case 3:
			snprintf(new_error->message,60,"gpsy on dead robot %d",value);
			break;
		default:
			break;
	}
	if(burp_errors == NULL) {
		burp_errors = new_error;
		last_burp_error = new_error;
	}
	else {
		last_burp_error -> next_message = new_error;
		last_burp_error = new_error;
	}
}

struct warning_message* getWarnings() {
	return burp_errors;
}

void freeWarnings() {
	struct warning_message* tmp;
	while(burp_errors != NULL) {
		tmp = burp_errors;
		burp_errors = burp_errors->next_message;
		free(tmp);
	}
}


/*

	The following functions execute the burp language interpretation for the 
	diverse symbol categories,
	each return the result of the execution

*/
static short condition(Tree node, arena* arena,robot* robot) {
	int x = expression(g_node_nth_child(node, 0),arena,robot);
	int y = expression(g_node_nth_child(node, 2),arena,robot);
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

static int operator(Tree node, arena* arena,robot* robot) {
	int x = expression(g_node_nth_child(node, 0),arena,robot);
	int y = expression(g_node_nth_child(node, 2),arena,robot);
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
		return fmod(x,y);
	}
	return -1;
	
}

static int commands(Tree node,arena *arena,robot *robot) {
	char* data = node -> data;
	if(memcmp(IF,data,sizeof(IF)) == 0 
		&& condition(g_node_nth_child(node, 0),arena,robot)) {
		return expression(g_node_nth_child(node, 1),arena,robot);
	}
	else if(memcmp(WAIT,data,sizeof(WAIT)) == 0) {
		int delay = expression(g_node_nth_child(node, 0),arena,robot);
		wait_robot(robot,delay);
	}
	else if(memcmp(GOTO,data,sizeof(GOTO)) == 0) {
		int line = expression(g_node_nth_child(node, 0),arena,robot);
		return go_to(line);
	}
	else if(memcmp(POKE,data,sizeof(POKE)) == 0) {
		int addr = expression(g_node_nth_child(node, 0),arena,robot);
		if(addr >= robot_memory) {
			addWarning(1,addr,get_robot_id(robot));
			addr = robot_memory - 1;
		}
		int value = expression(g_node_nth_child(node, 1),arena,robot);
		poke(robot,addr,value);
	} 
	else if(memcmp(SHOOT,data,sizeof(SHOOT)) == 0) {
		int angle = expression(g_node_nth_child(node, 0),arena,robot);
		int distance = expression(g_node_nth_child(node, 1),arena,robot);
		shoot(robot,arena,angle,distance);
	}
	else if(memcmp(ENGINE,data,sizeof(ENGINE)) == 0) {
		int angle = expression(g_node_nth_child(node, 0),arena,robot);
		int speed = expression(g_node_nth_child(node, 1),arena,robot);
		if(speed > 100) speed = 100;
		if(speed < 0) speed = 0;

		engine(robot,angle,speed);
		
	}
	return -1;
}



static int expression(Tree tree, arena* arena,robot* robot) {
	Tree node = tree;
	char* data = node -> data;
	if(memcmp(OPERATOR,data,sizeof(OPERATOR)) == 0) {
		return operator(tree,arena,robot);
	}
	else if(memcmp(GPSX,data,sizeof(GPSX)) == 0) {
		int num = expression(g_node_nth_child(node, 0),arena,robot);
		if(num >= number_of_robots) {
			addWarning(0,num,get_robot_id(robot));
			num = number_of_robots - 1;
		}
		else if(num == -1) {
			addWarning(2,num,get_robot_id(robot));
			return 0;
		}
		
		return gpsx(arena,num);
	}
	else if(memcmp(GPSY,data,sizeof(GPSY)) == 0) {
		int num = expression(g_node_nth_child(node, 0),arena,robot);
		if(num >= number_of_robots) {
			addWarning(0,num,get_robot_id(robot));
			num = number_of_robots - 1;
		}
		else if(num == -1) {
			addWarning(3,num,get_robot_id(robot));
			return 0;
		}
		
		return gpsy(arena,num);
	}
	else if(memcmp(SELF,data,sizeof(SELF)) == 0) {
		return self(robot);
	}
	else if(memcmp(RAND,data,sizeof(RAND)) == 0) {
		int max = expression(g_node_nth_child(node, 0),arena,robot);
		return randoms(max);
	}
	else if(memcmp(PEEK,data,sizeof(PEEK)) == 0) {
		int addr = expression(g_node_nth_child(node, 0),arena,robot);
		if(addr >= robot_memory) {
			addWarning(1,addr,get_robot_id(robot));
			addr = robot_memory - 1;
		}
		
		return peek(robot,addr);
	}
	else if(memcmp(STATE,data,sizeof(STATE)) == 0) {
		int num = expression(g_node_nth_child(node, 0),arena,robot);
		if(num >= number_of_robots) {
			addWarning(0,num,get_robot_id(robot));
			num = number_of_robots - 1;
		}
		return state(arena,num);
	}
	else if(memcmp(SPEED,data,sizeof(SPEED)) == 0) {
		return speed(robot);
	}
	else if(memcmp(ANGLE,data,sizeof(ANGLE)) == 0) {
		int x1 = expression(g_node_nth_child(node, 0),arena,robot);
		int y1 = expression(g_node_nth_child(node, 1),arena,robot);
		int x2 = expression(g_node_nth_child(node, 2),arena,robot);
		int y2 = expression(g_node_nth_child(node, 3),arena,robot);
		int x =  angle(x1,y1,x2,y2);
		return x;
	}
	
	else if(memcmp(TARGETX,data,sizeof(TARGETX)) == 0) {
		int x1 = expression(g_node_nth_child(node, 0),arena,robot);
		int angle = expression(g_node_nth_child(node, 1),arena,robot);
		int length = expression(g_node_nth_child(node, 2),arena,robot);
		return targetx(x1,angle,length);
	}
	else if(memcmp(TARGETY,data,sizeof(TARGETY)) == 0) {
		int y1 = expression(g_node_nth_child(node, 0),arena,robot);
		int angle = expression(g_node_nth_child(node, 1),arena,robot);
		int length = expression(g_node_nth_child(node, 2),arena,robot);
		return targety(y1,angle,length);
	}
	else if(memcmp(DISTANCE,data,sizeof(DISTANCE)) == 0) {
		int x1 = expression(g_node_nth_child(node, 0),arena,robot);
		int y1 = expression(g_node_nth_child(node, 1),arena,robot);
		int x2 = expression(g_node_nth_child(node, 2),arena,robot);
		int y2 = expression(g_node_nth_child(node, 3),arena,robot);
		return distance(x1,y1,x2,y2);
	}

	else if(memcmp(CARDINAL,data,sizeof(CARDINAL)) == 0) {
		return cardinal(arena);
	}
	else {
		return *((int*) data);
	}
	return -1;
}

int interprete(int line, Tree tree, arena* arena,robot* robot) {
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

