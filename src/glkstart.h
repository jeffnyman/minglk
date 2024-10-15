#ifndef GT_START_H
#define GT_START_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL 0
#endif

#define glk_arg_End (0)

typedef struct glk_startup_struct
{
  int argc;
  char *argv;
} glk_startup_t;

typedef struct glk_argumentlist_struct
{
  char *name;
  int argtype;
  char *desc;
} glk_argumentlist_t;

extern int glk_startup_code(glk_startup_t *data);
extern glk_argumentlist_t glk_arguments[];

#endif
