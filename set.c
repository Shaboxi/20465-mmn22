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
    
    printf("\ncheckdup: %c value: %c ", checkDup[i], *value);
    for (i = 0; checkDup[i] ; i++)
    {        
        if(checkDup[i] == *value)
        {
            return 1;
        }            
    }  
    return 0;
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
    int dupFlag;  
    
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

        dupFlag = check_duplication(*sets[setIndex].set,value);

        if(strcmp("-1",value) == 0)
            (*sets[setIndex].set)[i] = NULL;
        else if (dupFlag == 0) /* if no duplication found */
        {
            (*sets[setIndex].set)[i] = *value;
            /* <-works for char
            strcpy((sets[setIndex].set)[i],value);
            */
        }
            
        else /* if found a duplication, make sure not to skip this index */
            i--;
                
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
    int i,k=0;
    int indexSet1,indexSet2,indexSet3;
    char* value;
    int checkDup;
    printf("\nUNION SET\n");


    /* get the sets id */
    value = strtok(args, ","); 
    indexSet1 = string_to_set(value);
    
    value = strtok(NULL, ","); 
    indexSet2 = string_to_set(value);

    value = strtok(NULL, ","); 
    indexSet3 = string_to_set(value);

    /* put the data of set1 and set2 in set3 
    zero_set(*sets[indexSet3].set);
    */

    

    for(i=0;(*sets[indexSet1].set)[i];i++)
    {
        (*sets[indexSet3].set)[i] = (*sets[indexSet1].set)[i];
    }

    
    

    for(k=0;(*sets[indexSet2].set)[k];k++)
    {
        
        /*
        printf("\nset2 value: %c", (*sets[indexSet2].set)[k]);
        checkDup = check_duplication(*sets[indexSet3].set,sets[indexSet2].set[k]);
        printf("\nthe value compared: %c checkdup: %d ", (*sets[indexSet2].set)[k], checkDup);
        if(checkDup == 0)
        {
            (*sets[indexSet3].set)[i] = (*sets[indexSet2].set)[k];
            i++;
        }
        
        */
    
       printf("\nset2 value: %c", (*sets[indexSet2].set)[k]);
       checkDup = check_duplication(*sets[indexSet3].set,(sets[indexSet2].set)[k]);
       printf("\nthe value compared: %c checkdup: %d ", (*sets[indexSet2].set)[k], checkDup);
       if(checkDup == 0)
       {
           (*sets[indexSet3].set)[i] = (*sets[indexSet2].set)[k];
           i++;
       }

    }


    /* mark the set as not empty */
    sets[indexSet3].isEmpty = 1;    

    /*
    
    strcpy((sets[2].set)[2],"22");
    strcpy(&SETC[2],"22");

    printf("\n 1. %c ", (*sets[2].set)[3]);
    printf("\n 2. %c ", (char)(SETC[2]));

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


    

    

    -------

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
