#include "set.h"

int main()
{
    char input[120];    
    char* args; /* holds the arguments for the function that gets called */
    int i;
    
    struct CMD cmd[]={
        {"read_set", read_set},
        {"print_set", print_set},
        {"union_set", union_set},
        {"not_valid",NULL}
    };

    while(1 < 2)
    {
        printf("\n\nEnter command: \n");
        scanf("%[^\n]%*c",input);

        /* get the func name and args */                
        strtok(input, " ");                
        args = strtok(NULL, " ");
        
        if(strcmp("stop",input) == 0)
        {
            printf("\nExit Program\n");
            break;
        }

        /* check if the command exists */
        for (i = 0; cmd[i].func!=NULL; i++)
        {
            if(strcmp(cmd[i].name,input) == 0)
                break;
        }

        /* if the command dosent exist print error, else call it */
        if(cmd[i].func==NULL)
            printf("\nCOMMAND NOT FOUND");
        else
        {
            (*(cmd[i].func))(args);     
        }

    }
    
    return 0;
}





