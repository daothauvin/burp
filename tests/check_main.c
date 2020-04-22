#include <check.h>
#include <stdlib.h>
#include "check_header.h"


int main(void) {
    int number_failed = 0;
    SRunner *sr;

    sr = srunner_create(check_robot());
    srunner_add_suite(sr,check_missile());
    srunner_add_suite(sr,check_arena());
    srunner_add_suite(sr,check_commands());
	srunner_add_suite(sr,make_file_reader());
    
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
