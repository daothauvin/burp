/*
	Interprete a branch of the syntax tree given by syntax_analyse
	use the commands file of the game model
*/

#include "interpreter.h"


static void printnode(GNode* node, gpointer data);
static int expression(void* tree, void* arene,void* robot);
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

static void printnode(GNode* node, gpointer data) {
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

static void searchline(GNode* node, gpointer data) {
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

static short condition(void* tree, void* arene, void* robot) {
	GNode* node = tree;
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
	else if(memcmp(cond,SUP_EG ,sizeof(SUP_EG )) == 0) {
		return x >= y;
	}
	else if(memcmp(cond,INF_EG,sizeof(INF_EG)) == 0) {
		return x <= y;
	}
	return -1;
}

static int operator(void* tree, void* arene, void* robot) {
	GNode* node = tree;
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

static int commands(void* line,void* arene,void* robot) {
	GNode* node = line;
	char* data = node -> data;
	if(memcmp(IF,data,sizeof(IF)) == 0) {
		if(condition(g_node_nth_child(node, 0),arene,robot))
			return expression(g_node_nth_child(node, 1),arene,robot);
	}
	else if(memcmp(WAIT,data,sizeof(WAIT)) == 0) {
		
		int delay = expression(g_node_nth_child(node, 0),arene,robot);
		wait(robot,delay);
		
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
		//double distance = expression(g_node_nth_child(node, 1),arene,robot);
		//shoot(robot,arene,angle,distance);
		shoot(robot,arene,angle);
	}
	else if(memcmp(ENGINE,data,sizeof(ENGINE)) == 0) {
		double angle = expression(g_node_nth_child(node, 0),arene,robot);
		double speed = expression(g_node_nth_child(node, 1),arene,robot);
		engine(robot,angle,speed);
		
	}
	return -1;
}



static int expression(void* tree, void* arene,void* robot) {
	GNode* node = tree;
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
		return random(max);
	}
	else if(memcmp(PEEK,data,sizeof(PEEK)) == 0) {
		int addr = expression(g_node_nth_child(node, 0),arene,robot);
		//return peek(robot,addr);
		peek(robot,addr);
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

int interprete(int line, void* tree, void* arena,void* robot) {
	while(1) {
		GNode* node = g_node_new (&line);
		g_node_children_foreach (tree, G_TRAVERSE_ALL,searchline,node);
		if(memcmp(LINE,node -> data,sizeof(LINE)) == 0) {
			int res = commands(node,arena,robot);
			if(res != -1) return res;
		}
		else {
			printf("not found\n");
			
		}
	}
	return line+1;
}
