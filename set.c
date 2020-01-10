#include "set.h"

/* define the sets and init them with 0 */
set SETA,SETB,SETC,SETD,SETE,SETF = { 0 };

/* create a struct of sets */
struct SETS sets[]={
    {"SETA", &SETA},
    {"SETB", &SETB},
    {"SETC", &SETC},
    {"SETD", &SETD},
    {"SETE", &SETE},
    {"SETF", &SETF},
    {"not_valid",NULL}
};

int string_to_set(char *set)
{
    int i =0;

    for (i = 0; sets[i].set!=NULL; i++)
    {
        if(strcmp(sets[i].name,set) == 0)
        {
            printf("\nstring_to_set: %s\n", sets[i].name);
            return i; 
        }
            
    }

    return i; /* return null */
}

void read_set(char *args)
{
    int setIndex;
    setIndex = string_to_set(args);
    
    *sets[setIndex].set[0] = 1;
    
    SETA[0] = 1;

    printf("\nREAD SET\n");
    printf("\nREAD SET: %s\n", args);
    printf("\n From Read_set: %c\n", *sets[setIndex].set[0]);
    printf("\n From Read_set: %c\n", SETA[0]);
}
