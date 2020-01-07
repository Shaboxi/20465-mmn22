#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SET_LEN 16

typedef char set[SET_LEN];

void read_set(void);

struct 
{
    char *name;
    void (*func)(void);
} cmd[]={
    {"read_set", read_set},
    {"not_valid",NULL}
};

