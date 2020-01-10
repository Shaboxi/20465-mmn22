#ifndef _INCL_GUARD
#define _INCL_GUARD

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define SET_LEN 16 /* the set length */

typedef char set[SET_LEN]; /* define a set as an array of chars */

set SETA,SETB,SETC,SETD,SETE,SETF;

struct SETS
{
    char *name;
    set *set;
    int isEmpty; /* accepts 0 or 1, 0 for empty 1 for not empty */
};

/* define the commands */
void read_set(char *args);
void print_set(char *args);
void union_set(char *args);

/* helper functions */
int string_to_set(char *set);
int check_duplication(int setIndex, char *value);

/* define a struct for commands */
struct CMD
{
    char *name;
    void (*func)();
};



#endif


