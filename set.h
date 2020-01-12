#ifndef _INCL_GUARD
#define _INCL_GUARD

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

#define INPUT_SIZE 100

#define SET_LEN 16 /* the set length */
typedef char set[SET_LEN]; /* define a set as an array of chars */
set SETA,SETB,SETC,SETD,SETE,SETF;

struct SETS
{
    char *name;
    set *set;
    int isEmpty; /* accepts 0 or 1. 0 for empty, 1 for not empty */
};

/* commands */
void read_set(char *args);
void print_set(char *args);
void union_set(char *args);
void intersect_set(char *args);
void sub_set(char *args);
void symdiff_set(char *args);

/* helper functions */
int string_to_set(char *set);
int check_duplication(set checkDup, char *value);
void zero_set(set toZero);
void replace_spaces(char *str);
int consective_commas(char *str);
int missing_commas(char *str);
int validate_input(char *input);


/* define a struct for commands */
struct CMD
{
    char *name;
    void (*func)();
};

#endif