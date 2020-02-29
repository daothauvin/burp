#include "syntax_analyse.h"

static GScanner * sc;

static GNode* condition(GScanner* gs);

static char* error_token = NULL;
static char* excepted_token = NULL;
static int errorposition = 0;
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
	//activate symbols
	//gsc -> scan_symbols = 1;
	//return token symbol if find symbol
	gsc -> symbol_2_token = 0;
	
	gchar* c = gsc -> cset_identifier_first;
	
	int sizeone = strlen(c);

	gchar* newc = malloc((sizeone+6)*sizeof(char));
	memmove(newc, c,sizeone);
	newc[sizeone] = '+';
	newc[sizeone+1] = '-';
	newc[sizeone+2] = '*';
	newc[sizeone+3] = '/';
	newc[sizeone+4] = '%';
	
	gchar* c2 = gsc -> cset_identifier_nth;
	int sizetwo = strlen(c2);
	gchar* newc2 = malloc((sizetwo+2)*sizeof(char));
	memmove(newc2, c2,sizetwo);
	newc2[sizetwo] = '+';
	
	gsc -> cset_identifier_first = newc;
	gsc -> cset_identifier_nth = newc2;
	
	printf("%s\n",gsc -> cset_identifier_first);
	printf("%s\n",gsc -> cset_identifier_nth);
}



//give symbols
static void symbols(GScanner* gs) {
	//put the scope to 0 ( it's normally 0 but to be sure )
	g_scanner_set_scope (gs,0);
	
	//add symbols
	int plus = PLUS;
	int min = MIN;
	int time = TIME;
	int div = DIV;
	int mod = MOD;
	g_scanner_scope_add_symbol (gs, 0, "+", &plus);
	g_scanner_scope_add_symbol (gs, 0, "-", &min);
	g_scanner_scope_add_symbol (gs, 0, "*", &time);
	g_scanner_scope_add_symbol (gs, 0, "/", &div);
	g_scanner_scope_add_symbol (gs, 0, "%", &mod);

	
}

//number
static GNode* number(GScanner* gs) {
	GTokenType t = g_scanner_get_next_token (gs);
	switch(t) {
		case G_TOKEN_INT:
			if(g_scanner_cur_value (gs).v_int < 0 ) {
				error_token = g_scanner_cur_value (gs).v_string;
				excepted_token = "a positive number";
				errorposition = g_scanner_cur_position (gs);	
				errorline = g_scanner_cur_line (gs);
				return NULL;
			}
			else {
				int value = g_scanner_cur_value (gs).v_int;
				return g_node_new (&value);
			}
			break;
		default:
			error_token = g_scanner_cur_value (gs).v_string;
			excepted_token = "a positive number";
			errorposition = g_scanner_cur_position (gs);
			errorline = g_scanner_cur_line (gs);
			return NULL;
	}
}


//operator
static GNode* operator(GScanner* gs) {
	
	operator_name* value = g_scanner_cur_value (gs).v_symbol;
	
	switch(g_scanner_get_next_token (gs)) {
		case G_TOKEN_SYMBOL :
			printf("%p\n",value);
			switch(*value) {
				case PLUS :
					break;
				case MIN :
					break;
				case TIME :
					break;
				case DIV :
					break;
				case MOD :
					break;
				default :
					error_token = g_scanner_cur_value (gs).v_string;
					excepted_token = "an operator";
					errorposition = g_scanner_cur_position (gs);	
					errorline = g_scanner_cur_line (gs);
					return NULL;
			}
			return g_node_new (&value);
			break;
		default :
			error_token = g_scanner_cur_value (gs).v_string;
			excepted_token = "an operator";
			errorposition = g_scanner_cur_position (gs);	
			errorline = g_scanner_cur_line (gs);
			return NULL;
		}

}

//comparaison
static GNode* comparaison(GScanner* gs) { 
	switch(g_scanner_get_next_token (gs)) {
	  /*		case '<' :
			break;
		case '<=' :
			break;
		case '=' :
			break;
		case '<>' :
			break;
		case '>' :
		break; */
		default :
			error_token = g_scanner_cur_value (gs).v_string;
			excepted_token = "a comparaison operator";
			errorposition = g_scanner_cur_position (gs);	
			errorline = g_scanner_cur_line (gs);
	}
	return g_node_new (NULL);
}


//expression
static GNode* expression(GScanner* gs) {
	int op = OPERATOR;
	GTokenType t = g_scanner_get_next_token (gs);
	gchar *value = g_scanner_cur_value (gs).v_identifier;
	
	GNode* arg0;
	GNode* arg1;
	GNode* arg2;
	GNode* arg3;
	GNode* myself;
	int int_value = g_scanner_cur_value (gs).v_int;
	switch(t) {
		
		case G_TOKEN_INT:
				myself = g_node_new (&int_value);
			break;
			
		case G_TOKEN_LEFT_PAREN:
			arg0 = expression(gs);
			if(arg0 == NULL) return NULL;
			arg1 = operator(gs);
			if(arg1 == NULL) return NULL;
			arg2 = expression(gs);
			if(arg2 == NULL) return NULL;
			myself = g_node_new (&op);
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
			if(strcmp("PPEK",value) == 0 || strcmp("RAND",value) == 0 || strcmp("STATE",value) == 0 || strcmp("GPSX",value) == 0 || strcmp("GPSY",value) == 0) {
				arg0 = expression(gs);
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			
			else if(strcmp("CARDINAL",value) == 0 || strcmp("SELF",value) == 0 || strcmp("SPEED",value) == 0 || strcmp("DISTANCE",value) == 0) {
				myself = g_node_new (value);
			}
			
			else if(strcmp("ANGLE",value) == 0) {
				arg0 = expression(gs);
				if(arg0 == NULL) return NULL;
				arg1 = expression(gs);
				if(arg1 == NULL) return NULL;
				arg2 = expression(gs);
				if(arg2 == NULL) return NULL;
				arg3 = expression(gs);
				if(arg3 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
				g_node_insert(myself,2,arg2);
				g_node_insert(myself,3,arg3);
			}	
			else if(strcmp("TARGETX",value) == 0 || strcmp("TARGETY",value) == 0) {
				arg0 = expression(gs);
				if(arg0 == NULL) return NULL;
				arg1 = expression(gs);
				if(arg1 == NULL) return NULL;
				arg2 = expression(gs);
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

static GNode* command(GScanner* gs) {
	
	GNode* arg0;
	GNode* arg1;
	GNode* myself;
	
	GTokenType t = g_scanner_get_next_token (gs);
	gchar *value = g_scanner_cur_value (gs).v_identifier;
	switch(t) {
		case G_TOKEN_IDENTIFIER:
			if(strcmp("WAIT",value) == 0 || strcmp("SHOOT",value) == 0) {
				arg0 = expression(gs);
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0); 
			}
			else if(strcmp("ENGINE",value) == 0 || strcmp("POKE",value) == 0) {
				arg0 = expression(gs);
				if(arg0 == NULL) return NULL;
				arg1 = expression(gs);
				if(arg1 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else if(strcmp("GOTO",value) == 0) {
				arg0 = number(gs);
				if(arg0 == NULL) return NULL;
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			else if(strcmp("IF",value) == 0) {
				arg0 = condition(gs);
				if(arg0 == NULL) return NULL;
				//THEN
				switch(g_scanner_get_next_token (gs)) {
					case G_TOKEN_IDENTIFIER:
						if(strcmp("THEN",g_scanner_cur_value (gs).v_identifier) == 0) {
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
				arg1 = number(gs);
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



static GNode* condition(GScanner* gs) {
	GNode* arg0 = expression(gs);
	if(arg0 == NULL) return NULL;
	GNode* arg1 = comparaison(gs);
	if(arg1 == NULL) return NULL;
	GNode* arg2 = expression(gs);
	if(arg2 == NULL) return NULL;
	GNode* myself = g_node_new ("COND");
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	g_node_insert(myself,2,arg2);
	return myself;
}


static GNode* line(GScanner* gs) {
	GNode* arg0 = number(gs);
	if(arg0 == NULL) return NULL;
	GNode* arg1 = command(gs);
	if(arg1 == NULL) return NULL;
	GNode* myself = g_node_new ("LINE");
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	return myself;
	
}	

static GNode* program(GScanner* gs) {
	GNode* currentline;
	GNode* program = g_node_new("PROGRAM");
	int n = 0;
	currentline = line(gs);
	if(currentline == NULL) return NULL;
	g_node_insert (program, n, currentline);
	while(g_scanner_peek_next_token(sc) != G_TOKEN_EOF) {
		n++;
		currentline = line(gs);
		if(currentline == NULL) return NULL;
		g_node_insert (program, n, currentline);
	}
	return program;
}

void* init(char* pathname) {
	
	sc = g_scanner_new (NULL);
	
	symbols(sc);
	
	GScannerConfig* gsc = sc -> config;
	init_config(gsc);
	
	error_token = NULL;
	excepted_token = NULL;
	
	int fd = open(pathname,O_RDONLY);
	if(fd < -1) {
		return NULL;
	}
	
	//printf("symbol %p\n",g_scanner_lookup_symbol(sc,"+"));
	
	g_scanner_input_file (sc,fd);
	GNode* n = program(sc);
	
	if(error_token !=NULL) return NULL;
	
	//printf("depth : %d\n",g_node_max_height (n));
	return n;
}
