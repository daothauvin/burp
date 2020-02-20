#include "interpreter.h"

static GScanner * sc;

static GNode* condition(GScanner* gs);

GNode * create_tree() {
	return g_node_new(NULL);
}


//init the configuration
static void init_config(GScannerConfig* gsc) {
	//identifier with one char
	gsc -> scan_identifier_1char = 1;
	//activate symbols
	//gsc -> scan_symbols = 1;
	//return token symbol if find symbol
	gsc -> symbol_2_token = 1;
}


//give symbols
static void symbols(GScanner* gs) {
	//put the scope to 0
	g_scanner_set_scope (gs,0);
	//add + symbol -> do not work
	g_scanner_scope_add_symbol (gs,0,"+","+");
	
}

//number
static GNode* number(GScanner* gs) {
	GTokenType t = g_scanner_get_next_token (gs);
	switch(t) {
		case G_TOKEN_INT:
			if(g_scanner_cur_value (gs).v_int < 0 ) {
				printf("except a positive number");
				exit(1);
			}
			else {
				int value = g_scanner_cur_value (gs).v_int;
				return g_node_new (&value);
			}
			break;
		default:
			printf("except a number");
			exit(1);
	}
}


//operator
static GNode* operator(GScanner* gs) { 
	switch(g_scanner_get_next_token (gs)) {
		case '+' :
			break;
		case '-' :
			break;
		case '*' :
			break;
		case '/' :
			break;
		case '%' :
			break;
		default :
			fprintf(stderr,"unexcepted operator\n");
			exit(1);
	}
	return g_node_new (NULL);
}

//comparaison
static GNode* comparaison(GScanner* gs) { 
	switch(g_scanner_get_next_token (gs)) {
		case '<' :
			break;
		case '<=' :
			break;
		case '=' :
			break;
		case '<>' :
			break;
		case '>' :
			break;
		default :
			fprintf(stderr,"unexcepted comparaison\n");
			exit(1);
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
			arg1 = operator(gs);
			arg2 = expression(gs);
			myself = g_node_new (&op);
			if(g_scanner_get_next_token (gs) != G_TOKEN_RIGHT_PAREN) 
				fprintf(stderr,"need to close parenthesis\n");
			g_node_insert(myself,0,arg0);
			g_node_insert(myself,1,arg1);
			g_node_insert(myself,2,arg2);
			break;
			
		case G_TOKEN_IDENTIFIER:
			if(strcmp("PPEK",value) == 0 || strcmp("RAND",value) == 0 || strcmp("STATE",value) == 0 || strcmp("GPSX",value) == 0 || strcmp("GPSY",value) == 0) {
				arg0 = expression(gs);
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			
			else if(strcmp("CARDINAL",value) == 0 || strcmp("SELF",value) == 0 || strcmp("SPEED",value) == 0 || strcmp("DISTANCE",value) == 0) {
				myself = g_node_new (value);
			}
			
			else if(strcmp("ANGLE",value) == 0) {
				arg0 = expression(gs);
				arg1 = expression(gs);
				arg2 = expression(gs);
				arg3 = expression(gs);
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
				g_node_insert(myself,2,arg2);
				g_node_insert(myself,3,arg3);
			}	
			else if(strcmp("TARGETX",value) == 0 || strcmp("TARGETY",value) == 0) {
				arg0 = expression(gs);
				arg1 = expression(gs);
				arg2 = expression(gs);
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
				g_node_insert(myself,2,arg2);
				
					
				
			}
			else {
				fprintf(stderr,"unexcepted expression\n");
			}
			break;
		default :
			fprintf(stderr,"unexcepted expression\n");
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
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0); 
			}
			else if(strcmp("ENGINE",value) == 0 || strcmp("POKE",value) == 0) {
				arg0 = expression(gs);
				arg1 = expression(gs);
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else if(strcmp("GOTO",value) == 0) {
				arg0 = number(gs);
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
			}
			else if(strcmp("IF",value) == 0) {
				arg0 = condition(gs);
				//THEN
				switch(g_scanner_get_next_token (gs)) {
					case G_TOKEN_IDENTIFIER:
					if(strcmp("THEN",g_scanner_cur_value (gs).v_identifier) == 0) {
						//ok
					}
					else {
						printf("excepted THEN\n");
						exit(1);
					}
					break;
					default :
						printf("excepted THEN\n");
						exit(1);
				}
				arg1 = number(gs);
				myself = g_node_new (value);
				g_node_insert(myself,0,arg0);
				g_node_insert(myself,1,arg1);
			}
			else {
				fprintf(stderr,"> unexcepted command\n");
				exit(1);
			}
			break;
		default :
			fprintf(stderr,"unexcepted command\n");
			exit(1);
	}
	return myself;
}



static GNode* condition(GScanner* gs) {
	GNode* arg0 = expression(gs);
	GNode* arg1 = comparaison(gs);
	GNode* arg2 = expression(gs);
	GNode* myself = g_node_new ("COND");
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	g_node_insert(myself,2,arg2);
	return myself;
}


static GNode* line(GScanner* gs) {
	GNode* arg0 = number(gs);
	GNode* arg1 = command(gs);
	GNode* myself = g_node_new ("LINE");
	g_node_insert(myself,0,arg0);
	g_node_insert(myself,1,arg1);
	return myself;
	
}	

static GNode* program(GScanner* gs) {
	GNode* program = g_node_new("PROGRAM");
	int n = 0;
	g_node_insert (program, n, line(gs));
	while(g_scanner_peek_next_token(sc) != G_TOKEN_EOF) {
		n++;
		g_node_insert (program, n, line(gs));
	}
	return program;
}

//g_scanner_peek_next_token ();
//g_scanner_get_next_token ()
//g_scanner_eof (GScanner *scanner);
void init(char* pathname) {
	
	sc = g_scanner_new (NULL);
	symbols(sc);
	GScannerConfig* gsc = sc -> config;
	init_config(gsc);
	int fd = open(pathname,O_RDONLY);
	printf("symbol %p\n",g_scanner_lookup_symbol(sc,"+"));
	
	if(fd < 0) { //TO-DO
		perror("open");
	}
	g_scanner_input_file (sc,fd);
	GNode* n = program(sc);
	printf("depth : %d\n",g_node_max_height (n));
	/*
	while(!g_scanner_eof (sc)) {
		GTokenType t = g_scanner_get_next_token (sc);
		printf("token : %d\n",t);
		GTokenValue v = g_scanner_cur_value (sc);
		
		switch(t) {
			case G_TOKEN_SYMBOL:
				printf("symbol value : %s\n",(char*)v.v_symbol);
				break;
			case G_TOKEN_IDENTIFIER:
				printf("identifier value : %s\n",v.v_identifier);
				break;
			case '+':
				printf("+\n");
				break;
			default :
				printf("other\n");
		}
	}
	*/
}
