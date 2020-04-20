#ifndef CHECK_HEADER_H
#define CHECK_HEADER_H

#include <check.h>

Suite * make_file_reader(void);
Suite * check_robot(void);
Suite * check_missile(void);
Suite * check_arena(void);
Suite * check_commands(void);
#endif