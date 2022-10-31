#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<errno.h>
#include<limits.h>
#include<sys/wait.h>

int main(int argc, char const *argv[])
{
    /* code */
    if (argc==1)
    {
        printf("Error :no arguments provided.\n");
    }
    else if (strcmp(argv[1],"-n")==0)
    {
            int count=1;

        for (int i = 2; i < argc; i++)
        {
            FILE *file=fopen(argv[i],"r");
        if (file!=NULL)
        {
            char str[5000];
        while (fgets(str,5000,file)!=NULL)
        {
            printf("%d %s",count,str);
            count++;
        }
        
        fclose(file);

        }
        else{
            printf("Error(%d) cat: %s\n",errno,strerror(errno));
        }
        }

        
    }
    else if (argv[1][0]!='-')
    {
        for (int i = 1; i < argc; i++)
        {
             FILE *file=fopen(argv[i],"r");
        if (file!=NULL)
        {
            char str[50000];
        while (fgets(str,50000,file)!=NULL)
        {
            printf("%s",str);
        }
        
        fclose(file);

        }
        else{
            printf("Error(%d): %s\n",errno,strerror(errno));
        }

        }
        
           }
    else if (strcmp(argv[1],"-E")==0)
    {
        
        for (int i = 2; i < argc; i++)
        {
            
        FILE *file=fopen(argv[i],"r");
        if (file!=NULL)
        {
            char str[5000];
            char ch=fgetc(file);
        while (ch!=EOF)
        {
            if (ch=='\n')
            {
                printf("$%c",ch);
            }
            else{
                printf("%c",ch);
            }
            ch=fgetc(file);
            
        }
        
        fclose(file);

        }
        else{
            printf("Error(%d): %s\n",errno,strerror(errno));
        }
        }
        
    }
    else{
        printf("cat : unrecognized option\n");
    }
    
    return 0;
}
