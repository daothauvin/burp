#include "../../src/model/game/missile.h"
#include <check.h>

static void setup(void) {}

static void teardown(void) {}

START_TEST(test_create_missile)
{
  ;   
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
    suite_add_tcase(s, tc_core);

    return s;
}
