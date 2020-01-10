#ifndef _INCL_GUARD
#define _INCL_GUARD

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SET_LEN 16 /* the set length */

typedef char set[SET_LEN]; /* define a set as an array of chars */

set SETA,SETB,SETC,SETD,SETE,SETF;

struct SETS
{
    char *name;
    set *set;
};

/* define the commands */
void read_set(char *args);

/* define a struct for commands */
struct CMD
{
    char *name;
    void (*func)();
};



#endif


