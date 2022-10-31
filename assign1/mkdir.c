#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<errno.h>
#include<limits.h>
#include<sys/wait.h>
#include<sys/stat.h>

int main(int argc, char const *argv[])
{
    if(argc==1){
        printf("mkdir : missing operand\n");
    }
    else if(strcmp(argv[1],"-v")==0){
        if(mkdir(argv[2],0777)==0){
            printf("mkdir: created directory '%s'\n",argv[2]);
        }
        else{
            printf("Error(%d):%s\n",errno,strerror(errno));
        }
    }
    else if(strcmp(argv[1],"-p")==0){
        if(mkdir(argv[2],0777)!=0 && errno==2){
            
             char *split=strtok(argv[2],"/");
             char cwd[2356];
             strcpy(cwd,split);
            while (split!=NULL)
            {
                int create=(mkdir(cwd,0777));
               
                
                strcat(cwd,"/");
                
                split=strtok(NULL,"/");
                if(split!=NULL)strcat(cwd,split);
            }
        }
            
        else{
            printf("Error(%d):%s\n",errno,strerror(errno));
        }

        }
    else if (argv[1][0]!='-')
    {
        if(mkdir(argv[1],0777)!=0){
            printf("Error(%d):%s\n",errno,strerror(errno));

        }
        
    }
    else{
        printf("mkdir : unrecognized option\n");
    }
    
    
    return 0;
}
