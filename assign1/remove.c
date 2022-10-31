#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdbool.h>
#include<errno.h>
#include<limits.h>
#include<sys/wait.h>

bool dir(const char* file){
    struct stat route;
    stat(file,&route);
    if(S_ISREG(route.st_mode)==0){
        return true;
    }
    else return false;
}
int main(int argc, char const *argv[])
{
    
    if (argc==1)
    {
        printf("rm : missing operand\n");
    }
    else if (strcmp(argv[1],"-v")==0)
    {
        if(!dir((const char*)argv[2])){

        
        if (remove(argv[2])==0)
        {
            printf("removed %s\n",argv[2]);
        }
        else printf("Error(%d): %s\n",errno,strerror(errno));
        }
        else{
            printf("Error(21) : %s\n",strerror(21));
        }
    }
    else if (strcmp(argv[1],"-d")==0)
    {
        
        
        if (remove(argv[2])!=0)
        {
            printf("Error(%d):%s\n",errno,strerror(errno));
        }

        
    }
    else if (argv[1][0]!='-')
    {
        if(!dir((const char*)argv[1])){

        
        if (remove(argv[1])==0)
        {
            printf("removed %s\n",argv[1]);
        }
        else printf("Error(%d): %s\n",errno,strerror(errno));
        }
        else{
            printf("Error(21) : %s\n",strerror(21));
        }
    }
    else{
        printf("rm : unrecognized option\n");
    }
    
    
    
    
    return 0;
}
