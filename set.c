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

/* return the value as int if it is not found in the array. else returns -1 */
int check_duplication(int setIndex, char *value)
{
    char* dummy = "c";
    int intValue;
    printf("\ncheck_duplication");
    
    printf("\nvalue1: %s", value);
    printf("\ndummy1: %s", dummy);
    
    *dummy = *value;


    printf("\nvalue2: %s", value);
    printf("\ndummy2: %s", dummy);
    

    intValue = atoi(dummy);
    

    printf("\nvalue3: %s", value);
    printf("\ndummy3: %s", dummy);
    

    return intValue;
}

/* define the sets and init them with 0 */
void zero_set(set toZero)
{
    int i = 0;
    for (i = 0; i < SET_LEN ; i++)
    {
        toZero[i] = '0';
    }    
}


/* put data in a set */
void read_set(char *args)
{
    int setIndex;
    int i;
    char* value;    
    
/*
    printf("\nREAD SET");
    printf("\nARGS: %s", args); 
*/

    /* get the set id */
    value = strtok(args, ","); 
    setIndex = string_to_set(value);
    
    zero_set(*sets[setIndex].set);

    /* check if we got to the end of the input, 
    otherwise, put the value in the set */
    for(i = 0; strcmp("-1",value) != 0; i++)
    {
        value = strtok(NULL, ","); 

        if(strcmp("-1",value) == 0)
            (*sets[setIndex].set)[i] = NULL;
        else
            (*sets[setIndex].set)[i] = *value;
    }
    
    /* mark the set as not empty */
    sets[setIndex].isEmpty = 1;

}

/* print data from a set */
void print_set(char *args)
{
    int setIndex;
    int i = 0;    

    setIndex = string_to_set(args);
    
    printf("\nPRINT %s: ", sets[setIndex].name);   
    
    if(sets[setIndex].isEmpty == 0)
        printf("The set is empty\n");
    else
    {                
        while ((*sets[setIndex].set)[i])        
        {            
            printf("%c ", (*sets[setIndex].set)[i]); 
            i++;   
        }        
    }
    printf("\n");
}

/* unites sets */
void union_set(char *args)
{
    int i;
    
    printf("\nUNION SET\n");

/*    
    for (i = 0; i < 3; i++)
    {
        
        printf("\nprint set: %d ---> ", i);
        
        for(k = 0; k < 4; k++ )
        {
            printf("%d ", (char)*((sets[i].set)[k]));  
        }

            
    }
*/

    


    printf("\n\nprint set: A ---> ");
    printf("%d ", SETA[0]);
    printf("%d ", SETA[1]);
    printf("%d ", SETA[2]);
    printf("%d ", SETA[3]);

    printf("\nprint set: B ---> ");
    printf("%c ", (char)(SETB[0]));
    printf("%c ", (char)(SETB[1]));
    printf("%c ", (char)(SETB[2]));
    printf("%c ", (char)(SETB[3]));

    printf("\nprint set: C ---> ");
    printf("%c ", (char)(SETC[0]));
    printf("%c ", (char)(SETC[1]));
    printf("%c ", (char)(SETC[2]));
    printf("%c ", (char)(SETC[3]));

    printf("\n -asaf %d ", (*sets[2].set)[3]);
    printf("\n -asaf %c ", (*sets[2].set)[3]);
    

    /*

        
    i = strcmp("-",(sets[2].set)[2]);
    printf("\n strcmp ---> %d", strcmp("-1",(sets[2].set)[2]));
    printf("\n--- ");
    printf("\nprint set: A ---> %p", &SETA[0]);    
    printf("\nprint set: 0 ---> %p", &*sets[0].set[0]);
    printf("\n --%d ", SETB[1]);
    printf("\n --%s ", *(sets[1].set+1));
    printf("\n --%s ", *(sets[1].set+0));
    */
     
}
