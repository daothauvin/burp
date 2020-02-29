#include "syntax_analyse.h"

int main() {
	void* p1 = init("failure_test.txt");
	if(p1==NULL) {
		printf("file one error\n");
		printf(message_error());
		printf("\n");
	}
	void* p2 = init("achieve_test.txt");
	if(p2==NULL) {
		printf("file two error\n");
		printf(message_error());
		printf("\n");
	}
	
	
}