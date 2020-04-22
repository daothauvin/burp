#include "../../src/model/game/missile.h"
#include "../../src/model/game/missile.c"
#include <check.h>
robot* rob;
missile *m;
static void setup(void) {
  rob = create_robot(0.0,0.0,0.0,0.0,0);
  m = create_missile(0.0,0.0,0.0,rob,0.0);
}

static void teardown(void) {
  destroy_missile(&m);
  destroy_robot(&rob);
}

START_TEST(test_create_missile)
{
  ck_assert(m->angle == 0.0);
  ck_assert(m->pos.x == 0.0 && m->pos.y == 0.0);
  ck_assert(m->speed == missile_speed);
  ck_assert(m->parcouru_distant == 0.0);
  ck_assert(m->explosion_distant == 0.0);
  ck_assert(m->will_explode == false);
  ck_assert(m->owner == rob);
}
END_TEST

START_TEST(test_update_pos_missile)
{
  update_pos_missile(m);
  m->angle = 90.0;
  m->explosion_distant = 9000;
  update_pos_missile(m);
  ck_assert_int_eq((int)m->pos.y,500);
  ck_assert_int_eq((int)m->pos.x,0);
}
END_TEST

START_TEST(test_explode)
{
  point p;
  ck_assert(!explode(m,&p));
  m->will_explode = true;
  ck_assert(explode(m,&p));
  ck_assert(m->pos.x == p.x && m->pos.y == p.y);
}
END_TEST

START_TEST(test_will_explode)
{
  update_pos_missile(m);
  ck_assert(m->will_explode == true);
  ck_assert(will_explode(m)==true);
}
END_TEST

START_TEST(test_collision_with_missiles)
{
  collision_with_missiles(rob,m);
  ck_assert(will_explode(m)==true);
}
END_TEST

START_TEST(test_get_missile_angle)
{
  m->angle = 123.0;
  ck_assert(get_missile_angle(m) == m->angle);
}
END_TEST

START_TEST(test_get_missile_speed)
{
  m->speed = 123.0;
  ck_assert(get_missile_speed(m) == m->speed);
}
END_TEST

START_TEST(test_get_explosion_distant)
{
  m->explosion_distant = 123.0;
  ck_assert(get_explosion_distant(m) == m->explosion_distant);
}
END_TEST

START_TEST(test_get_parcouru_distant)
{
  m->parcouru_distant = 123.0;
  ck_assert(get_parcouru_distant(m) == m->parcouru_distant);
}
END_TEST

START_TEST(test_get_missile_pos)
{
  m->pos.x = 1545;
  m->pos.y = 8751;
  point p;
  get_missile_pos(m,&p);
  ck_assert(m->pos.x == p.x);
  ck_assert(m->pos.y == p.y);
}
END_TEST

START_TEST(test_get_missile_owner)
{
  ck_assert_ptr_eq(get_missile_owner(m),rob);
}
END_TEST

Suite * check_missile (void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Create missile");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
	  tcase_add_test(tc_core, test_create_missile);
    tcase_add_test(tc_core,test_update_pos_missile);
    tcase_add_test(tc_core,test_explode);
    tcase_add_test(tc_core,test_will_explode);
    tcase_add_test(tc_core,test_collision_with_missiles);
    tcase_add_test(tc_core,test_get_missile_angle);
    tcase_add_test(tc_core,test_get_missile_speed);
    tcase_add_test(tc_core,test_get_explosion_distant);
    tcase_add_test(tc_core,test_get_parcouru_distant);
    tcase_add_test(tc_core,test_get_missile_pos);
    tcase_add_test(tc_core,test_get_missile_owner);
    suite_add_tcase(s, tc_core);

    return s;
}
