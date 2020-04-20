#include "../../src/model/game/robot.h"
#include "../../src/model/game/robot.c"
#include <check.h>


robot *rob;
static void setup(void) {
  rob = create_robot(0.0,0.0,0.0,max_speed,0);
}

static void teardown(void) {
  destroy_robot(&rob);
}

START_TEST(test_create_robot)
{
  ck_assert(rob->pos.x == 0.0 && rob->pos.y == 0.0);
  ck_assert(rob->angle == 0.0);
  ck_assert(rob->health_points == 100);
  ck_assert_int_eq(rob->id,0);
  ck_assert_int_eq(rob->missiles,0);
  ck_assert(rob->speed == max_speed);
  ck_assert_int_eq(rob->waiting_time,0);
}
END_TEST

START_TEST(test_update_pos_robot){
  update_pos_robot(rob);
  ck_assert(rob->pos.x == max_speed && rob->pos.y == 0.0);
}
END_TEST

START_TEST(test_inflict_damage_from_missile){
  point p;
  p.x = 0.0;
  p.y = 0.0;
  inflict_damage_from_missile(rob,p);
  ck_assert(rob->health_points == 100 - damage_explosion_low_range);
}
END_TEST

Suite * check_robot (void) {
    Suite *s;
    TCase *tc_core, *tc_limits;

    s = suite_create("Create robot");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
	  tcase_add_test(tc_core, test_create_robot);
    tcase_add_test(tc_core,test_inflict_damage_from_missile);
    tcase_add_test(tc_core,test_update_pos_robot);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
    tc_limits = tcase_create("Limits");

    //tcase_add_test(tc_limits, test_bad_expression);
    suite_add_tcase(s, tc_limits);

    return s;
}
