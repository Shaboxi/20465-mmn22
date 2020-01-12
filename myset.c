#include "set.h"

int main()
{
    char input[INPUT_SIZE];    
    char* args; /* holds the arguments for the function that gets called */
    int i;
    
    struct CMD cmd[]={
        {"read_set", read_set},
        {"print_set", print_set},
        {"union_set", union_set},
        {"intersect_set", intersect_set},
        {"sub_set", sub_set},
        {"symdiff_set", symdiff_set},
        {"not_valid",NULL}
    };

    while(1 < 2)
    {
        printf("\n\nEnter command: \n");
        scanf("%[^\n]%*c",input);

        /* validate input */
        if(validate_input(input) == 0)
        {
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
                printf("\nUndifiend command name");
            else
            {
                (*(cmd[i].func))(args);     
            }
        }
        else
        {
            printf("\ninput was unvalid");
        }
        
    }
    
    return 0;
}





