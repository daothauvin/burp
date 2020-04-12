#include "syntax_analyse.h"


/*
macro executed when a analyse error occure with something we do not know 
( v_string could be without \0 )
*/
#define ERROR_UNKNOWN_OCCURED(token) \
    updateErrorMessage("UNKNOWN", token);\
    return NULL;

/*
macro executed when an error occured during the syntax analyse 
( with a string value )
*/
#define ERROR_OCCURED(token) \
	updateErrorMessage(g_scanner_cur_value (gs).v_string, token);\
    g_scanner_destroy (gs);\
    return NULL;

/*
from for a case if a G_TOKEN_INT IS NOT EXCEPTED ( need to declare int size_cur_token before )
[ size_cur_token ] should be defined and have the good value, 
error_token_tmp is the buffer to stock the result temporarily
*/
#define ERROR_INT_UNEXCEPTED(token,error_token_tmp) \
	case G_TOKEN_INT :\
		error_token_tmp = malloc(size_cur_token + 1);\
		int number = (int) g_scanner_cur_value (gs).v_int;\
		printf("the number : %d of size %d\n",number,size_cur_token + 1);\
		snprintf(error_token_tmp,size_cur_token + 1,"%d",number);\
		updateErrorMessage(error_token_tmp, token);\
		free(error_token_tmp);\
    	g_scanner_destroy (gs);\
    	return NULL;
		
/*
	TODO : 
	create functions to free everything
*/


/*
	Configure the Scanner
*/
static void init_config(GScannerConfig* gsc);

void freeTree(Tree t) {
	g_node_destroy(t);
}


/*
	Uptade error message, free error_token and excepted_token
*/
static void updateErrorMessage(char* error_token_tmp,char* excepted_token_tmp);

/*
	Return the size of a token, if it is not a G_TOKEN_IDENTIFIER then return -1
*/
static int sizeofToken(GTokenType t);


//the scanner currently running
static GScanner * gs;


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
	strcpy(error_token,error_token_tmp);

	excepted_token = malloc(strlen(excepted_token_tmp) + 1);
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
	g_scanner_destroy(gs);
	free(excepted_token);
	free(error_token);
}

/*
	Configure the Scanner
*/
static void init_config(GScannerConfig* gsc) {
	//accept identifier with one char
	gsc -> scan_identifier_1char = 1;

	//add excepted token as identifier

	gchar* cset_identifier = gsc -> cset_identifier_first;
	int sizeone = strlen(cset_identifier);
	gchar* newcset_identifier_first = malloc((sizeone+9)*sizeof(char));
	memmove(newcset_identifier_first, cset_identifier,sizeone);
	newcset_identifier_first[sizeone] = '+';
	newcset_identifier_first[sizeone+1] = '-';
	newcset_identifier_first[sizeone+2] = '*';
	newcset_identifier_first[sizeone+3] = '/';
	newcset_identifier_first[sizeone+4] = '%';
	newcset_identifier_first[sizeone+5] = '=';
	newcset_identifier_first[sizeone+6] = '<';
	newcset_identifier_first[sizeone+7] = '>';

	int sizetwo = strlen(cset_identifier);
	gchar* newcset_identifier_nth = malloc((sizetwo+3)*sizeof(char));
	memmove(newcset_identifier_nth, cset_identifier,sizetwo);
	newcset_identifier_nth[sizetwo] = '=';
	newcset_identifier_nth[sizetwo+1] = '>';
	gsc -> cset_identifier_first = newcset_identifier_first;
	gsc -> cset_identifier_nth = newcset_identifier_nth;
}

/*
	Return the size of a token, if it is not a G_TOKEN_IDENTIFIER or G_TOKEN_INT then return -1
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
				snprintf(message,size_of_message + 1,"a number <= %d",INT_MAX);
				updateErrorMessage(g_scanner_cur_value (gs).v_string, message);
				free(message);
    			g_scanner_destroy (gs);
   				return NULL;
			}
			stocked_value = malloc(sizeof(int));
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
	gchar *value;
	char* buf;
	switch(t) {
		case G_TOKEN_IDENTIFIER :			
			if(strcmp(PLUS,curValue.v_identifier) == 0 
			|| strcmp(MINUS,curValue.v_identifier) == 0 
			|| strcmp(TIME,curValue.v_identifier) == 0 
			|| strcmp(DIV,curValue.v_identifier) == 0 
			|| strcmp(MOD,curValue.v_identifier) == 0) {
				value = malloc(size_cur_token);
				memcpy(value,curValue.v_identifier, size_cur_token);
				return g_node_new (value);	
			}
			ERROR_OCCURED("an operator")
			break;
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
	gchar *value;
	char* buf;
	switch(t) {
		case G_TOKEN_IDENTIFIER :
			
			if(strcmp(INF,char_value) == 0 
			|| strcmp(INF_EG,char_value) == 0 
			|| strcmp(EG,char_value) == 0 
			|| strcmp(DIFF,char_value) == 0 
			|| strcmp(SUP_EG,char_value) == 0 
			|| strcmp(SUP,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value, char_value, size_cur_token);
				return g_node_new (value);
			}
			ERROR_OCCURED("a comparison operator")
			break;
		ERROR_INT_UNEXCEPTED("a comparison operator",buf)
		default :
			break;
	}
	ERROR_UNKNOWN_OCCURED("a comparison operator")
}


//expression
static Tree expression() {

	GTokenType t = g_scanner_get_next_token (gs);

	int size_cur_token = sizeofToken(t);
	
	gchar *value;
	
	int int_value = g_scanner_cur_value (gs).v_int;
	gchar* char_value = g_scanner_cur_value (gs).v_identifier;
	
	Tree arg0;
	Tree arg1;
	Tree arg2;
	Tree arg3;
	Tree myself;
	
	switch(t) {
		
		case G_TOKEN_INT:
				value = malloc(size_cur_token);
				memcpy(value, &int_value, size_cur_token);
				myself = g_node_new (value);
			break;
		case G_TOKEN_LEFT_PAREN:
			arg0 = expression();
			if(arg0 == NULL) return NULL;
			arg1 = operator();
			if(arg1 == NULL) return NULL;
			arg2 = expression();
			if(arg2 == NULL) return NULL;
			myself = g_node_new (OPERATOR);
			if(g_scanner_get_next_token (gs) != G_TOKEN_RIGHT_PAREN) {
				ERROR_OCCURED(")")
			}
			g_node_insert(myself,0,arg0);
			g_node_insert(myself,1,arg1);
			g_node_insert(myself,2,arg2);
			break;
			
		case G_TOKEN_IDENTIFIER:
			
			if(strcmp(MINUS,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value,char_value, size_cur_token);
				arg0 = number();
				*((int*) arg0 -> data) = - *((int*) arg0 -> data);
				return arg0;
			}
			if(strcmp(PEEK,char_value) == 0 
			|| strcmp(RAND,char_value) == 0 
			|| strcmp(STATE,char_value) == 0 
			|| strcmp(GPSX,char_value) == 0 
			|| strcmp(GPSY,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value,char_value, size_cur_token);
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			
			else if(strcmp(CARDINAL,char_value) == 0 
			|| strcmp(SELF,char_value) == 0 
			|| strcmp(SPEED,char_value) == 0 
			|| strcmp(DISTANCE,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value,char_value, size_cur_token);
				myself = g_node_new (value);
			}
			
			else if(strcmp(ANGLE,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value,char_value, size_cur_token);
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				arg1 = expression();
				if(arg1 == NULL) return NULL;
				arg2 = expression();
				if(arg2 == NULL) return NULL;
				arg3 = expression();
				if(arg3 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
				g_node_insert(myself,2,arg2);
				g_node_insert(myself,3,arg3);
			}	
			else if(strcmp(TARGETX,char_value) == 0 || strcmp(TARGETY,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value,char_value, size_cur_token);
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				arg1 = expression();
				if(arg1 == NULL) return NULL;
				arg2 = expression();
				if(arg2 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
				g_node_insert(myself,2,arg2);
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
			
			if(strcmp(WAIT,char_value) == 0 || strcmp(SHOOT,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value, char_value, size_cur_token);
				
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0); 
			}
			else if(strcmp(ENGINE,char_value) == 0 || strcmp(POKE,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value, char_value, size_cur_token);
				
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				arg1 = expression();
				if(arg1 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else if(strcmp(GOTO,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value, char_value, size_cur_token);
				arg0 = number();
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			else if(strcmp(IF,char_value) == 0) {
				value = malloc(size_cur_token);
				memcpy(value, char_value, size_cur_token);
				arg0 = condition();
				if(arg0 == NULL) return NULL;
				//THEN
				switch(g_scanner_get_next_token (gs)) {
					case G_TOKEN_IDENTIFIER:
						if(strcmp(THEN,g_scanner_cur_value (gs).v_identifier) == 0) {
							//ok
						}
						else {
							ERROR_OCCURED("a THEN")
						}
					break;
					ERROR_INT_UNEXCEPTED("a THEN",buf)
					default :
						ERROR_UNKNOWN_OCCURED("a THEN")
				}
				arg1 = number();
				if(arg1 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else {
				ERROR_OCCURED("a valid command")
			}
			break;
			ERROR_INT_UNEXCEPTED("a valid command",buf)
		default :
			ERROR_UNKNOWN_OCCURED("a valid command")
	}
	return myself;
}



static Tree condition() {
	Tree arg0 = expression();
	if(arg0 == NULL) return NULL;
	Tree arg1 = comparison();
	if(arg1 == NULL) return NULL;
	Tree arg2 = expression();
	if(arg2 == NULL) return NULL;
	Tree myself = g_node_new (COND);
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	g_node_insert(myself,2,arg2);
	return myself;
}
static Tree line(int num) {
	Tree arg0 = number();
	if(arg0 == NULL) return NULL;
	int value = *((int*) arg0 -> data);
	if( value != num ) {
	
		int excepted_size_message = snprintf(NULL, 0, "line %d", num) + 1;
		char* excepted_token_tmp = malloc(excepted_size_message);
		snprintf(excepted_token_tmp,excepted_size_message,"line %d",num);

		
		int error_size_message = snprintf(NULL, 0, "line %d", value) + 1;
		printf("number %d of size %d\n",value,error_size_message - 5);
		char* error_token_tmp = malloc(error_size_message);
		snprintf(error_token_tmp,error_size_message,"line %d",value);

		updateErrorMessage(error_token_tmp,excepted_token_tmp);
		
		free(excepted_token_tmp);
		free(error_token_tmp);
		return NULL;
	} 
	
	
	Tree arg1 = command();
	if(arg1 == NULL) return NULL;
	Tree myself = g_node_new (LINE);
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	return myself;
	
}	

static Tree program() {
	Tree currentline;
	Tree program = g_node_new("PROGRAM");
	int n = 0;
	currentline = line(n);
	if(currentline == NULL) {
		g_node_destroy (program);
		return NULL;
	}
	g_node_insert (program, n, currentline);
	while(g_scanner_peek_next_token(gs) != G_TOKEN_EOF) {
		n++;
		currentline = line(n);
		if(currentline == NULL) {
			g_node_destroy (program);
			return NULL;
		}
		g_node_insert (program, n, currentline);
	}
	return program;
}

Tree init_file_tree(char* pathname) {
	
	gs = g_scanner_new (NULL);
	
	GScannerConfig* gsc = gs -> config;
	init_config(gsc);
	
	error_token = NULL;
	excepted_token = NULL;
	
	int fd = open(pathname,O_RDONLY);
	if(fd < -1) {
		return NULL;
	}
	
	//printf("symbol %p\n",g_scanner_lookup_symbol(sc,"+"));
	
	g_scanner_input_file (gs,fd);
	Tree n = program();
	
	//printf("depth : %d\n",g_node_max_height (n));
	return n;
}
