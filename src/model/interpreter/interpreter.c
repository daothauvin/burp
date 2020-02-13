#include "interpreter.h"

static GScanner * sc;

GNode * create_tree() {
	return g_node_new(NULL);
}


//init the configuration
static void init_config(GScannerConfig* gsc) {
	//identifier with one char
	gsc -> scan_identifier_1char = 1;
	//activate symbols
	gsc -> scan_symbols = 1;
}

//give symbols
static void symbols(GScanner* gs) {
	char* plus = "+";
	g_scanner_scope_add_symbol (gs,1,"+",plus);
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
	if(fd < 0) { //TO-DO
		perror("open");
	}
	g_scanner_input_file (sc,fd);
	while(!g_scanner_eof (sc)) {
		GTokenType t = g_scanner_get_next_token (sc);
		printf("%d\n",t);
	}
}