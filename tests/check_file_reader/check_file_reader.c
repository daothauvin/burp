#include "check_file_reader.h"

Arene a;
Robot jean_paul;

void setup(void) {
	a = create_arene();
	jean_paul = create_robot();
	add_robot(a,jean_paul);
    assert(a != NULL);
	assert(jean_paul != NULL);
}

void teardown(void) {
	free(jean_paul);
	free(a);
}

START_TEST(test_failure)
{
    void* p = init_file_tree(PATH_TO_DIR "/failure_test.txt");
	ck_assert_msg(p == NULL, "Init should fail");
	if(p==NULL) {
		printf("file one error\n");
		write(1,message_error(),strlen(message_error()));
		printf("\n");
	}
}
END_TEST

START_TEST(test_success)
{
    void* p = init_file_tree(PATH_TO_DIR "/achieve_test.txt");
	ck_assert_msg(p != NULL, "Init should success");
	printf("the tree p : \n");
	print(p);
	interprete(6, p,a,jean_paul);
	interprete(8, p,a,jean_paul);
	printf("waiting time %d\n",jean_paul -> waiting_time);
}
END_TEST


Suite * make_file_reader(void) {
    Suite *s;
    TCase *tc_core, *tc_limits;

    s = suite_create("FileReader");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_success);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
    tc_limits = tcase_create("Limits");

    tcase_add_test(tc_limits, test_failure);
    suite_add_tcase(s, tc_limits);

    return s;
}
