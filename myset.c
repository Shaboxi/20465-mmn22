#include "set.h"

int main()
{
    set SETA;
    
    char input[120];
    char* func; /* holds the function to call after the input is parsed */
    char* args; /* holds the arguments for the function that gets called */
    int i;
    
    struct CMD cmd[]={
        {"read_set", read_set},
        {"not_valid",NULL}
    };

    while(1 < 2)
    {
        printf("\nEnter command: \n");
        scanf("%[^\n]%*c",input);
        
        printf("\nThe string you've enterd is: %s", input);

        func = strtok(input, " "); 
        printf("\nThe func you've enterd is: %s", func);
        
        args = strtok(NULL, " ");
        printf("\nThe args you've enterd is: %s", args);

        if(strcmp("stop",input) == 0)
        {
            printf("\nExit Program\n");
            break;
        }

        for (i = 0; cmd[i].func!=NULL; i++)
        {
            printf("\ninput: %s", input);
            if(strcmp(cmd[i].name,input) == 0)
                break;
        }

        if(cmd[i].func==NULL)
            printf("\nCOMMAND NOT FOUND \n");
        else
        {
            (*(cmd[i].func))(args);     
        }


        

    }
    
    SETA[0] = '1';

    printf("\n BOOM: %c\n", SETA[0]);

    return 0;
}





