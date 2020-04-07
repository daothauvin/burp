#include "syntax_analyse.h"
#include "interpreter.h"

int main() {
	Arene a = create_arene();
	Robot jean_paul = create_robot();
	add_robot(a,jean_paul);
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
		interprete(6, p2,a,jean_paul);
		interprete(8, p2,a,jean_paul);
		printf("waiting time %d\n",jean_paul -> waiting_time);
	}
	
	
}