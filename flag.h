/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/05/03
*/

#ifndef FLAG_H
#define FLAG_H

#define FLAG_OPTS_COUNT 2

#include "libc/stddef.h"

struct flag_option
{
  union {
    bool_t    *as_bool;
    u0_t      *as_ptr;
  } arg_pointer;

  u0_t (*exec_func_handler)(i32_t actual_argc, char_t **actual_argv, char_t **non_option);

  const char *long_option;

  const char *short_option;

  union {
    bool_t    as_bool;
    u0_t      *as_ptr;
  } default_value;

  const char *option_comment;

};

enum flag_option_info 
{
  FLAG_TYPE_BOOLEAN = 0
};

enum flag_status
{
  FLAG_ITS_FINE = 0,
  FLAG_NA,
  FLAG_ARGNF,
  FLAG_ARGNP
};

typedef struct flag_parser
{
  struct flag_option *flag_options[FLAG_OPTS_COUNT];
  enum flag_option_info flag_infos[FLAG_OPTS_COUNT];

  enum flag_status status;

  u8_t flag_index;

  char_t **rest_argv;
  i32_t rest_argc;

  char_t *program_exec_path;
  char_t *consumed_arg;

  char_t *arg_not_found;

} flag_parser_t;

u0_t flag_reset(flag_parser_t *flag);

u0_t flag_bool(struct flag_option *option, flag_parser_t *flag);

enum flag_status flag_parser(i32_t argc, char_t *argv[], flag_parser_t *flag);

char_t* flag_arg_not_found(const flag_parser_t *flag);
char_t* flag_exec_path(const flag_parser_t *flag);
char_t** flag_non_args(const flag_parser_t *flag);

const char_t* flag_status_to_str(enum flag_status status);

#endif

