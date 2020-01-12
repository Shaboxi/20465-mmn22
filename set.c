#include "set.h"

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

/* get a set as a string and returns the set the set id matches */
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

/* return 1 if char value is found in the array. else returns 0 */
int check_duplication(set checkDup, char *value)
{
    int i = 0;
    int bit;
    
    bit = (checkDup[i/8] & (1 << (i%8)));
    if(bit == 1)
    {
        return 1;
    }            
    
    return 0;
}

/*  init a set with 0 */
void zero_set(set toZero)
{
    int i = 0;
    for (i = 0; i < CHAR_MAX ; i++)
    {
        toZero[i/8] &= ~(1 << (i%8));
    }    
}

/*  check if a set is all 0. return 0 if true, else returns 1 */
int check_zero_set(set isZero)
{
    int i = 0;
    int bit; 

    for (i = 0; i < CHAR_MAX ; i++)
    {
        bit = (isZero[i/8] & (1 << (i%8)));
        if(bit != 0)
            return 1;
    }
    return 0;
}

/* replace spaces */
void replace_spaces(char *str)
{
    int count = 0; 
    int i;

    for (i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i];  
                                  
    str[count] = '\0'; 
}

/* validate input */
/* return 0 if input is validated, else prints a relevent error and returns 1 */
int validate_input(char *input)
{
    char dummy[INPUT_SIZE];
    char* dummyArgs;

    /* copy the input to a char dummy[] so the real input wont get dirty */
    strcpy(dummy,input);
    printf("\nvalidating input(dummy): %s", dummy);

    /* since the command validation in preformed in main(), 
    this function will validate the arguments of an input. */
    replace_spaces(dummy);
    printf("\ndummy after space clean: %s", dummy);
    /*
    strtok(dummy, " ");
    printf("\ndummy after strtok: %s", dummy);
    dummyArgs = strtok(NULL, " ");    

    printf("\nvalidating args: %s", dummyArgs);
*/


    return 1;
}

/* COMMANDS START HERE */

/* put data in a set */
void read_set(char *args)
{
    int setIndex;
    char* value;
    int dupFlag;  
    
    /* get the set id */
    value = strtok(args, ","); 
    setIndex = string_to_set(value);
    
    zero_set(*sets[setIndex].set);

    /* check if we got to the end of the input, 
    otherwise, put the value in the set */
    while(strcmp("-1",value) != 0)
    {
        value = strtok(NULL, ","); 

        /* 0 if not duplication, 1 is theres a duplication */
        dupFlag = check_duplication(*sets[setIndex].set,value);
        
        if(strcmp("-1",value) == 0)
            (*sets[setIndex].set)[atoi(value)] = NULL;
        else if (dupFlag == 0) /* if no duplication found */
        {
            /* set 1 in the bit of the index */
            (*sets[setIndex].set)[atoi(value)/8] |= (1 << (atoi(value)%8));
        }            
    }
    
    if(check_zero_set(*sets[setIndex].set) == 0)
    {
        /* mark the set as empty */
        sets[setIndex].isEmpty = 0;
    }
    else
    {
        /* mark the set as not empty */
        sets[setIndex].isEmpty = 1; 
    }
}

/* print data from a set */
void print_set(char *args)
{
    int setIndex;
    int i = 0;    
    int bit; 
    setIndex = string_to_set(args);
    
    printf("\nPRINT %s: ", sets[setIndex].name);   
    
    if(sets[setIndex].isEmpty == 0)
        printf("The set is empty\n");
    else
    {                
        while (i < CHAR_MAX)
        {            
            /* get the data of the bit */
            bit = ((*sets[setIndex].set)[i/8] & (1 << (i%8)));
            /*printf("%d ", bit); */
            /* if the bit is not 0, print it */
            if(bit != 0)
                printf("%d ", i); 
            i++;   
        }        
    }
    printf("\n");
}

/* unites sets */
void union_set(char *args)
{
    int i;
    int indexSet1,indexSet2,indexSet3;
    char* value;
    int bit1,bit2;

    printf("\nUNION SET\n");

    /* get the sets id */
    value = strtok(args, ","); 
    indexSet1 = string_to_set(value);
    
    value = strtok(NULL, ","); 
    indexSet2 = string_to_set(value);

    value = strtok(NULL, ","); 
    indexSet3 = string_to_set(value);

    /* put the data of set1 and set2 in set3 */
    for(i=0; i < CHAR_MAX; i++)
    {
        /* get the data of the bit */
        bit1 = ((*sets[indexSet1].set)[i/8] & (1 << (i%8)));
        bit2 = ((*sets[indexSet2].set)[i/8] & (1 << (i%8)));

        /* if the bit is not 0, print it */
        if(bit1 != 0 || bit2 != 0)
            (*sets[indexSet3].set)[i/8] |= (1 << (i%8));
            
    }

    if(check_zero_set(*sets[indexSet3].set) == 0)
    {
        /* mark the set as empty */
        sets[indexSet3].isEmpty = 0;
    }
    else
    {
        /* mark the set as not empty */
        sets[indexSet3].isEmpty = 1; 
    } 
}

/* intersect sets */
void intersect_set(char *args)
{
    int i;
    int indexSet1,indexSet2,indexSet3;
    char* value;
    int bit1,bit2;

    printf("\n INTERSECT SET\n");

    /* get the sets id */
    value = strtok(args, ","); 
    indexSet1 = string_to_set(value);
    
    value = strtok(NULL, ","); 
    indexSet2 = string_to_set(value);

    value = strtok(NULL, ","); 
    indexSet3 = string_to_set(value);

    for(i=0; i < CHAR_MAX; i++)
    {
        /* get the data of the bit */
        bit1 = ((*sets[indexSet1].set)[i/8] & (1 << (i%8)));
        bit2 = ((*sets[indexSet2].set)[i/8] & (1 << (i%8)));

        /* both bits are 1, change bit in set3 to also be 1 */
        if(bit1 && bit2)
            (*sets[indexSet3].set)[i/8] |= (1 << (i%8));
        else /* else zero it */
            (*sets[indexSet3].set)[i/8] &= ~(1 << (i%8));
            
    }  

    if(check_zero_set(*sets[indexSet3].set) == 0)
    {
        /* mark the set as empty */
        sets[indexSet3].isEmpty = 0;
    }
    else
    {
        /* mark the set as not empty */
        sets[indexSet3].isEmpty = 1; 
    }

}

/* subtract sets */
void sub_set(char *args)
{
    int i;
    int indexSet1,indexSet2,indexSet3;
    char* value;
    int bit1,bit2;

    printf("\nSUB SET\n");

    /* get the sets id */
    value = strtok(args, ","); 
    indexSet1 = string_to_set(value);
    
    value = strtok(NULL, ","); 
    indexSet2 = string_to_set(value);

    value = strtok(NULL, ","); 
    indexSet3 = string_to_set(value);

    for(i=0; i < CHAR_MAX; i++)
    {
        /* get the data of the bit */
        bit1 = ((*sets[indexSet1].set)[i/8] & (1 << (i%8)));
        bit2 = ((*sets[indexSet2].set)[i/8] & (1 << (i%8)));

        /* make sure only bits from set1 are set to 1, change bit in set3 to also be 1 */
        if(bit1 != bit2 && bit1 != 0)
            (*sets[indexSet3].set)[i/8] |= (1 << (i%8));
        else /* else zero it */
            (*sets[indexSet3].set)[i/8] &= ~(1 << (i%8));
            
    }  

    if(check_zero_set(*sets[indexSet3].set) == 0)
    {
        /* mark the set as empty */
        sets[indexSet3].isEmpty = 0;
    }
    else
    {
        /* mark the set as not empty */
        sets[indexSet3].isEmpty = 1; 
    }

}

/* symdiff_set */
void symdiff_set(char *args)
{
    int i;
    int indexSet1,indexSet2,indexSet3;
    char* value;
    int bit1,bit2;

    printf("\nSYMDIFF SET\n");

    /* get the sets id */
    value = strtok(args, ","); 
    indexSet1 = string_to_set(value);
    
    value = strtok(NULL, ","); 
    indexSet2 = string_to_set(value);

    value = strtok(NULL, ","); 
    indexSet3 = string_to_set(value);

    for(i=0; i < CHAR_MAX; i++)
    {
        /* get the data of the bit */
        bit1 = ((*sets[indexSet1].set)[i/8] & (1 << (i%8)));
        bit2 = ((*sets[indexSet2].set)[i/8] & (1 << (i%8)));

        /* set all the bits that are on set1 or set 2, but not on both */
        if((bit1 || bit2) && bit1 != bit2)
            (*sets[indexSet3].set)[i/8] |= (1 << (i%8));
        else /* else zero it */
            (*sets[indexSet3].set)[i/8] &= ~(1 << (i%8));
            
    }

    if(check_zero_set(*sets[indexSet3].set) == 0)
    {
        /* mark the set as empty */
        sets[indexSet3].isEmpty = 0;
    }
    else
    {
        /* mark the set as not empty */
        sets[indexSet3].isEmpty = 1; 
    }
}