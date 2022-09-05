/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "libc/stddef.h"
#include "libc/stdio.h"

#include "flag.h"

static bool help_flag;

static u0 displayHelp(__attribute__((unused)) i32 actualArgc, __attribute__((unused)) int8 **actualArgv,
                      __attribute__((unused)) int8 **nonOption)
{
  if (help_flag)
    oPuts("Help value is true");
  else
    oPuts("Help value is false");
}

__attribute__((unused)) i32 oMain(i32 argc, int8 *argv[])
{
  flagParser_t flag;

  __attribute__((unused)) static struct flagOption options[FLAG_OPTS_COUNT] = {
#define HELP_ARG_INDEX 0
    {{&help_flag}, displayHelp, "help", "h", {true}, "Display the usage table for the user"},
    {}
  };

  flagReset(&flag);
  flagBool(&options[HELP_ARG_INDEX], &flag);
  bool parser_status = flagParser(argc, argv, &flag);

  oPuts(flagStatusToStr(parser_status));
  
  return 0;
}

