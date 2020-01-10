#include "set.h"

/* define the sets and init them with 0 */
set SETA,SETB,SETC,SETD,SETE,SETF = { 0 };

/* create a struct of sets */
struct SETS sets[]={
    {"SETA", &SETA,0},
    {"SETB", &SETB,0},
    {"SETC", &SETC,0},
    {"SETD", &SETD,0},
    {"SETE", &SETE,0},
    {"SETF", &SETF,0},
    {"not_valid",NULL,0}
};

/* get a set as a string the returns the set id matches */
int string_to_set(char *set)
{
    int i =0;

    for (i = 0; sets[i].set!=NULL; i++)
    {
        if(strcmp(sets[i].name,set) == 0)
        {
            return i; 
        }
            
    }

    return i; /* return null */
}

/* return the value as int if it is not found in the array. else returns -1 */
int check_duplication(int setIndex, char *value)
{
    char* dummy;
    int intValue;
    *dummy = *value;

    intValue = atoi(dummy);
    
    return intValue;
}

/* put data in a set */
void read_set(char *args)
{
    int setIndex;
    int i;
    char* value;
    int dummy;

    printf("\nREAD SET");
    printf("\nARGS: %s", args);    

    /* get the set id */
    value = strtok(args, ","); 
    setIndex = string_to_set(value);
    
    for(i = 0; strcmp("-1",value) != 0; i++)
    {
        value = strtok(NULL, ",");
        dummy = check_duplication(setIndex,value);
        printf("\ndummy: %d", dummy); 
        if(dummy != -1)
            *sets[setIndex].set[i] =  atoi(value);
    }
    
    sets[setIndex].isEmpty = 1;
    
/*
    printf ("ARGS? %s", args);
    value = strtok(NULL, ",");
    printf("\n values not handeld: %s\n", value);

    printf("\n From Read_set: %d\n", *sets[setIndex].set[0]);
    printf("\n From Read_set: %d\n", SETA[0]);
*/
}

/* print data from a set */
void print_set(char *args)
{
    int setIndex;
    int i;

    setIndex = string_to_set(args);

    printf("\nPRINT SET\n");

    if(sets[setIndex].isEmpty == 0)
        printf("\nThe set is empty\n");
    else
    {
        for(i=0; *sets[setIndex].set[i] != -1; i++ )
        {
            printf("%d ", *sets[setIndex].set[i]);    
        }        
    }
    printf("\n");
}
