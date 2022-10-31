#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<errno.h>
#include<limits.h>
#include<sys/wait.h>
#include<time.h>
int main(int argc, char const *argv[])
{
    time_t tim=time(NULL);
    if (argc==1 ||(strcmp(argv[1],"-u")==0))
    {
    printf("UTC %s",asctime(localtime(&tim)));
        
    }
    else if (strcmp(argv[1],"-I")==0)
    {
       struct tm t=*localtime(&tim);

    printf("%d-%d-%d",t.tm_year+1900,t.tm_mon+1,t.tm_mday);
        
    }
    else if(strcmp(argv[1],"--help")==0){
        // FILE *file=fopen()
        printf("Usage: date [OPTION]\n");
        printf("\nMandatory arguments to short options are mandatory.\n");
        printf("-I        output date in ISO 8601 format. Example: 2006-08-14\n");
        printf("--help    display this help and exit\n");
    }
    else{
        printf("date : invalid option");
    }
    
    
        
    
    printf("\n");
    // getchar();
    return 0;
}