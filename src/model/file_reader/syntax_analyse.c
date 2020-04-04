#include "syntax_analyse.h"

static GScanner * gs;

static GNode* condition();

/**

error handling

**/

//unecepted token name
static char* error_token = NULL;
//ecepted token name
static char* excepted_token = NULL;
//position of the error
static int errorposition = 0;
//line of the error
static int errorline = 0;


static char error_message[255];

char* message_error() {
	if(error_token == NULL) {
		return NULL;
	}
	sprintf(error_message, "found %s when searching %s at position %d line %d",error_token, excepted_token ,errorposition,errorline);
	return error_message;
}

//init the configuration
static void init_config(GScannerConfig* gsc) {
	//identifier with one char
	gsc -> scan_identifier_1char = 1;
	
	//add excepted token for identifier
	gchar* c = gsc -> cset_identifier_first;
	
	int sizeone = strlen(c);
	gchar* newc = malloc((sizeone+9)*sizeof(char));
	memmove(newc, c,sizeone);
	newc[sizeone] = '+';
	newc[sizeone+1] = '-';
	newc[sizeone+2] = '*';
	newc[sizeone+3] = '/';
	newc[sizeone+4] = '%';
	newc[sizeone+5] = '=';
	newc[sizeone+6] = '<';
	newc[sizeone+7] = '>';

	int sizetwo = strlen(c);
	gchar* newc2 = malloc((sizetwo+3)*sizeof(char));
	memmove(newc2, c,sizetwo);
	newc2[sizetwo] = '=';
	newc2[sizetwo+1] = '>';
	gsc -> cset_identifier_first = newc;
	gsc -> cset_identifier_nth = newc2;
	
	//printf("%s\n",gsc -> cset_identifier_first);
	//printf("%s\n",gsc -> cset_identifier_nth);
}

//number
static GNode* number() {
	GTokenType t = g_scanner_get_next_token (gs);
	int* value = malloc(sizeof(int));
	int int_value = (int) g_scanner_cur_value (gs).v_int;
	//printf("int_value : %d\n",int_value);
	switch(t) {
		case G_TOKEN_INT:
			memmove(value,&int_value,sizeof(int));
			return g_node_new (value);
			break;
		default:
			break;
	}
	error_token = g_scanner_cur_value (gs).v_string;
	excepted_token = "a number";
	errorposition = g_scanner_cur_position (gs);
	errorline = g_scanner_cur_line (gs);
	return NULL;
}


//operator
static GNode* operator() {
	GTokenType t = g_scanner_get_next_token (gs);
	//char* value = g_scanner_cur_value (gs).v_identifier;
	int valuesize = t == G_TOKEN_IDENTIFIER? strlen(g_scanner_cur_value (gs).v_identifier) * sizeof(char) : 0;
	//malloc sans free si erreur
	gchar *value = malloc(valuesize);
	switch(t) {
		case G_TOKEN_IDENTIFIER :
			memcpy(value, g_scanner_cur_value (gs).v_identifier, valuesize);
			if(strcmp(PLUS,value) == 0 || strcmp(MINUS,value) == 0 || strcmp(TIME,value) == 0 || strcmp(DIV,value) == 0 || strcmp(MOD,value) == 0) {
				
				return g_node_new (value);
			}
			break;
		default:
			break;
	}
	error_token = g_scanner_cur_value (gs).v_string;
	excepted_token = "an operator";
	errorposition = g_scanner_cur_position (gs);	
	errorline = g_scanner_cur_line (gs);
	return NULL;

}

//comparison
static GNode* comparison() { 

	GTokenType t = g_scanner_get_next_token (gs);
	
	int valuesize = t == G_TOKEN_IDENTIFIER? strlen(g_scanner_cur_value (gs).v_identifier) * sizeof(char) : 0;
	//malloc sans free si erreur
	gchar *value = malloc(valuesize);
	
	switch(t) {
		case G_TOKEN_IDENTIFIER :
			memcpy(value, g_scanner_cur_value (gs).v_identifier, valuesize);
			if(strcmp(INF,value) == 0 || strcmp(INF_EG,value) == 0 || strcmp(EG,value) == 0 || strcmp(DIFF,value) == 0 || strcmp(SUP_EG,value) == 0 || strcmp(SUP,value) == 0) {
				return g_node_new (value);
			}
			break;
		default :
			break;
	}
	error_token = g_scanner_cur_value (gs).v_string;
	excepted_token = "a comparison operator";
	errorposition = g_scanner_cur_position (gs);	
	errorline = g_scanner_cur_line (gs);
	return NULL;
}


//expression
static GNode* expression() {

	GTokenType t = g_scanner_get_next_token (gs);

	int valuesize = (t == G_TOKEN_IDENTIFIER)? strlen(g_scanner_cur_value (gs).v_identifier) * sizeof(char) : sizeof(int);
	//malloc sans free si erreur
	gchar *value = malloc(valuesize);
	int int_value = g_scanner_cur_value (gs).v_int;
	
	GNode* arg0;
	GNode* arg1;
	GNode* arg2;
	GNode* arg3;
	GNode* myself;
	
	switch(t) {
		
		case G_TOKEN_INT:
				memcpy(value, &int_value, valuesize);
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
				error_token = g_scanner_cur_value (gs).v_string;
				excepted_token = ")";
				errorposition = g_scanner_cur_position (gs);
				errorline = g_scanner_cur_line (gs);
				return NULL;
			}
			g_node_insert(myself,0,arg0);
			g_node_insert(myself,1,arg1);
			g_node_insert(myself,2,arg2);
			break;
			
		case G_TOKEN_IDENTIFIER:
			memcpy(value, g_scanner_cur_value (gs).v_identifier, valuesize);
			if(strcmp(MINUS,value) == 0) {
				arg0 = number();
				*((int*) arg0 -> data) = - *((int*) arg0 -> data);
				return arg0;
			}
			if(strcmp(PEEK,value) == 0 || strcmp(RAND,value) == 0 || strcmp(STATE,value) == 0 || strcmp(GPSX,value) == 0 || strcmp(GPSY,value) == 0) {
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			
			else if(strcmp(CARDINAL,value) == 0 || strcmp(SELF,value) == 0 || strcmp(SPEED,value) == 0 || strcmp(DISTANCE,value) == 0) {
				myself = g_node_new (value);
			}
			
			else if(strcmp(ANGLE,value) == 0) {
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
			else if(strcmp(TARGETX,value) == 0 || strcmp(TARGETY,value) == 0) {
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
				error_token = g_scanner_cur_value (gs).v_string;
				excepted_token = "a valid expression";
				errorposition = g_scanner_cur_position (gs);	
				errorline = g_scanner_cur_line (gs);
				return NULL;
			}
			break;
		default :
			error_token = g_scanner_cur_value (gs).v_string;
			excepted_token = "a valid expression";
			errorposition = g_scanner_cur_position (gs);	
			errorline = g_scanner_cur_line (gs);
			return NULL;
	}
	return myself;
}

static GNode* command() {
	
	GNode* arg0;
	GNode* arg1;
	GNode* myself;
	
	GTokenType t = g_scanner_get_next_token (gs);
	
	int valuesize = t == G_TOKEN_IDENTIFIER? strlen(g_scanner_cur_value (gs).v_identifier) * sizeof(char) : 0;
	//malloc sans free si erreur
	gchar *value = malloc(valuesize);
	
	switch(t) {
		case G_TOKEN_IDENTIFIER:
			memcpy(value, g_scanner_cur_value (gs).v_identifier, valuesize);
			
			if(strcmp(WAIT,value) == 0 || strcmp(SHOOT,value) == 0) {
				
				
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0); 
			}
			else if(strcmp(ENGINE,value) == 0 || strcmp(POKE,value) == 0) {
				arg0 = expression();
				if(arg0 == NULL) return NULL;
				arg1 = expression();
				if(arg1 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else if(strcmp(GOTO,value) == 0) {
				arg0 = number();
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			else if(strcmp(IF,value) == 0) {
				arg0 = condition();
				if(arg0 == NULL) return NULL;
				//THEN
				switch(g_scanner_get_next_token (gs)) {
					case G_TOKEN_IDENTIFIER:
						if(strcmp(THEN,g_scanner_cur_value (gs).v_identifier) == 0) {
							//ok
						}
						else {
							error_token = g_scanner_cur_value (gs).v_string;
							excepted_token = "a THEN";
							errorposition = g_scanner_cur_position (gs);	
							errorline = g_scanner_cur_line (gs);
							return NULL;
						}
					break;
					default :
						error_token = g_scanner_cur_value (gs).v_string;
						excepted_token = "a THEN";
						errorposition = g_scanner_cur_position (gs);	
						errorline = g_scanner_cur_line (gs);
						return NULL;
				}
				arg1 = number();
				if(arg1 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else {
				error_token = g_scanner_cur_value (gs).v_string;
				excepted_token = "a valid command";
				errorposition = g_scanner_cur_position (gs);	
				errorline = g_scanner_cur_line (gs);
				return NULL;
			}
			break;
		default :
			error_token = g_scanner_cur_value (gs).v_string;
			excepted_token = "a valid command";
			errorposition = g_scanner_cur_position (gs);	
			errorline = g_scanner_cur_line (gs);
			return NULL;
	}
	return myself;
}



static GNode* condition() {
	GNode* arg0 = expression();
	if(arg0 == NULL) return NULL;
	GNode* arg1 = comparison();
	if(arg1 == NULL) return NULL;
	GNode* arg2 = expression();
	if(arg2 == NULL) return NULL;
	GNode* myself = g_node_new (COND);
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	g_node_insert(myself,2,arg2);
	return myself;
}


static GNode* line() {
	GNode* arg0 = number();
	if(arg0 == NULL) return NULL;
	GNode* arg1 = command();
	if(arg1 == NULL) return NULL;
	GNode* myself = g_node_new (LINE);
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	return myself;
	
}	

static GNode* program() {
	GNode* currentline;
	GNode* program = g_node_new("PROGRAM");
	int n = 0;
	currentline = line(gs);
	if(currentline == NULL) return NULL;
	g_node_insert (program, n, currentline);
	while(g_scanner_peek_next_token(gs) != G_TOKEN_EOF) {
		n++;
		currentline = line();
		if(currentline == NULL) return NULL;
		g_node_insert (program, n, currentline);
	}
	return program;
}

void* init(char* pathname) {
	
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
	GNode* n = program();
	
	if(error_token !=NULL) return NULL;
	
	//printf("depth : %d\n",g_node_max_height (n));
	return n;
}
