#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<errno.h>
#include<limits.h>
#include<sys/wait.h>
#include<dirent.h>

long int filesize(char filename[]){
    FILE *file=fopen(filename,"r");
    fseek(file,0L,SEEK_END);
    long int size=ftell(file);
    fclose(file);
    return size;
}
int main(int argc, char const *argv[])
{
    struct dirent *ptr;
    DIR *dir=opendir(".");
    if(argc==1){
        if (dir==NULL)
        {
            printf("Error(%d): %s",errno,strerror(errno));
            return 0;
        }
        while ((ptr=readdir(dir))!=NULL)
        {
            if (ptr->d_name[0]=='.')
            {
                continue;
            }
            
            printf("%s ",ptr->d_name);
        }
        
        
    }
    else
    {
        if (argv[1][1]=='a')
        {
             if (dir==NULL)
        {
            printf("Error(%d): %s",errno,strerror(errno));
            return 0;
        }
        while ((ptr=readdir(dir))!=NULL)
        {
            printf("%s ",ptr->d_name);
        }
        }
        else if (argv[1][1]=='1')
        {
            if (dir==NULL)
            {
                printf("Error(%d): %s",errno,strerror(errno));
                return 0;
            }
            while ((ptr=readdir(dir))!=NULL)
            {


                if (ptr->d_name[0]=='.')
            {
                continue;
            }
                printf("%s\n",ptr->d_name);
            }
            
            
        }
        else{
                printf("ls : invalid option\n");
            }
            
        
           
    }
    printf("\n");
    
    return 0;
}
