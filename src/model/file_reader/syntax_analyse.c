#include "syntax_analyse.h"
typedef Tree branch();


/**
* macro executed when a analyse error occure with something we do not know 
* ( v_string could be without \0 )
*/
#define ERROR_UNKNOWN_OCCURED(token) \
    updateErrorMessage("UNKNOWN", token);\
    return NULL;

/**
* macro executed when an error occured during the syntax analyse 
* ( with a string value )
*/
#define ERROR_OCCURED(token) \
	updateErrorMessage(g_scanner_cur_value (gs).v_string, token);\
    g_scanner_destroy (gs);\
	gs = NULL;\
    return NULL;

/**
* from for a case if a G_TOKEN_INT IS NOT EXCEPTED ( need to declare int size_cur_token before )
* [ size_cur_token ] should be defined and have the good value, 
* error_token_tmp is the buffer to stock the result temporarily
*/
#define ERROR_INT_UNEXCEPTED(token,error_token_tmp) \
	error_token_tmp = malloc(size_cur_token + 1);\
	if(error_token_tmp == NULL) return NULL;\
	int number = (int) g_scanner_cur_value (gs).v_int;\
	snprintf(error_token_tmp,size_cur_token + 1,"%d",number);\
	updateErrorMessage(error_token_tmp, token);\
	free(error_token_tmp);\
    g_scanner_destroy (gs);\
	gs = NULL;\
    return NULL;

/**
*	Configure the Scanner
*/
static void init_config(GScannerConfig* gsc);



/**
*	Uptade error message, free error_token and excepted_token
*/
static void updateErrorMessage(char* error_token_tmp,char* excepted_token_tmp);

/**
*	Return the size of a token, if it is not a G_TOKEN_IDENTIFIER then return -1
*/
static int sizeofToken(GTokenType t);


//the scanner currently running
static GScanner * gs;


static gboolean freeNodeData(GNode *node, gpointer data) {
	if(node -> data != NULL) {
		free(node -> data);
	}
	node -> data = NULL;
	return 0;
}


void freeTree(Tree t) {
	g_node_traverse (t,G_POST_ORDER,G_TRAVERSE_ALL,-1, freeNodeData, NULL);
	g_node_destroy(t);
}

/*
	Information about the last error
*/
//unexcepted token name
static char* error_token = NULL;
//excepted token name
static char* excepted_token = NULL;
//position of the error
static int errorposition = 0;
//line of the error
static int errorline = 0;

//the error message given
static char error_message[1024];

static void updateErrorMessage(char* error_token_tmp,char* excepted_token_tmp) {
	free(error_token);
	free(excepted_token);
	
	error_token = malloc(strlen(error_token_tmp) + 1);
	if(error_token == NULL) return;
	strcpy(error_token,error_token_tmp);

	excepted_token = malloc(strlen(excepted_token_tmp) + 1);
	if(excepted_token == NULL) return;
	strcpy(excepted_token,excepted_token_tmp);
	
	errorposition = g_scanner_cur_position (gs);
	errorline = g_scanner_cur_line (gs);
}

char* message_error() {
	if(error_token == NULL) {
		return NULL;
	}
	snprintf(error_message,1024, 
		"found %s when searching %s at position %d line %d",
		error_token, excepted_token ,errorposition,errorline);
	return error_message;
}

void  freeSyntaxAnalyseContest() {
	if(gs!=NULL) {
		g_scanner_destroy(gs);
		gs = NULL;
	}
	free(excepted_token);
	free(error_token);
}

/**
*	Configure the Scanner
*/
static void init_config(GScannerConfig* gsc) {
	//accept identifier with one char
	gsc -> scan_identifier_1char = 1;

	//add excepted token as identifier
	gchar* newcset_identifier_first = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%=<>";

	
	gchar* newcset_identifier_nth = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ=>";
	
	gsc -> cset_identifier_first = newcset_identifier_first;
	gsc -> cset_identifier_nth = newcset_identifier_nth;
}

/**
*	Return the size of a token, 
*	if it is not a G_TOKEN_IDENTIFIER or G_TOKEN_INT then return -1
*/
static int sizeofToken(GTokenType t) {
	if(t == G_TOKEN_IDENTIFIER) {
		return strlen(g_scanner_cur_value (gs).v_identifier);
	}
	else if(t == G_TOKEN_INT) {
		return snprintf(NULL,0,"%d",(int) g_scanner_cur_value (gs).v_int);
	}
	return -1;
}

/**
*	Free multiples trees at once
*/
static void freeTrees(int number_tree, ...) {
   va_list va;
   va_start (va, number_tree);
	for(int i = 0; i < number_tree; i++) {
		Tree t = va_arg (va, Tree);
		free(t);
	}
	va_end (va);
}



/**
*	Create a new node, his children will be initilialized this functions of type
*	branch and the number of children should be [nb_branch]
*/

static Tree create_Tree_branches(char* myvalue, int size, int nb_branch, ...) {
	gchar* value = malloc(size);
	if(value == NULL) return NULL;
	Tree myself = g_node_new (value);
	memcpy(value,myvalue,size);
	va_list va;
   	va_start (va, nb_branch);
	for(int i = 0; i < nb_branch; i++) {
		Tree t = va_arg (va, branch*)();
		if(t == NULL) {
			freeTree(myself);
			return NULL;
		}
		g_node_insert(myself,i,t);
	}
	va_end(va);
	return myself;
}

/*

	The next functions correspond to every tags in Burp language

*/

static Tree condition();

//number
static Tree number() {
	GTokenType t = g_scanner_get_next_token (gs);
	int* stocked_value;
	gulong value = g_scanner_cur_value (gs).v_int;
	//if error
	int size_of_message;
	char* message;
	
	int int_value = (int) value;
	
	switch(t) {
		case G_TOKEN_INT:
			if(value > INT_MAX) { //too big int
				size_of_message = snprintf(NULL,0,"a number <= %d",INT_MAX);
				message = malloc(size_of_message + 1);
				if(message == NULL) return NULL;
				snprintf(message,size_of_message + 1,"a number <= %d",INT_MAX);
				updateErrorMessage("a very high number", message);
				free(message);
    			g_scanner_destroy (gs);
				gs = NULL;
   				return NULL;
			}
			stocked_value = malloc(sizeof(int));
			if(stocked_value == NULL) return NULL;
			memmove(stocked_value,&int_value,sizeof(int));
			return g_node_new (stocked_value);
			break;
		case G_TOKEN_IDENTIFIER:
			ERROR_OCCURED("a number")
		default:
			break;
	}
	ERROR_UNKNOWN_OCCURED("a number")
}

//operator
static Tree operator() {
	GTokenType t = g_scanner_get_next_token (gs);
	int size_cur_token = sizeofToken(t);
	GTokenValue curValue = g_scanner_cur_value (gs);
	//gchar *value;
	char* buf;
	switch(t) {
		case G_TOKEN_IDENTIFIER :			
			if(strcmp(PLUS,curValue.v_identifier) == 0 
			|| strcmp(MINUS,curValue.v_identifier) == 0 
			|| strcmp(TIME,curValue.v_identifier) == 0 
			|| strcmp(DIV,curValue.v_identifier) == 0 
			|| strcmp(MOD,curValue.v_identifier) == 0) {
				return create_Tree_branches(curValue.v_identifier, 
					size_cur_token + 1, 0);
			}
			ERROR_OCCURED("an operator")
			break;
		case G_TOKEN_INT :
			ERROR_INT_UNEXCEPTED("an operator",buf)
		default:
			break;
	}
	ERROR_UNKNOWN_OCCURED("an operator")

}

//comparison
static Tree comparison() { 

	GTokenType t = g_scanner_get_next_token (gs);
	
	int size_cur_token = sizeofToken(t);
	gchar* char_value = g_scanner_cur_value (gs).v_identifier;
	char* buf;
	switch(t) {
		case G_TOKEN_IDENTIFIER :
			if(strcmp(INF,char_value) == 0 
			|| strcmp(INF_EG,char_value) == 0 
			|| strcmp(EG,char_value) == 0 
			|| strcmp(DIFF,char_value) == 0 
			|| strcmp(SUP_EG,char_value) == 0 
			|| strcmp(SUP,char_value) == 0) {
				return create_Tree_branches(char_value, size_cur_token + 1, 0);
			}
			ERROR_OCCURED("a comparison operator")
			break;
		case G_TOKEN_INT :
			ERROR_INT_UNEXCEPTED("a comparison operator",buf)
		default :
			break;
	}
	ERROR_UNKNOWN_OCCURED("a comparison operator")
}






//expression
static Tree expression() {

	char* buf;
	GTokenType t = g_scanner_get_next_token (gs);

	int size_cur_token = sizeofToken(t);
	
	gchar *value;
	
	int int_value = g_scanner_cur_value (gs).v_int;
	gchar* char_value = g_scanner_cur_value (gs).v_identifier;
	
	Tree arg0;
	Tree myself;
	
	switch(t) {
		case G_TOKEN_INT:
				return create_Tree_branches((char*) &int_value, sizeof(int), 0);
			break;
		case G_TOKEN_LEFT_PAREN:
			myself = create_Tree_branches(OPERATOR, sizeof(OPERATOR) + 1, 
				3, expression , operator, expression);
			switch(g_scanner_get_next_token (gs)) {
				case G_TOKEN_RIGHT_PAREN:
				break;
				freeTree(myself);
				case G_TOKEN_IDENTIFIER:
					ERROR_OCCURED(")")
				case G_TOKEN_INT :
					ERROR_INT_UNEXCEPTED(")",buf)
				default:
					ERROR_UNKNOWN_OCCURED(")")
			}
			break;
			
		case G_TOKEN_IDENTIFIER:
			
			if(strcmp(MINUS,char_value) == 0) {
				value = malloc(size_cur_token + 1);
				if(value == NULL) return NULL;
				strcpy(value,char_value);
				arg0 = number();
				*((int*) arg0 -> data) = - *((int*) arg0 -> data);
				return arg0;
			}
			if(strcmp(PEEK,char_value) == 0 
			|| strcmp(RAND,char_value) == 0 
			|| strcmp(STATE,char_value) == 0 
			|| strcmp(GPSX,char_value) == 0 
			|| strcmp(GPSY,char_value) == 0) {
				myself = create_Tree_branches(char_value, size_cur_token + 1, 
					1, expression);
			} else if(strcmp(CARDINAL,char_value) == 0 
			|| strcmp(SELF,char_value) == 0 
			|| strcmp(SPEED,char_value) == 0 ) {
				myself = create_Tree_branches(char_value, size_cur_token + 1,0);
			} else if(strcmp(DISTANCE,char_value) == 0
			|| strcmp(ANGLE,char_value) == 0 ) {
				myself = create_Tree_branches(char_value, size_cur_token + 1, 
					4, expression, expression, expression, expression);
			} else if(strcmp(TARGETX,char_value) == 0 
			|| strcmp(TARGETY,char_value) == 0) {
				myself = create_Tree_branches(char_value, size_cur_token + 1, 
					3, expression, expression, expression);
			}
			else {
				ERROR_OCCURED("a valid expression")
			}
			break;
		default :
			ERROR_UNKNOWN_OCCURED("a valid expression")
	}
	return myself;
}

static Tree command() {
	
	Tree arg0;
	Tree arg1;
	Tree myself;
	

	GTokenType t = g_scanner_get_next_token (gs);
	int size_cur_token = sizeofToken(t);
	
	gchar* char_value = g_scanner_cur_value (gs).v_identifier;

	gchar *value;
	
	char* buf;

	switch(t) {
		case G_TOKEN_IDENTIFIER:
			
			if(strcmp(WAIT,char_value) == 0) {
				myself = create_Tree_branches(char_value, size_cur_token + 1, 
					1, expression);
			}
			else if(strcmp(ENGINE,char_value) == 0 
			|| strcmp(SHOOT,char_value) == 0 || strcmp(POKE,char_value) == 0) {
				myself = create_Tree_branches(char_value, size_cur_token + 1, 
					2, expression, expression);
			}
			else if(strcmp(GOTO,char_value) == 0) {
				myself = create_Tree_branches(char_value, size_cur_token + 1, 
					1, number);
			}
			else if(strcmp(IF,char_value) == 0) {
				value = malloc(size_cur_token + 1);
				if(value == NULL) return NULL;
				strcpy(value, char_value);
				arg0 = condition();
				if(arg0 == NULL) {
					free(value);
					return NULL;
				}
				//THEN
				switch(g_scanner_get_next_token (gs)) {
					case G_TOKEN_IDENTIFIER:
						if(strcmp(THEN,
							g_scanner_cur_value(gs).v_identifier)==0) {
							//ok
						}
						else {
							free(value);
							freeTree(arg0);
							ERROR_OCCURED("a THEN")
						}
					break;
					case G_TOKEN_INT :
						free(value);
						freeTree(arg0);	
						ERROR_INT_UNEXCEPTED("a THEN",buf)
					default :
						free(value);
						freeTree(arg0);
						ERROR_UNKNOWN_OCCURED("a THEN")
				}
				arg1 = number();
				if(arg1 == NULL) {
					free(value);
					freeTree(arg0);
					return NULL;
				}
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else {
				ERROR_OCCURED("a valid command")
			}
			break;
			case G_TOKEN_INT :
				ERROR_INT_UNEXCEPTED("a valid command",buf)
		default :
			ERROR_UNKNOWN_OCCURED("a valid command")
	}
	return myself;
}



static Tree condition() {
	return create_Tree_branches(COND, strlen(COND) + 1, 
					3, expression, comparison, expression);
}
static Tree line(int num) {
	
	Tree arg0 = number();
	if(arg0 == NULL) return NULL;
	int value = *((int*) arg0 -> data);
	if( value != num ) {
	
		int excepted_size_message = snprintf(NULL, 0, "line %d", num) + 1;
		char* excepted_token_tmp = malloc(excepted_size_message);
		if(excepted_token_tmp == NULL) {
			freeTree(arg0);
			return NULL;
		}
		snprintf(excepted_token_tmp,excepted_size_message,"line %d",num);

		
		int error_size_message = snprintf(NULL, 0, "line %d", value) + 1;
		char* error_token_tmp = malloc(error_size_message);
		if(error_token_tmp == NULL) {
			freeTree(arg0);
			free(excepted_token_tmp);
			return NULL;
		}
		snprintf(error_token_tmp,error_size_message,"line %d",value);

		updateErrorMessage(error_token_tmp,excepted_token_tmp);
		
		free(excepted_token_tmp);
		free(error_token_tmp);
		freeTree(arg0);
		return NULL;
	} 
	
	
	Tree arg1 = command();
	if(arg1 == NULL) {
		freeTree(arg0);
		return NULL;
	}
	gchar* char_value = malloc(strlen(LINE) + 1);
	if(char_value == NULL) {
		freeTrees(2,arg0,arg1);
		return NULL;
	}
	strcpy(char_value,LINE);
	Tree myself = g_node_new (char_value);
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	return myself;
	
}	

static Tree program() {
	Tree currentline;
	gchar* program_char = malloc(8);
	if(program_char == NULL) return NULL;
	strcpy(program_char,"PROGRAM");
	Tree program = g_node_new(program_char);
	int n = 0;
	currentline = line(n);
	if(currentline == NULL) {
		freeTree (program);
		return NULL;
	}
	g_node_insert (program, n, currentline);
	while(g_scanner_peek_next_token(gs) != G_TOKEN_EOF) {
		n++;
		currentline = line(n);
		if(currentline == NULL) {
			freeTree (program);
			return NULL;
		}
		g_node_insert (program, n, currentline);
	}
	return program;
}

Tree init_file_tree(char* pathname) {
	if(gs != NULL) g_scanner_destroy(gs);
	gs = g_scanner_new (NULL);
	
	GScannerConfig* gsc = gs -> config;
	init_config(gsc);
	
	error_token = NULL;
	excepted_token = NULL;
	
	int fd = open(pathname,O_RDONLY);
	if(fd < -1) {
		return NULL;
	}
	g_scanner_input_file (gs,fd);
	Tree n = program();
	return n;
}
