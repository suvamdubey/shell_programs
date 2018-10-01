#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<pwd.h>
#include<time.h>
#include<fcntl.h>
#include<limits.h>

#define ERR_CODE INT_MIN
#define EXIT_STATUS INT_MAX
#define MAX_TOKS 10
#define DELIMETERS " \n\t"

void init_display(char * user_name){
  system("clear");
	time_t t = time(NULL);
	struct tm* cur_time = localtime(&t);
	printf("Hi! %s,",user_name);
	if(cur_time->tm_hour > 5 && cur_time->tm_hour < 12) printf("Good Morning.\n");
	else if(cur_time->tm_hour >= 12 && cur_time->tm_hour < 4) printf("Good Evening.\n");
	else printf("Good Night.\n");
	printf("Welcome to JUBCSEIII.\n");
}

char * read_instruction(){
	ssize_t ins_size = 0;
  char * inst = NULL;
	getline(&inst,&ins_size,stdin);
  return inst;
}

char ** parse_by_space(char * inst){
  char ** args = NULL;
	if(!(args = (char **)(malloc(MAX_TOKS * sizeof(char *))))){
		printf("error: Memory allocation failure!\n");
    exit(0);
	}
	char * word = strtok(inst,DELIMETERS);    
  int i = 0;
  while( word!=NULL){
    args[i++] = strdup(word);
    word = strtok(NULL," \n");
  }
  args[i]=NULL;
  return args;
}

int spawn(char * command, char ** args){
	pid_t child_pid = fork();
  int child_status;
	if(child_pid != 0){
    wait(NULL);
		return child_pid;
	}	
	else{
		if(execvp(command,args) == -1){
      printf("error: invalid command\n");
			return ERR_CODE;
		}
    else{
      wait(&child_status);
      if(WIFEXITED(child_status)){
        /*printf("process complete\n");
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        int x = open("/dev/null", O_RDWR);   // Redirect input, output and stderr to /dev/null
        dup( x);*/
        return 0;
      }
      else{
        printf("abrupt termination of process\n");
        return ERR_CODE;
      }
    }
	}

}

int excecute_inst(char ** args){
	if(strcmp(args[0],"newdir") == 0){
		args[0] = "mkdir";
	}
	else if(strcmp(args[0],"editfile") == 0){
		args[0] = "vi";
	}
	else if(strcmp(args[0],"content")==0){
		args[0] = "cat";
	}
	else if(strcmp(args[0],"exitbcse")==0){
		return EXIT_STATUS;
	}
  else if(strcmp(args[0],"info")==0){
    args[0] = "stat";
  }
	return spawn(args[0],args);
}

void launch_shell(char * user_name){
	char *inst;
	char ** args;
	int status;
	do{
    printf("jubcse$ ");
		inst = read_instruction();
		if(strlen(inst) <= 1){
      continue;free(inst);
    }
  	args = parse_by_space(inst);
    //for(int i = 0; i < MAX_TOKS; i++) printf("%s*", args[i]);
    status = excecute_inst(args);
    free(inst);
    free(args);
  }while(status != EXIT_STATUS);
}

int main(){
	char * user_name = getenv("USER");
	init_display(user_name);
	launch_shell(user_name);
	return 0;
}
