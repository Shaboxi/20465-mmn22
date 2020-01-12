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

    return -1; /* return -1 if set does not exists */
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

/* check consective commas */
int consective_commas(char *str)
{
    int i;

    for (i = 1; str[i]; i++) 
        if (str[i] == ',' && str[i-1] == ',') 
            return 1;
                                  
    return 0;
}

/* check missing commas */
int missing_commas(char *str)
{
    int i;
    for (i = 1; str[i]; i++) 
        if (str[i] == ',') 
            return 0;
                                  
    return 1;
}

/* check illegal commas */
int illegal_commas(char *str)
{
    int len = strlen(str);
    char *lastChar = &str[len-1];
        if(lastChar[0] == ',')
            return 1;
    return 0;                              
}

/* validate input */
/* return 0 if input is validated, else prints a relevent error and returns 1 */
int validate_input(char *input)
{
    char dummy[INPUT_SIZE]; /* a copy of the input */
    char dummy2[INPUT_SIZE]; /* a copy of the input */
    char* dummyFunc; 
    char* dummyArgs;
    char* setName1;
    char* setName2;
    char* setName3;
    int dummy2Length;
    char* checkLast; /* used to store the last 2 chars of the input */
    /* create a struct of commands for validation */
    char *commands[7] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "not_valid"};
    int i;
    int noCommandFlag = 0;

    /* copy the input to a char dummy[] so the real input wont get dirty */
    strcpy(dummy,input);
    strcpy(dummy2,input);
    

    /* validate the arguments of an input */
    /*replace_spaces(dummy);*/
    
    /*
    printf("\nvalidating input(dummy): %s", dummy);
    printf("\ndummy after space clean: %s", dummy);
    ---

    dummyFunc = strtok(dummy, "_set");
    printf("\ndummyFunc: %s", dummyFunc);
    
    dummyArgs = strtok(NULL, "_set");    
    printf("\ndummyArgs: %s", dummyArgs);
    ---
    printf("\ndummyFunc: %s", dummyFunc);    
    printf("\ndummyArgs: %s", dummyArgs);
    
*/
    dummyFunc = strtok(dummy, " ");  
    dummyArgs = strtok(NULL, " ");
        
    if(illegal_commas(dummyFunc) == 1)
    {
        printf("\nIllegal comma");
        return 1;        
    }


    /* check if the command exists */
    for (i = 0; i < 7; i++)
    {
        if(strcmp(commands[i],dummyFunc) == 0)
        {
            noCommandFlag = 1;
        }
    }
    if(noCommandFlag == 0)
    {
        printf("\nUndifiend command name");
        return 1;
    }

    if(consective_commas(dummyArgs) == 1)
    {
        printf("\nMultiple consective commas");
        return 1;
    }

    if(missing_commas(dummyArgs) == 1)
    {
        printf("\nMissing commas");
        return 1;
    }

    /* if this is one of the 3 params functions */
    if(strcmp(dummyFunc,"read_set") != 0 && strcmp(dummyFunc,"print_set") != 0)
    {
        /* check if there are 3 setes */
        setName1 = strtok(dummyArgs, ",");
        if(setName1 == NULL)
        {
            printf("\nMissing parameter");
            return 1;
        }

        setName2 = strtok(NULL, ",");
        if(setName2 == NULL)
        {
            printf("\nMissing parameter");
            return 1;
        }

        setName3 = strtok(NULL, ",");
        if(setName3 == NULL)
        {
            printf("\nMissing parameter");
            return 1;
        }
        
        if( string_to_set(setName1) == -1  || string_to_set(setName2) == -1 || string_to_set(setName3) == -1)
        {
            printf("\nUndifient set name");
            return 1;
        }

    }
    else if(strcmp(dummyFunc,"read_set") == 0)
    {                
        /* get the set id */
        setName1 = strtok(dummyArgs, ","); 
        
        if(string_to_set(setName1) == -1)
        {
            printf("\nUndefined set name");
            return 1;
        }

        /* check if last 2 chars are '-1' */
        dummy2Length = strlen(dummy2);
        checkLast = &dummy2[dummy2Length-2];
        if(strcmp(checkLast,"-1") != 0)
        {
            printf("\nList of members is not terminiated corectly (missing -1)");
            return 1;
        }

        /* check range of values */
        while(strcmp("-1",dummyArgs) != 0)
        {
            dummyArgs = strtok(NULL, ","); 
            
            if(atoi(dummyArgs) == 0 || atof(dummyArgs) == 0.0)
            {
                printf("\nInvalid set member - not an intger");
                return 1;                
            }
            else if(atoi(dummyArgs) > CHAR_MAX || atoi(dummyArgs) < -1)
            {
                printf("\nInvalid set member - value out of range");
                return 1;
            }    

        }


    }
    else /* then its a print_set command */
    {                
        /* get the set id */
        setName1 = strtok(dummyArgs, ","); 
        if(setName1 != NULL && string_to_set(setName1) == -1)
        {
            printf("\nUndefined set name");
            return 1;
        }     

        setName2 = strtok(NULL, ",");
        if(setName2 != NULL)
        {
            printf("\nExtra text after the end of the command");
            return 1;
        }               
    }
    

    
    
    return 0;
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