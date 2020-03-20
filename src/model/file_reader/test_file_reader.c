#include "syntax_analyse.h"
#include "interpreter.h"

int main() {
	void* p1 = init("failure_test.txt");
	if(p1==NULL) {
		printf("file one error\n");
		printf(message_error());
		printf("\n");
	}
	else {
		printf("the tree p1 : \n");
		print(p1);
	}
	void* p2 = init("achieve_test.txt");
	if(p2==NULL) {
		printf("file two error\n");
		printf(message_error());
		printf("\n");
	}
	else {
		printf("the tree p2 : \n");
		print(p2);
		interprete(3, p2,NULL,NULL);
	}
	
	
}