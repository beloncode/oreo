/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "libc/stddef.h"
#include "libc/stdio.h"
#include "libc/string.h"

#include "libc/unistd.h"

#include "flag.h"

static bool_t help_flag;

static u0_t
display_help
(i32_t actual_argc, char_t **actual_argv, char_t **non_option)
{
  if (help_flag)
    O_puts("Help value is true");
  else
    O_puts("Help value is false");
}

i32_t
O_main
(i32_t argc, char_t *argv[])
{
  flag_parser_t flag;

  static struct flag_option options[FLAG_OPTS_COUNT] = {
#define HELP_ARG_INDEX 0
    {{&help_flag}, display_help, "help", "h", {true}, "Display the usage table for the user"},
    {}
  };

  flag_reset(&flag);
  flag_bool(&options[HELP_ARG_INDEX], &flag);
  bool_t parser_status = flag_parser(argc, argv, &flag);
  
  O_puts(flag_status_to_str(parser_status));
  
  return (0);
}

