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

START_TEST(test_bad_expression)
{
    void* p = init_file_tree(PATH_TO_DIR "/f_expression.txt");
	ck_assert_msg(p == NULL, "SALUT has been accepted as an expression");
	int sizemessage = strlen(message_error());
	char* exceptedmessage = "found SALUT when searching a valid expression at position 12 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(),exceptedmessage,sizemessage) == 0
	,"Unexcepted Error Message");
}
END_TEST

START_TEST(test_negative_goto)
{
    void* p = init_file_tree(PATH_TO_DIR "/f_goto.txt");
	
	ck_assert_msg(p == NULL, "goto should not accept negative number");
	int sizemessage = strlen(message_error());
	char* exceptedmessage = "found - when searching a number at position 8 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(),exceptedmessage,sizemessage) == 0
	,"Unexcepted Error Message");
}
END_TEST

START_TEST(test_unexcepted_line)
{
    void* p = init_file_tree(PATH_TO_DIR "/f_line.txt");
	ck_assert_msg(p == NULL, "line should be in order");

	int sizemessage = strlen(message_error());
	char* exceptedmessage = "found line 42 when searching line 0 at position 2 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(),exceptedmessage,sizemessage) == 0
	,"Unexcepted Error Message");
}
END_TEST


START_TEST(test_unexcepted_number)
{
    void* p = init_file_tree(PATH_TO_DIR "/f_number.txt");
	ck_assert_msg(p == NULL, "A number is not a valid command");
	
	int sizemessage = strlen(message_error());
	char* exceptedmessage = "found 1 when searching a valid command at position 3 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(),exceptedmessage,sizemessage) == 0
	,"Unexcepted Error Message");
}
END_TEST

START_TEST(test_cardinal_and_if)
{
    void* p = init_file_tree(PATH_TO_DIR "/s_cardinal_if.txt");
	ck_assert_msg(p != NULL, "Init should success");
	ck_assert_msg(interprete(0, p,a,jean_paul) == 6,"Should enter in if and go to line 6");
}
END_TEST

START_TEST(test_poke_peek_wait)
{
    void* p = init_file_tree(PATH_TO_DIR "/s_poke_peek_wait.txt");
	ck_assert_msg(p != NULL, "Init should success");
	int start = 0;
	while((start = interprete(start, p,a,jean_paul))!=3)
		;
	
	ck_assert_msg(jean_paul -> waiting_time == 1000,"Robot Should have a waiting time of 1000");
}
END_TEST

Suite * make_file_reader(void) {
    Suite *s;
    TCase *tc_core, *tc_limits;

    s = suite_create("FileReader");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_cardinal_and_if);
	tcase_add_test(tc_core, test_poke_peek_wait);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
    tc_limits = tcase_create("Limits");

    tcase_add_test(tc_limits, test_bad_expression);
	tcase_add_test(tc_limits, test_negative_goto);
	tcase_add_test(tc_limits, test_unexcepted_line);
	tcase_add_test(tc_limits, test_unexcepted_number);
	
    suite_add_tcase(s, tc_limits);

    return s;
}
