#include "../../src/model/game/commands.h"
#include <check.h>

robot *rob;
arena *a;

static void setup(void)
{
  a = create_arena();
  rob = create_robot(7000.0, 3500.0, 14.0, 27.0, 0,"ccc");
  robot *robot1 = create_robot(0, 0, 0, 0, 1,"bbb");
  robot *robot2 = create_robot(0, 0, 0, 0, 2,"aaa");
  add_robot(a, rob);
  add_robot(a, robot1);
  add_robot(a, robot2);
}

static void teardown(void)
{
  freeArena(&a);
}

START_TEST(test_wait_robot)
{
  ck_assert_int_eq(wait_robot(rob, 15), 15);
  ck_assert_int_eq(get_waiting_time_robot(rob), 15);
}
END_TEST

START_TEST(test_poke_peek)
{
  ck_assert(poke(rob, 14, 57) == true);
  ck_assert_int_eq(peek(rob, 14), 57);
}
END_TEST

START_TEST(test_cardinal)
{
  ck_assert_int_eq(cardinal(a), get_nb_robot_arena(a));
  ck_assert_int_eq(cardinal(a), 3);
}
END_TEST

START_TEST(test_self)
{
  ck_assert_int_eq(get_robot_id(get_robot_index(a, 2)),  
    self(get_robot_index(a, 2)));
}
END_TEST

START_TEST(test_speed)
{
  ck_assert_int_eq((int)speed(rob), 27);
}
END_TEST

START_TEST(test_state)
{
  ck_assert_int_eq(state(a, 0), 100);
}
END_TEST

START_TEST(test_gpsx)
{
  ck_assert_int_eq((int)gpsx(a, 0), 7000);
}
END_TEST

START_TEST(test_gpsy)
{
  ck_assert_int_eq((int)gpsy(a, 0), 3500);
}
END_TEST

START_TEST(test_engine)
{
  engine(rob, 45, 75);
  ck_assert_int_eq(get_robot_angle(rob), 45);
  ck_assert_int_eq(get_robot_speed(rob), 75);
}
END_TEST

START_TEST(test_shoot)
{
  ck_assert(shoot(rob, a, 45, max_range_explosion) == true);
  ck_assert_int_eq(get_nb_missiles_arena(a), 1);
  ck_assert_int_eq(get_robot_nb_missiles(rob), 1);

  ck_assert(shoot(rob, a, 45, max_range_explosion) == true);
  ck_assert_int_eq(get_nb_missiles_arena(a), 2);
  ck_assert_int_eq(get_robot_nb_missiles(rob), 2);

  ck_assert(shoot(rob, a, 45, max_range_explosion) == false);
  ck_assert_int_eq(get_nb_missiles_arena(a), 2);
  ck_assert_int_eq(get_robot_nb_missiles(rob), 2);

  remove_missile(a, get_missile_index(a, 0));
  ck_assert_int_eq(get_nb_missiles_arena(a), 1);
  ck_assert_int_eq(get_robot_nb_missiles(rob), 1);

  ck_assert(shoot(rob, a, 45, max_range_explosion) == true);
  ck_assert_int_eq(get_nb_missiles_arena(a), 2);
  ck_assert_int_eq(get_robot_nb_missiles(rob), 2);
}
END_TEST

START_TEST(test_angle)
{
     ck_assert_int_eq(angle(0,0,3,3),45);
     ck_assert_int_eq(angle(3,3,3,3),0);
}
END_TEST

START_TEST(test_targetx)
{
    ck_assert_int_eq((int)targetx(0,90,4),0);
    ck_assert_int_eq((int)targetx(0,0,4),4);
}
END_TEST

START_TEST(test_targety)
{
    ck_assert_int_eq((int)targety(0,90,4),4);
    ck_assert_int_eq((int)targety(0,0,4),0);
}
END_TEST

START_TEST(test_distance)
{
  ck_assert_int_eq((int)distance(14,17,25,25),13);
}
END_TEST

Suite *check_commands(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Create commands");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_test(tc_core, test_wait_robot);
  tcase_add_test(tc_core, test_poke_peek);
  tcase_add_test(tc_core, test_cardinal);
  tcase_add_test(tc_core, test_self);
  tcase_add_test(tc_core, test_speed);
  tcase_add_test(tc_core, test_state);
  tcase_add_test(tc_core, test_gpsx);
  tcase_add_test(tc_core, test_gpsy);
  tcase_add_test(tc_core, test_engine);
  tcase_add_test(tc_core, test_shoot);
  tcase_add_test(tc_core, test_angle);
  tcase_add_test(tc_core, test_targetx);
  tcase_add_test(tc_core, test_targety);
  tcase_add_test(tc_core, test_distance);
  suite_add_tcase(s, tc_core);

  return s;
}
