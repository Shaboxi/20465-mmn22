#include "header.h"

void read_set()
{
    printf("\nREAD SET\n");
}



int main()
{
    set SETA;
    
    char input[127];
    int i;

    while(1 < 2)
    {
        printf("\nEnter command: \n");
        scanf("%s",input);
        
        printf("\nThe string you've enterd is: %s", input);
        
        for (i = 0; cmd[i].func!=NULL; i++)
        {
            if(strcmp(cmd[i].name,input) == 0)
                break;
        }

        if(cmd[i].func==NULL)
            printf("\nCOMMAND NOT FOUND \n");
        else
        {
            (*(cmd[i].func))();
        }

        if(strcmp("stop",input) == 0)
        {
            printf("\nExit Program\n");
            break;
        }
        

    }
    

    
    SETA[0] = '1';

    printf("\n BOOM: %c\n", SETA[0]);

    return 0;
}





