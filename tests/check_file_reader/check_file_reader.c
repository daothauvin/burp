#include "check_file_reader.h"

arena* a;
robot* jean_paul;
Tree p;
void setup(void) {
	a = create_arena();
	jean_paul = create_robot(0,0,0,0,0, 	"rb1");
	robot* robot1 = create_robot(0,0,0,0,1, "rb2");
	robot* robot2 = create_robot(0,0,0,0,2, "rb3");
	robot* robot3 = create_robot(0,0,0,0,3, "rb4");
	add_robot(a,jean_paul);
	add_robot(a,robot1);
	add_robot(a,robot2);
	add_robot(a,robot3);
}

static void teardown(void)
{
	freeArena(&a);
	freeSyntaxAnalyseContest();
	if (p != NULL)
		freeTree(p);
	freeWarnings();
}

START_TEST(test_bad_expression)
{
	p = init_file_tree(PATH_TO_DIR "/f_expression.txt");
	ck_assert_msg(p == NULL, "SALUT has been accepted as an expression");
	int sizemessage = strlen(message_error());
	char *exceptedmessage = "found SALUT when searching a valid expression at"
		" position 12 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(), 
		exceptedmessage, sizemessage) == 0, "Unexcepted Error Message");
}
END_TEST

START_TEST(test_negative_goto)
{
	p = init_file_tree(PATH_TO_DIR "/f_goto.txt");

	ck_assert_msg(p == NULL, "goto should not accept negative number");
	int sizemessage = strlen(message_error());
	char *exceptedmessage=
		"found - when searching a number at position 8 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(), 
		exceptedmessage, sizemessage) == 0, "Unexcepted Error Message");
}
END_TEST

START_TEST(test_unexcepted_line)
{
	p = init_file_tree(PATH_TO_DIR "/f_line.txt");
	ck_assert_msg(p == NULL, "line should be in order");

	int sizemessage = strlen(message_error());
	char *exceptedmessage = 
		"found line 42 when searching line 0 at position 2 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && memcmp(message_error(), 
		exceptedmessage, sizemessage) == 0, "Unexcepted Error Message");
}
END_TEST

START_TEST(test_unexcepted_number)
{
	p = init_file_tree(PATH_TO_DIR "/f_number.txt");
	ck_assert_msg(p == NULL, "A number is not a valid command");

	int sizemessage = strlen(message_error());
	char *exceptedmessage = 
		"found 1 when searching a valid command at position 3 line 1";
	ck_assert_msg(sizemessage == strlen(exceptedmessage) 
		&& memcmp(message_error(), exceptedmessage, sizemessage) == 0, 
		"Unexcepted Error Message");
}
END_TEST

START_TEST(test_to_big_number)
{
	p = init_file_tree(PATH_TO_DIR "/f_bigint.txt");
	// difficult to test because the script can't update 
	//to contain more than the max value on every computer
	if (p == NULL)
	{
		int sizemessage = strlen(message_error());
		int mysize = 
			snprintf(NULL, 0, 
			"found a very high number when searching a number <= %d at"
			" position 53 line 1", INT_MAX);
		char *exceptedmessage = malloc(mysize + 1);
		snprintf(exceptedmessage, mysize + 1, 
			"found a very high number when searching a number <= %d at"
			" position 53 line 1", INT_MAX);
		ck_assert_msg(
			sizemessage == mysize 
			&& memcmp(message_error(), exceptedmessage, sizemessage) == 0, 
			"Unexcepted Error Message");
		free(exceptedmessage);
	}

}
END_TEST

START_TEST(test_unknown_char)
{
	p = init_file_tree(PATH_TO_DIR "/f_unknown.txt");
	ck_assert_msg(p == NULL, "( is not a correct command");

	int sizemessage = strlen(message_error());
	char *exceptedmessage = 
		"found UNKNOWN when searching a number at position 8 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && 
		memcmp(message_error(), exceptedmessage, sizemessage) == 0, 
		"Unexcepted Error Message");
}
END_TEST

START_TEST(test_empty)
{
	p = init_file_tree(PATH_TO_DIR "/f_empty.txt");
	//write(1,message_error(),strlen(message_error()));
	//printf("\n");
	
	ck_assert_msg(p == NULL, "Empty Script should not success");

	int sizemessage = strlen(message_error());
	char* exceptedmessage = "found UNKNOWN when searching a number at position 1 line 1";
	ck_assert_msg(
		sizemessage == strlen(exceptedmessage) && 
		memcmp(message_error(),exceptedmessage,sizemessage) == 0,
		"Unexcepted Error Message");
}
END_TEST


START_TEST(test_cardinal_if)
{
	p = init_file_tree(PATH_TO_DIR "/s_cardinal_if.txt");

	ck_assert_msg(p != NULL, "Init should success");
	//printTree(p);
	int next_line = interprete(0, p,a,jean_paul);

	ck_assert_ptr_eq(getWarnings(),NULL);
	int excepted_line = 6;
	ck_assert_int_eq(next_line,excepted_line);
}
END_TEST


START_TEST(test_cardinal_if_fail)
{
	p = init_file_tree(PATH_TO_DIR "/s_cardinal_if_2.txt");
	ck_assert_msg(p != NULL, "Init should success");

	int next_line = interprete(0, p,a,jean_paul);

	ck_assert_ptr_eq(getWarnings(),NULL);
	int excepted_line = 1;
	ck_assert_int_eq(next_line,excepted_line);
}
END_TEST

START_TEST(test_poke_peek_wait)
{
	p = init_file_tree(PATH_TO_DIR "/s_poke_peek_wait.txt");
	
	ck_assert_msg(p != NULL, "Init should success");
	int start = 0;
	while ((start = interprete(start, p, a, jean_paul)) != 3)
		;

	ck_assert_ptr_eq(getWarnings(),NULL);
	int waiting_time = get_waiting_time_robot(jean_paul);
	int excepted_waiting_time = 1000;
	ck_assert_int_eq(waiting_time,excepted_waiting_time);
}
END_TEST

START_TEST(test_rand_speed_engine)
{

	p = init_file_tree(PATH_TO_DIR "/s_rand_speed_engine.txt");
	
	ck_assert_msg(p != NULL, "Init should success");

	set_robot_speed(jean_paul,1);
	interprete(0, p,a,jean_paul);

	ck_assert_ptr_eq(getWarnings(),NULL);
	int angle = get_robot_angle(jean_paul);
	int excepted_angle = 7;
	ck_assert_int_eq(angle,excepted_angle);
	ck_assert_msg(get_robot_speed(jean_paul) > 0,
		"Robot's speed should be > 0 but found %d",get_robot_speed(jean_paul));
	ck_assert_msg(get_robot_speed(jean_paul) < 4,
		"Robot's speed should be < 4 but found %d",get_robot_speed(jean_paul));

}
END_TEST


START_TEST(test_gps_self)
{

	p = init_file_tree(PATH_TO_DIR "/s_gps_self.txt");
	ck_assert_msg(p != NULL, "Init should success");

	set_robot_angle(jean_paul,1);
	set_robot_speed(jean_paul,1);
	interprete(0, p,a,jean_paul);

	ck_assert_ptr_eq(getWarnings(),NULL);
	int angle = get_robot_angle(jean_paul);
	int excepted_angle = 0;
	ck_assert_int_eq(angle,excepted_angle);
	int speed = get_robot_speed(jean_paul);
	int excepted_speed = 0;
	ck_assert_int_eq(speed,excepted_speed);

}
END_TEST

START_TEST(test_shoot_distance_angle)
{

	p = init_file_tree(PATH_TO_DIR "/s_shoot_distance_angle.txt");
	ck_assert_msg(p != NULL, "Init should success");
	interprete(0, p,a,jean_paul);

	ck_assert_ptr_eq(getWarnings(),NULL);
	int nb_missiles = get_nb_missiles_arena(a);
	int excepted_nb_missiles = 1;
	ck_assert_int_eq(nb_missiles,excepted_nb_missiles);
	ck_assert_msg(get_missile_owner(get_missile_index(a,0)) == jean_paul,
		"Missile's owner is wrong");
	ck_assert_int_eq((int) get_missile_angle(get_missile_index(a,0)),-45);
	int excepted_explosion_distance = 5;
	int explosion_distance = get_explosion_distant(get_missile_index(a,0));
	ck_assert_int_eq(explosion_distance,excepted_explosion_distance);
	
}
END_TEST


START_TEST(test_state_target)
{
	
	p = init_file_tree(PATH_TO_DIR "/s_state_target.txt");
	
	ck_assert_msg(p != NULL, "Init should success");
	interprete(0, p,a,jean_paul);

	ck_assert_ptr_eq(getWarnings(),NULL);
	int health_points = get_robot_health_points(jean_paul);
	int waiting_time = get_waiting_time_robot(jean_paul);
	ck_assert_int_eq(health_points + 1,waiting_time);
	
	
}
END_TEST

START_TEST(test_memory_number_to_big)
{
	p = init_file_tree(PATH_TO_DIR "/w_memory_size.txt");
	ck_assert_msg(p != NULL, "Init should success");
	
	interprete(0, p,a,jean_paul);
	struct warning_message * message = getWarnings();
	ck_assert_ptr_ne(NULL,message);
	ck_assert_ptr_eq(message->next_message,NULL);
	ck_assert_str_eq(message->message,"robot memory 300 is invalid (max: 255)");
	
	
}
END_TEST

START_TEST(test_gpsx_dead_robot)
{
	p = init_file_tree(PATH_TO_DIR "/w_gps_on_dead_robots.txt");
	ck_assert_msg(p != NULL, "Init should success");
	robot* r1 = get_robot_per_id(a,1);
	remove_robot(a,r1);
	destroy_robot(&r1);
	interprete(0, p,a,jean_paul);
	struct warning_message * message = getWarnings();
	ck_assert_ptr_ne(NULL,message);
	ck_assert_ptr_eq(message->next_message,NULL);
	ck_assert_str_eq(message->message,"gpsx on dead robot 1");
}
END_TEST

START_TEST(test_gpsy_dead_robot)
{
	p = init_file_tree(PATH_TO_DIR "/w_gps_on_dead_robots.txt");
	ck_assert_msg(p != NULL, "Init should success");
	robot* r1 = get_robot_per_id(a,1);
	remove_robot(a,r1);
	destroy_robot(&r1);
	interprete(1, p,a,jean_paul);
	struct warning_message * message = getWarnings();
	ck_assert_ptr_ne(NULL,message);
	ck_assert_ptr_eq(message->next_message,NULL);
	ck_assert_str_eq(message->message,"gpsy on dead robot 1");
}
END_TEST

START_TEST(test_negative_waiting_time)
{
	p = init_file_tree(PATH_TO_DIR "/w_negative_waiting_time.txt");
	ck_assert_msg(p != NULL, "Init should success");
	interprete(0, p,a,jean_paul);
	struct warning_message * message = getWarnings();
	ck_assert_ptr_ne(NULL,message);
	ck_assert_ptr_eq(message->next_message,NULL);
	ck_assert_str_eq(message->message,
		"waiting time -15 should not be negative");
}
END_TEST


START_TEST(test_negative_distance)
{
	p = init_file_tree(PATH_TO_DIR "/w_negative_distance.txt");
	ck_assert_msg(p != NULL, "Init should success");
	interprete(0, p,a,jean_paul);
	struct warning_message * message = getWarnings();
	ck_assert_ptr_ne(NULL,message);
	
	ck_assert_str_eq(message->message,
		"distance -5 should not be negative");
	
	message = message -> next_message;
	ck_assert_ptr_ne(NULL,message);
	ck_assert_ptr_eq(message->next_message,NULL);
	ck_assert_str_eq(message->message,
		"distance -10 should not be negative");
}
END_TEST



START_TEST(test_robot_number_to_big)
{
	p = init_file_tree(PATH_TO_DIR "/w_robot_number.txt");
	ck_assert_msg(p != NULL, "Init should success");
	interprete(0, p,a,jean_paul);
	struct warning_message * message = getWarnings();
	ck_assert_ptr_ne(NULL,message);
	ck_assert_ptr_eq(message->next_message,NULL);
	ck_assert_str_eq(message->message,"robot number 6 is invalid (max: 3)");


}
END_TEST



Suite *make_file_reader(void)
{
	Suite *s;
	TCase *tc_core, *tc_limits, *tc_warnings;

	s = suite_create("FileReader");

	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_cardinal_if);
	tcase_add_test(tc_core, test_cardinal_if_fail);
	tcase_add_test(tc_core, test_poke_peek_wait);
	tcase_add_test(tc_core, test_state_target);
	tcase_add_test(tc_core, test_shoot_distance_angle);
	tcase_add_test(tc_core, test_gps_self);
	tcase_add_test(tc_core, test_rand_speed_engine);
	
	suite_add_tcase(s, tc_core);

	/* Limits test case */
	tc_limits = tcase_create("Limits");
	tcase_add_checked_fixture(tc_limits, setup, teardown);
	tcase_add_test(tc_limits, test_bad_expression);
	tcase_add_test(tc_limits, test_negative_goto);
	tcase_add_test(tc_limits, test_unexcepted_line);
	tcase_add_test(tc_limits, test_unexcepted_number);
	tcase_add_test(tc_limits, test_unknown_char);
	tcase_add_test(tc_limits, test_to_big_number);
	tcase_add_test(tc_limits, test_empty);
    suite_add_tcase(s, tc_limits);
	
	tc_warnings = tcase_create("Warnings");
	tcase_add_checked_fixture(tc_warnings, setup, teardown);
	tcase_add_test(tc_warnings, test_memory_number_to_big);
	tcase_add_test(tc_warnings, test_robot_number_to_big);
	tcase_add_test(tc_warnings, test_gpsx_dead_robot);
	tcase_add_test(tc_warnings, test_gpsy_dead_robot);
	tcase_add_test(tc_warnings, test_negative_waiting_time);
	tcase_add_test(tc_warnings, test_negative_distance);
	
	suite_add_tcase(s, tc_warnings);

	return s;
}
