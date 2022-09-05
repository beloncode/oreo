/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/03
*/

#include "libc/branch.h"
#include "libc/string.h"

#include "flag.h"

static const int8* const flagStatusStr[] = {
  "It's fine, go ahead and try new options",
  "The last argument isn't a option",
  "Argument not found",
  "Argument value not passed",
  NULL
};

u0 flagReset(flagParser_t *flag)
{
  unlikely (flag == NULL)
    return;

  flag->status = FLAG_ITS_FINE;
  flag->restArgv = NULL;
  flag->argNotFound = NULL;
  flag->flagIndex = flag->restArgc = 0;

  for (u8 c_loop = 0; c_loop < FLAG_OPTS_COUNT; c_loop++)
    flag->flagOptions[c_loop] = 0;
}

static u0 flagIncIndex(flagParser_t *flag)
{
  if (++flag->flagIndex == FLAG_OPTS_COUNT)
    flag->flagIndex = 0;
}

u0 flagBool(struct flagOption *option, flagParser_t *flag)
{
  unlikely (flag == NULL)
    return;

  u8 fIndex = flag->flagIndex;
  struct flagOption **optionAva = flag->flagOptions + fIndex;
  enum flagOptionInfo *pOptionInfo = flag->flagInfos + fIndex;

  *optionAva = option;
  *pOptionInfo = FLAG_TYPE_BOOLEAN;

  *option->argPointer.asBool = option->defaultValue.asBool;

  flagIncIndex(flag);
}

static int8* flagProcessValue(struct flagOption *option, enum flagOptionInfo type, int8 *argument)
{
  static const int8* const boolean_format[] = {"true", "false"};

  if (type == FLAG_TYPE_BOOLEAN) {
    if (oStrCmp(argument, boolean_format[0]) == 0)
      *option->argPointer.asBool = true;
    else if (oStrCmp(argument, boolean_format[1]) == 0)
      *option->argPointer.asBool = false;
  }
  return argument;
}

__attribute__((unused)) enum flagStatus flagParser(i32 argc, int8 *argv[], flagParser_t *flag)
{
  u8 arrayIndex;
  enum optionType {
    OPTION_UNDEFINED = 0,
    OPTION_SHORT,
    OPTION_LONG,
    OPTION_WITH_VALUE
  };

  enum optionType optionType;
  flag->programExecPath = *argv++;

  i32 currArgc;
  int8 *currArgv = NULL;

  while (argc > 1 && *argv) {
    currArgc = argc--;
    currArgv = *argv++;
    optionType = OPTION_UNDEFINED;
    arrayIndex = 0;

    if (*currArgv == '-') {
      optionType = OPTION_SHORT;
      currArgv++;
    }
    if (*currArgv == '-') {
      optionType = OPTION_LONG;
      currArgv++;
    }

    if (optionType == OPTION_UNDEFINED) {
      flag->restArgv = argv - 1;
      flag->restArgc = currArgc;
      flag->status = FLAG_NA;
      continue;
    }

    flag->consumedArg = currArgv;

    int8 *argValue;
    mu64 argValuePos = oStrlen(currArgv);

    if ((argValue = oStrchr(currArgv, '='))) {
      optionType = OPTION_WITH_VALUE;
      /* Now pointing to the argument value */
    }

    for (; arrayIndex < FLAG_OPTS_COUNT; arrayIndex++) {
      struct flagOption *currOption = *(flag->flagOptions + arrayIndex);
      enum flagOptionInfo type = *flag->flagInfos + arrayIndex;
      
      if (currOption == NULL) {
        flag->argNotFound = currArgv;
        return flag->status = FLAG_ARGNF;
      }
      if (optionType == OPTION_SHORT)
        if (*currOption->shortOption != *currArgv)
          continue;
      if (optionType == OPTION_LONG)
        if (oStrncmp(currOption->longOption, currArgv, argValuePos) != 0)
          continue;
      
      if (argValue && oStrlen(argValue) > 1)
        flagProcessValue(currOption, type, argValue);
      else
        if (optionType == OPTION_WITH_VALUE)
          return flag->status = FLAG_ARGNP;
      currOption->execFuncHandler(currArgc, &currArgv, flag->restArgv);
      break;
    }
  }
  return flag->status = FLAG_ITS_FINE;
}

__attribute__((unused)) int8* flagArgNotFound(const flagParser_t *flag)
{
  unlikely (flag == NULL)
    return NULL;
  return flag->argNotFound;
}

__attribute__((unused)) int8* flagExecPath(const flagParser_t *flag)
{
  unlikely (flag == NULL)
    return NULL;
  return flag->programExecPath;
}

__attribute__((unused)) int8** flagNonArgs(const flagParser_t *flag)
{
  unlikely (flag == NULL)
    return NULL;
  return flag->restArgv;
}

const int8* flagStatusToStr(enum flagStatus status)
{
  return flagStatusStr[status];
}

