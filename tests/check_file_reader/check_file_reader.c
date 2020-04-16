#include "check_file_reader.h"

Arene a;
Robot jean_paul;
Tree p;
void setup(void) {
	a = create_arene();
	jean_paul = create_robot();
	add_robot(a,jean_paul);
	Robot robot1 = create_robot();
	Robot robot2 = create_robot();
	Robot robot3 = create_robot();
	initialize_robot(robot1,0,0,0,0,0);
	initialize_robot(jean_paul,0,0,0,0,1);
	initialize_robot(robot2,0,0,0,0,2);
	initialize_robot(robot3,0,0,0,0,3);
    assert(a != NULL);
	assert(jean_paul != NULL);
}

void teardown(void) {
	free(jean_paul);
	free(a);
	freeSyntaxAnalyseContest();
	if(p != NULL) freeTree(p);
}

START_TEST(test_bad_expression)
{
    p = init_file_tree(PATH_TO_DIR "/f_expression.txt");
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
    p = init_file_tree(PATH_TO_DIR "/f_goto.txt");
	
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
    p = init_file_tree(PATH_TO_DIR "/f_line.txt");
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
	p = init_file_tree(PATH_TO_DIR "/f_number.txt");
	ck_assert_msg(p == NULL, "A number is not a valid command");
	
	int sizemessage = strlen(message_error());
	char* exceptedmessage = "found 1 when searching a valid command at position 3 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(),exceptedmessage,sizemessage) == 0
	,"Unexcepted Error Message");
}
END_TEST

START_TEST(test_to_big_number)
{
    p = init_file_tree(PATH_TO_DIR "/f_bigint.txt");
	// difficult to test because the script can't update to contain more than the max value on every computer
	if(p == NULL) {
		int sizemessage = strlen(message_error());
		int mysize = snprintf(NULL,0,"found a very high number when searching a number <= %d at position 53 line 1",INT_MAX);
		char* exceptedmessage = malloc(mysize+1);
		snprintf(exceptedmessage,mysize+1,"found a very high number when searching a number <= %d at position 53 line 1",INT_MAX);
		ck_assert_msg(
			sizemessage == mysize && memcmp(message_error(),exceptedmessage,sizemessage) == 0
			,"Unexcepted Error Message");
	}
}
END_TEST

START_TEST(test_unknown_char)
{
    p = init_file_tree(PATH_TO_DIR "/f_unknown.txt");
	ck_assert_msg(p == NULL, "( is not a correct command");
	
	int sizemessage = strlen(message_error());
	char* exceptedmessage = "found UNKNOWN when searching a number at position 8 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(),exceptedmessage,sizemessage) == 0
		,"Unexcepted Error Message");
}
END_TEST

START_TEST(test_cardinal_if)
{
	p = init_file_tree(PATH_TO_DIR "/s_cardinal_if.txt");
	ck_assert_msg(p != NULL, "Init should success");
	int next_line = interprete(0, p,a,jean_paul);
	int excepted_line = 6;
	ck_assert_int_eq(next_line,excepted_line);
}
END_TEST

START_TEST(test_poke_peek_wait)
{
    p = init_file_tree(PATH_TO_DIR "/s_poke_peek_wait.txt");
	ck_assert_msg(p != NULL, "Init should success");
	int start = 0;
	while((start = interprete(start, p,a,jean_paul))!=3)
		;
	int waiting_time = jean_paul -> waiting_time;
	int excepted_waiting_time = 1000;
	ck_assert_int_eq(waiting_time,excepted_waiting_time);
}
END_TEST

START_TEST(test_rand_speed_engine)
{
	
	p = init_file_tree(PATH_TO_DIR "/s_rand_speed_engine.txt");
	ck_assert_msg(p != NULL, "Init should success");

	jean_paul -> speed = 1;
	interprete(0, p,a,jean_paul);
	int angle = jean_paul -> angle;
	int excepted_angle = 7;
	ck_assert_int_eq(angle,excepted_angle);
	ck_assert_msg(jean_paul -> speed > 0,"Robot's speed should be > 0 but found %d",jean_paul -> speed);
	ck_assert_msg(jean_paul -> speed < 4,"Robot's speed should be < 4 but found %d",jean_paul -> speed);

}
END_TEST

START_TEST(test_gps_self)
{
	
	p = init_file_tree(PATH_TO_DIR "/s_gps_self.txt");
	ck_assert_msg(p != NULL, "Init should success");

	jean_paul -> angle = 1;
	jean_paul -> speed = 1;
	interprete(0, p,a,jean_paul);

	int angle = jean_paul -> angle;
	int excepted_angle = 0;
	ck_assert_int_eq(angle,excepted_angle);
	int speed = jean_paul -> speed;
	int excepted_speed = 0;
	ck_assert_int_eq(speed,excepted_speed);

}
END_TEST

START_TEST(test_shoot_distance_angle)
{
	
	p = init_file_tree(PATH_TO_DIR "/s_shoot_distance_angle.txt");
	ck_assert_msg(p != NULL, "Init should success");
	interprete(0, p,a,jean_paul);
	int nb_missiles = a -> nb_missiles;
	int excepted_nb_missiles = 1;
	ck_assert_int_eq(nb_missiles,excepted_nb_missiles);
	ck_assert_msg(a -> list_missile[0] -> owner == jean_paul,"Missile's owner is wrong");
	ck_assert_int_eq((int) a -> list_missile[0] -> angle,45);
	int excepted_explosion_distance = 5;
	int explosion_distance = a -> list_missile[0] -> explosion_distant;
	ck_assert_int_eq(explosion_distance,excepted_explosion_distance);
	
}
END_TEST


START_TEST(test_state_target)
{
	
	p = init_file_tree(PATH_TO_DIR "/s_state_target.txt");
	//write(1,message_error(),strlen(message_error()));
	//printf("\n");
	ck_assert_msg(p != NULL, "Init should success");
	interprete(0, p,a,jean_paul);
	int health_points = jean_paul -> health_points;
	int waiting_time = jean_paul -> waiting_time;
	ck_assert_int_eq(health_points + 1,waiting_time);
	
}
END_TEST


Suite * make_file_reader(void) {
    Suite *s;
    TCase *tc_core, *tc_limits;

    s = suite_create("FileReader");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_cardinal_if);
	tcase_add_test(tc_core, test_poke_peek_wait);
	tcase_add_test(tc_core, test_state_target);
	tcase_add_test(tc_core, test_shoot_distance_angle);
	tcase_add_test(tc_core, test_gps_self);
	tcase_add_test(tc_core, test_rand_speed_engine);
	suite_add_tcase(s, tc_core);

    /* Limits test case */
    tc_limits = tcase_create("Limits");

    tcase_add_test(tc_limits, test_bad_expression);
	tcase_add_test(tc_limits, test_negative_goto);
	tcase_add_test(tc_limits, test_unexcepted_line);
	tcase_add_test(tc_limits, test_unexcepted_number);
	tcase_add_test(tc_limits, test_unknown_char);
	tcase_add_test(tc_limits, test_to_big_number);
    suite_add_tcase(s, tc_limits);

    return s;
}
