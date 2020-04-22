#include "../../src/model/game/robot.h"
#include "../../src/model/game/robot.c"
#include <check.h>

robot *rob;
robot *rob1;
static void setup(void)
{
  rob = create_robot(0.0, 0.0, 0.0, max_speed, 0);
  rob1 = create_robot(0.0, 0.0, 0.0, max_speed, 1);
}

static void teardown(void)
{
  destroy_robot(&rob);
  destroy_robot(&rob1);
}

START_TEST(test_create_robot)
{
  ck_assert(rob->pos.x == 0.0 && rob->pos.y == 0.0);
  ck_assert(rob->angle == 0.0);
  ck_assert(rob->health_points == 100);
  ck_assert_int_eq(rob->id, 0);
  ck_assert_int_eq(rob->missiles, 0);
  ck_assert(rob->speed == max_speed);
  ck_assert_int_eq(rob->waiting_time, 0);
}
END_TEST

START_TEST(test_update_pos_robot)
{
  update_pos_robot(rob);
  ck_assert(rob->pos.x == max_speed && rob->pos.y == 0.0);
}
END_TEST

START_TEST(test_inflict_damage_from_missile)
{
  point p;
  p.x = 0.0;
  p.y = 0.0;
  inflict_damage_from_missile(rob, p);
  ck_assert(rob->health_points == 100 - damage_explosion_low_range);
}
END_TEST

START_TEST(test_inflict_damage_from_collision)
{
  inflict_damage_from_collision(rob, rob1);
  ck_assert_int_eq(rob->health_points, 98);
  ck_assert_int_eq(rob1->health_points, 98);
}
END_TEST

START_TEST(test_check_collision_robots)
{
  ck_assert(check_collision_robots(rob, rob1) == true);
  rob->pos.x = 1000;
  ck_assert(check_collision_robots(rob, rob1) == false);
}
END_TEST

START_TEST(test_get_robot_health_points)
{
  ck_assert_int_eq(rob->health_points, get_robot_health_points(rob));
}
END_TEST

START_TEST(test_get_robot_angle)
{
  ck_assert_int_eq(rob->angle, get_robot_angle(rob));
}
END_TEST

START_TEST(test_set_robot_angle)
{
  set_robot_angle(rob, 75.0);
  ck_assert(rob->angle == 75.0);
}
END_TEST

START_TEST(test_get_robot_speed)
{
  ck_assert(rob->speed == get_robot_speed(rob));
}
END_TEST

START_TEST(test_set_robot_speed)
{
  assert(set_robot_speed(rob, 120));
  ck_assert(rob->speed == 120);
}
END_TEST

START_TEST(test_get_robot_pos)
{
  point p;
  get_robot_pos(rob, &p);
  ck_assert(p.x == rob->pos.x && p.y == rob->pos.y);
}
END_TEST

START_TEST(test_get_robot_id)
{
  ck_assert_int_eq(get_robot_id(rob), 0);
}
END_TEST

START_TEST(test_get_robot_nb_missiles)
{
  ck_assert_int_eq(0, get_robot_nb_missiles(rob));
  ck_assert_int_eq(get_robot_nb_missiles(rob), rob->missiles);
}
END_TEST

START_TEST(test_set_robot_nb_missiles)
{
  set_robot_nb_missiles(rob, 2);
  ck_assert_int_eq(get_robot_nb_missiles(rob), 2);
}
END_TEST

START_TEST(test_get_waiting_time_robot)
{
  ck_assert_int_eq(get_waiting_time_robot(rob), 0);
  ck_assert_int_eq(get_waiting_time_robot(rob), rob->waiting_time);
}
END_TEST

START_TEST(test_set_waiting_time_robot)
{
  set_waiting_time_robot(rob, 15);
  ck_assert_int_eq(get_waiting_time_robot(rob), 15);
}
END_TEST

START_TEST(test_poke_memory_at)
{
  ck_assert(poke_memory_at(rob, 15, 0));
  ck_assert_int_eq(rob->memory[0], 15);
}
END_TEST

START_TEST(test_peek_memory_at){
  ck_assert(poke_memory_at(rob, 15, 0));
  ck_assert_int_eq(rob->memory[0],15);
  ck_assert_int_eq(rob->memory[0],peek_memory_at(rob,0));
}
END_TEST

Suite *check_robot(void)
{
  Suite *s;
  TCase *tc_core, *tc_limits;

  s = suite_create("Create robot");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_test(tc_core, test_create_robot);
  tcase_add_test(tc_core, test_inflict_damage_from_missile);
  tcase_add_test(tc_core, test_update_pos_robot);
  tcase_add_test(tc_core, test_inflict_damage_from_collision);
  tcase_add_test(tc_core, test_check_collision_robots);
  tcase_add_test(tc_core, test_get_robot_health_points);
  tcase_add_test(tc_core, test_get_robot_angle);
  tcase_add_test(tc_core, test_set_robot_angle);
  tcase_add_test(tc_core, test_get_robot_speed);
  tcase_add_test(tc_core, test_set_robot_speed);
  tcase_add_test(tc_core, test_get_robot_pos);
  tcase_add_test(tc_core, test_get_robot_id);
  tcase_add_test(tc_core, test_get_robot_nb_missiles);
  tcase_add_test(tc_core, test_set_robot_nb_missiles);
  tcase_add_test(tc_core, test_get_waiting_time_robot);
  tcase_add_test(tc_core, test_set_waiting_time_robot);
  tcase_add_test(tc_core, test_poke_memory_at);
  tcase_add_test(tc_core, test_peek_memory_at);
  suite_add_tcase(s, tc_core);

  /* Limits test case */
  tc_limits = tcase_create("Limits");

  //tcase_add_test(tc_limits, test_bad_expression);
  suite_add_tcase(s, tc_limits);

  return s;
}
