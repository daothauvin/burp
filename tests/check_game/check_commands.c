#include "../../src/model/game/commands.h"
#include <check.h>

static void setup(void) {}

static void teardown(void) {}

START_TEST(target_x)
{
  printf("%f\n",targety(4,90,4));
  
}
END_TEST

Suite * check_commands (void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Create commands");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
	  tcase_add_test(tc_core, target_x);
    suite_add_tcase(s, tc_core);

    return s;
}
