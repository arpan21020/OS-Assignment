#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<errno.h>
#include<limits.h>
#include<sys/wait.h>

typedef struct data{
    char **console;
    int len;
}data;

data *spaceData(){
    data *consoleInput=(data*)malloc(sizeof(data));
    consoleInput->console=(char**)malloc(2048*sizeof(char*));
    consoleInput->len=0;
    return consoleInput;
}
void systemcalling(char *command){
    system(command);
    return NULL;
}
data * input(char user[]){
    data *commands=spaceData();
    char *get_input=(char*)malloc(sizeof(char)*2048);
    int idx=0;
    char prompt[2556];
    getcwd(prompt,sizeof(prompt));
    strcat(prompt,"/@host-");
    strcat(prompt,user);
    char wd[2556];
    sprintf(wd,"[%s]>>>",prompt);

    write(1,wd,strlen(wd));
    gets(get_input);

    char *split=strtok(get_input," ");
    while (split!=NULL)
    {
        commands->console[idx]=(char*)malloc(2048*sizeof(char));
        strcpy(commands->console[idx],split);
        commands->len++;
        split=strtok(NULL," ");
        idx++;
        }
    int remain=2048-1-idx;
    for (int i = 0; i < remain; i++)
    {
        commands->console[idx]=NULL;
    }
    
    return commands;
}
bool isinternalCommand(char* str){
    if((strcmp(str,"echo")==0) || (strcmp(str,"cd")==0) || (strcmp(str,"pwd")==0)){
        return true;
    }
    else return false;
}
bool isexternalCommand(char* str){
    if((strcmp(str,"ls")==0) || (strcmp(str,"cat")==0) || (strcmp(str,"date")==0) || (strcmp(str,"rm")==0) || (strcmp(str,"mkdir")==0)){
        return true;
    }
    else return false;
}

void pwd(char *option){
    // char *cwd=(char*)malloc(sizeof(char)*256);
    if (option==NULL || strcmp(option,"-P")==0 )
    {
        char cwd[256];
        if (getcwd(cwd,sizeof(cwd))==NULL)
        {
        printf("ERROR(%d): %s\n",errno,strerror(errno));
            
        }
        else{
            printf("%s",cwd);
        }
        

    }
    else if (strcmp(option,"-L")==0)
    {
        char cwd[256];
        char symlink[PATH_MAX];
        realpath(cwd,symlink);
        if (getcwd(cwd,sizeof(cwd))==NULL)
        {
        printf("ERROR(%d): %s\n",errno,strerror(errno));
            
        }
        else{
            printf("%s",cwd);
        }
    }

}

void echo(char *opt,data *args){
    if (opt != NULL && strcmp(opt,"--help")==0)
    {
        
        printf("echo [option]\n");
        printf("echo <text>\n");
        printf("echo -E <text>\n");

    }
    else if (opt != NULL &&strcmp(opt,"-E")==0)
    {
        for (int i = 2; i < args->len; i++)
        {
            int x=0;
            while(true){
                if (args->console[i][x]=='"')
                {
                    x++;
                    continue;
                }
                
                printf("%c",args->console[i][x]);
                x++;
                if (args->console[i][x]==NULL)
                {
                    break;
                }
                
            }
            printf(" ");
            
        }printf("\n");
    
    }
    
    else
    {
        for (int i = 1; i < args->len; i++)
        {
            int x=0;
            while(true){
                if (args->console[i][x]=='"')
                {
                    x++;
                    continue;
                }
                
                printf("%c",args->console[i][x]);
                x++;
                if (args->console[i][x]==NULL || args->console[i][x]==' ' || args->console[i][x]=='\n' || args->console[i][x]==EOF)
                {
                    break;
                }
                
            }
            printf(" ");
            
        }printf("\n");
    }    
}

void cd(char *args){
    if(args==NULL || strcmp(args,"--")==0 || strcmp(args,"~")==0){
        chdir(getenv("HOME"));
    }
    else if (chdir(args)!=0)
    {
        printf("ERROR(%d) :%s\n",errno,strerror(errno));
    }
    
    
}

void initialize(char user[]){
    
   
    // if(var[1][0]=='-'){
    //     printf("contains option\n");
    // }
    data* var;
    const char* CLEAR_SCREEN_ANSI=" \e[1;1H\e[2J";
        write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
         printf("********************************\n");
          printf("Welcome to Arpan's Shell\n");
    do
    {
    
    var=input(user);
    if (isexternalCommand(var->console[0]) && strcmp(var->console[var->len-1],"&t")!=0)
    {
        pid_t id;
        
        id=fork();
        if (id==0)
        {
            if (strcmp(var->console[0],"ls")==0)
        {
            execvp("/home/jarvis/assign1/ls",var->console);
            exit(0);

        }
        else if (strcmp(var->console[0],"cat")==0){

            execvp("/home/jarvis/assign1/cat",var->console);
            exit(0);
        }
        else if (strcmp(var->console[0],"date")==0)
        {
            execvp("/home/jarvis/assign1/date",var->console);
            exit(0);
        }
        else if (strcmp(var->console[0],"rm")==0)
        {
            execvp("/home/jarvis/assign1/remove",var->console);
            exit(0);
        }
        else if (strcmp(var->console[0],"mkdir")==0)
        {
            execvp("/home/jarvis/assign1/mkdir",var->console);
            exit(0);
        }

        
        
        }
        else{
            wait((int*)NULL);
        }   
        
    }
    else if (isexternalCommand(var->console[0]) && strcmp(var->console[var->len-1],"&t")==0)
    {
        char *path=(char*)malloc(2548*sizeof(char));

        strcat(path,"/home/jarvis/assign1/");
        pthread_t thread;
        if (strcmp(var->console[0],"ls")==0)
        {
            strcat(path,"ls");
            for (int i = 1; i < var->len-1; i++)
            {
                strcat(path," ");
                strcat(path,var->console[i]);
            }
        pthread_create(&thread,NULL,systemcalling,path); 
        pthread_join(thread,NULL);
        }
        else if (strcmp(var->console[0],"cat")==0)
        {
            strcat(path,"cat");
            for (int i = 1; i < var->len-1; i++)
            {
                strcat(path," ");
                strcat(path,var->console[i]);
            }
        pthread_create(&thread,NULL,systemcalling,path); 
        pthread_join(thread,NULL);
        }
        else if (strcmp(var->console[0],"date")==0)
        {
            strcat(path,"date");
            for (int i = 1; i < var->len-1; i++)
            {
                strcat(path," ");
                strcat(path,var->console[i]);
            }
        pthread_create(&thread,NULL,systemcalling,path); 
        pthread_join(thread,NULL);
        }
        else if (strcmp(var->console[0],"rm")==0)
        {
            strcat(path,"rm");
            for (int i = 1; i < var->len-1; i++)
            {
                strcat(path," ");
                strcat(path,var->console[i]);
            }
        pthread_create(&thread,NULL,systemcalling,path); 
        pthread_join(thread,NULL);
        }
        else if (strcmp(var->console[0],"mkdir")==0)
        {
            strcat(path,"mkdir");
            for (int i = 1; i < var->len-1; i++)
            {
                strcat(path," ");
                strcat(path,var->console[i]);
            }
        pthread_create(&thread,NULL,systemcalling,path); 
        pthread_join(thread,NULL);
        }
        
        
    }
    
    else if (isinternalCommand(var->console[0]))
    {
        if (strcmp(var->console[0],"pwd")==0)
        {
            if (var->console[1]!=NULL && var->console[1][0]=='-')
            {
                pwd(var->console[1]);
            }
            else{
                pwd(NULL);
            }
            printf("\n");
            
        }
        else if(strcmp(var->console[0],"echo")==0){
            if(var->console[1][0] !='-'){
                echo(NULL,var);
            }
            else{
                echo(var->console[1],var);
            }
        }
        else if (strcmp(var->console[0],"cd")==0)
        {
            cd(var->console[1]);

        }
        
       
        
        
    }
    else if (strcmp(var->console[0],"exit")==0)
    {
        break;
    }
    
    else{
        printf("ERROR : command not recognized\n");
        
    }
    // sleep(1);
    } while(strcmp(var->console[0],"exit"));
    
    
}


int main()
{
    const char* CLEAR_SCREEN_ANSI=" \e[1;1H\e[2J";
    write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
    printf("Initialzing Shell.....\n");
    char username[2048];
    char password[2048];
    label:
    printf("Host Login : ");
    scanf("%s",username);
    printf("Password : ");
    scanf("%s",password);
    getchar();
    if (strcmp(username,"Arpan")==0 && strcmp(password,"123")==0)
    {
        initialize(username);
    }
    else{
        printf("Login incorrect\n\n ");
        goto label;
        
    }
    return 0;
}