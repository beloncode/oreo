/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/03
*/

#ifndef FLAG_H
#define FLAG_H

#define FLAG_OPTS_COUNT 2

#include "libc/stddef.h"

struct flagOption
{
  union {
    bool    *asBool;
    u0      *asPtr;
  } argPointer;

  u0 (*execFuncHandler)(i32 actualArgc, int8 **actualArgv, int8 **nonOption);

  const char *longOption;

  const char *shortOption;

  union {
    bool asBool;
    u0 *asPtr;
  } defaultValue;

  const char *optionComment;
};

enum flagOptionInfo
{
  FLAG_TYPE_BOOLEAN = 0
};

enum flagStatus
{
  FLAG_ITS_FINE = 0,
  FLAG_NA,
  FLAG_ARGNF,
  FLAG_ARGNP
};

typedef struct
{
  struct flagOption *flagOptions[FLAG_OPTS_COUNT];
  enum flagOptionInfo flagInfos[FLAG_OPTS_COUNT];

  enum flagStatus status;

  u8 flagIndex;

  int8 **restArgv;
  i32 restArgc;

  int8 *programExecPath;
  int8 *consumedArg;

  int8 *argNotFound;

} flagParser_t;

u0 flagReset(flagParser_t *flag);

u0 flagBool(struct flagOption *option, flagParser_t *flag);

__attribute__((unused)) enum flagStatus flagParser(i32 argc, int8 *argv[], flagParser_t *flag);

__attribute__((unused)) int8* flagArgNotFound(const flagParser_t *flag);

__attribute__((unused)) int8* flagExecPath(const flagParser_t *flag);

__attribute__((unused)) int8** flagNonArgs(const flagParser_t *flag);

const int8* flagStatusToStr(enum flagStatus status);

#endif

