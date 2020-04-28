#include "../../src/model/game/arene.h"
#include "../../src/model/game/missile.h"
#include "../../src/model/game/arene.c"
#include "../../src/define.h"
#include <check.h>

robot *rob;
arena *a;

static void setup(void)
{
  a = create_arena();
  rob = create_robot(0, 0, 0, 0, 0);
  robot *robot1 = create_robot(0, 0, 0, 0, 1);
  robot *robot2 = create_robot(0, 0, 0, 0, 2);
  robot *robot3 = create_robot(0, 0, 0, 0, 3);
  add_robot(a, rob);
  add_robot(a, robot1);
  add_robot(a, robot2);
  add_robot(a, robot3);
}

static void teardown(void)
{
  freeArena(&a);
}

START_TEST(test_create_arena)
{
  ck_assert_int_eq(get_nb_missiles_arena(a), 0);
  ck_assert_int_eq(get_nb_robot_arena(a), 4);
}
END_TEST

START_TEST(test_add_missile)
{
  int nb_test_missiles = 10;
  missile **missiles_test = malloc(sizeof(missile *) * 10);
  for (int i = 0; i < nb_test_missiles; i++)
  {
    missiles_test[i] = create_missile(10.0, 10.0, 10.0, rob, max_range_explosion);
  }
  for (size_t i = 0; i < 8; i++)
  {
    ck_assert_int_eq(get_nb_missiles_arena(a), add_missile(a, missiles_test[i]));
  }
  ck_assert_int_eq(-1, add_missile(a, missiles_test[8]));
  for (size_t i = 8; i < nb_test_missiles; i++)
  {
    destroy_missile(&(missiles_test[i]));
  }
  free(missiles_test);
}
END_TEST

START_TEST(test_remove_missile)
{
  int nb_test_missiles = 10;
  missile **missiles_test = malloc(sizeof(missile *) * 10);
  for (int i = 0; i < nb_test_missiles; i++) {
    missiles_test[i] = create_missile(10.0, 10.0, 10.0, rob, max_range_explosion);
  }
  
  for (size_t i = 0; i < 8; i++) {
    ck_assert_int_eq(get_nb_missiles_arena(a), add_missile(a, missiles_test[i]));
  }
  ck_assert(remove_missile(a, missiles_test[5]));
  
  for (size_t i = 8; i < nb_test_missiles; i++) {
    destroy_missile(&(missiles_test[i]));
  }
  free(missiles_test);
}
END_TEST

START_TEST(test_add_robot)
{
}
END_TEST

START_TEST(test_remove_robot)
{
}
END_TEST

Suite *check_arena(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Create arena");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_test(tc_core, test_create_arena);
  tcase_add_test(tc_core, test_add_missile);
  tcase_add_test(tc_core, test_add_robot);
  tcase_add_test(tc_core, test_remove_missile);
  tcase_add_test(tc_core, test_remove_robot);
  suite_add_tcase(s, tc_core);

  return s;
}
