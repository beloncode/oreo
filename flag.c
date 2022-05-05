/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/05/03
*/

#include "libc/branch.h"
#include "libc/string.h"

#include "flag.h"

static const char_t* const flag_status_str[] = {
  "It's fine, go ahead and try new options",
  "The last argument isn't a option",
  "Argument not found",
  "Argument value not passed",
  NULL
};

u0_t 
flag_reset
(flag_parser_t *flag)
{
  unlikely (flag == NULL)
    return;

  flag->status = FLAG_ITS_FINE;
  flag->rest_argv = NULL;
  flag->arg_not_found = NULL;
  flag->flag_index = flag->rest_argc = 0;

  for (u8_t c_loop = 0; c_loop < FLAG_OPTS_COUNT; c_loop++)
    flag->flag_options[c_loop] = 0;
}

static 
u0_t
flag_inc_index
(flag_parser_t *flag)
{
  if (++flag->flag_index == FLAG_OPTS_COUNT)
    flag->flag_index = 0;
}

u0_t
flag_bool
(struct flag_option *option, flag_parser_t *flag)
{
  unlikely (flag == NULL)
    return;

  u8_t                    f_index       = flag->flag_index;
  struct flag_option      **option_ava  = flag->flag_options + f_index;
  enum flag_option_info   *optinfo_ava  = flag->flag_infos + f_index;

  *option_ava = option;
  *optinfo_ava = FLAG_TYPE_BOOLEAN;

  *option->arg_pointer.as_bool = option->default_value.as_bool;

  flag_inc_index(flag);
}

static char_t*
flag_process_value
(struct flag_option *option, enum flag_option_info type, char_t *argument)
{
  static const char_t* const boolean_format[] = {"true", "false"};

  if (argument) {
    switch (type) {

    case FLAG_TYPE_BOOLEAN:
      if (O_strcmp(argument, boolean_format[0]) == 0)
        *option->arg_pointer.as_bool = true;
      else if (O_strcmp(argument, boolean_format[1]) == 0)
        *option->arg_pointer.as_bool = false;
    break;
    
    }
  }
  return (argument);
}

enum flag_status
flag_parser
(i32_t argc, char_t *argv[], flag_parser_t *flag)
{
  u8_t array_index = 0;
  enum option_type {
    OPTION_UNDEFINED = 0,
    OPTION_SHORT,
    OPTION_LONG,
    OPTION_WITH_VALUE
  };

  enum option_type opt_type_state;
  flag->program_exec_path = *argv++;

  i32_t     curr_argc = 0;
  char_t    *curr_argv = NULL;

  while (argc > 1 && *argv) {

    curr_argc = argc--;
    curr_argv = *argv++;
    opt_type_state = OPTION_UNDEFINED;
    array_index = 0;

    if (*curr_argv == '-') {
      opt_type_state = OPTION_SHORT;
      curr_argv++;
    }
    if (*curr_argv == '-') {
      opt_type_state = OPTION_LONG;
      curr_argv++;
    }

    if (opt_type_state == OPTION_UNDEFINED) {
      flag->rest_argv = argv - 1;
      flag->rest_argc = curr_argc;
      flag->status = FLAG_NA;
      continue;
    }

    flag->consumed_arg = curr_argv;

    char_t *arg_value = *argv;
    mu64_t  arg_value_pos = O_strlen(curr_argv);

    if ((arg_value = O_strchr(curr_argv, '='))) {
      opt_type_state = OPTION_WITH_VALUE;
      /* Now pointing to the argument value */
      arg_value_pos = arg_value - curr_argv;
    }

    for (; array_index < FLAG_OPTS_COUNT; array_index++) {
      struct flag_option *curr_option = *(flag->flag_options + array_index);
      enum flag_option_info type = *flag->flag_infos + array_index;
      
      if (curr_option == NULL) {
        flag->arg_not_found = curr_argv;
        return (flag->status = FLAG_ARGNF);
      }

      if (opt_type_state == OPTION_SHORT)
        if (O_strncmp(curr_option->short_option, curr_argv, 1) != 0) continue;
      if (opt_type_state == OPTION_LONG)
        if (O_strncmp(curr_option->long_option, curr_argv, arg_value_pos) != 0) continue;
      
      if (arg_value && O_strlen(arg_value) > 1)
        arg_value = flag_process_value(curr_option, type, arg_value);
      else
        if (opt_type_state == OPTION_WITH_VALUE)
          return (flag->status = FLAG_ARGNP);
      curr_option->exec_func_handler(curr_argc, &curr_argv, flag->rest_argv);
      break;
    }
  }
  return (flag->status = FLAG_ITS_FINE);
}

char_t* 
flag_arg_not_found
(const flag_parser_t *flag)
{
  unlikely (flag == NULL)
    return NULL;
  return (flag->arg_not_found);
}

char_t*
flag_exec_path
(const flag_parser_t *flag)
{
  unlikely (flag == NULL)
    return NULL;
  return (flag->program_exec_path);
}

char_t**
flag_non_args
(const flag_parser_t *flag)
{
  unlikely (flag == NULL)
    return NULL;
  return (flag->rest_argv);
}

const char_t*
flag_status_to_str(enum flag_status status)
{
  return (flag_status_str[status]);
}

