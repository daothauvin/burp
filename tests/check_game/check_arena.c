#include "../../src/model/game/missile.h"
#include <check.h>

void setup(void) {}

void teardown(void) {}

START_TEST(test_create_arena)
{
  ;     
}
END_TEST

Suite * check_arena (void) {
    Suite *s;
    TCase *tc_core, *tc_limits;

    s = suite_create("Create arena");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
	//tcase_add_test(tc_core, test_cardinal_and_if);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
    tc_limits = tcase_create("Limits");

    //tcase_add_test(tc_limits, test_bad_expression);
    suite_add_tcase(s, tc_limits);

    return s;
}
