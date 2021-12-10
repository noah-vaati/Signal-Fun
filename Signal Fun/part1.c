//Noah Redden
//7841009
//COMP 3430, Assignment 2 
//part1 - pipes

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define PIPE_SIZE 64
#define ARGS_SIZE 100

//keeps track of which word should be changed to what; false is 0
int dogToCat = 0;
int catToDog = 0;

//pipe
int p[2];

void catchSignal(int);

int main(int argc, char *argv[]){

	//set up pipe
	if(pipe(p)<0)exit(1);

	//program to run
	char *prog;

	char *progArgs[argc];

	//program args
	if(argc>2){
		//has arguments
		progArgs[argc-1] = NULL;
	}else{
		//no arguments
		progArgs[0] = " ";
		progArgs[1] = NULL;
	}

	//args
	if(argc > 1){
		
		

		prog = argv[1];

		for(int i = 1; i < argc; i++){	
			progArgs[i-1] = argv[i];
		}

	}else{
		printf("Please enter CL arguments.\nUsage: part1 (file to run) (file arguments)\n");
		exit(1);
	}

	int rc = fork();

	if(rc==0){
		//child
		close(p[0]);

		//replace stdout with pipe write end
		dup2(p[1], STDOUT_FILENO);

		//launch program
		execvp(prog, progArgs);
	
	}else{
		//parent

		close(p[1]);

		//read from pipe
		char pStr[PIPE_SIZE];

		

		while(read(p[0], pStr, 1) > 0){
			signal(SIGUSR1, catchSignal);	
			signal(SIGUSR2, catchSignal);
			signal(SIGALRM, catchSignal);

			//used keep track of us being on track to spell out 'cat' or 'dog'
			int wordProgress = 0;

			//backup of last 1-2 chars
			char backup1[PIPE_SIZE];
			char backup2[PIPE_SIZE];

			if(dogToCat){
				//dogToCat

				//check 'D'
				if(wordProgress == 0 && (!strcmp(pStr,"d")||!strcmp(pStr,"D"))){
					strcpy(backup1,pStr);
					wordProgress++;
					read(p[0], pStr, 1);
				}

				//check 'O'
				if(wordProgress == 1 && (!strcmp(pStr,"o")||!strcmp(pStr,"O"))){
					strcpy(backup2,pStr);
					wordProgress++;
					read(p[0], pStr, 1);
				}else if(wordProgress == 1){
					write(STDOUT_FILENO, backup1, 1);

					write(STDOUT_FILENO, pStr, 1);
				}

				//check 'G'
				if(wordProgress == 2 && (!strcmp(pStr,"g")||!strcmp(pStr,"G"))){
					wordProgress++;

					//dont ask
					write(STDOUT_FILENO, "c", 1);
					write(STDOUT_FILENO, "a", 1);
					write(STDOUT_FILENO, "t", 1);
					//just dont

				}else if(wordProgress == 2){
					write(STDOUT_FILENO, backup1, 1);
					write(STDOUT_FILENO, backup2, 1);

					write(STDOUT_FILENO, pStr, 1);
				}

			}else if(catToDog){
				//catToDog
				
				//check 'C'
				if(wordProgress == 0 && (!strcmp(pStr,"c")||!strcmp(pStr,"C"))){
					strcpy(backup1,pStr);
					wordProgress++;
					read(p[0], pStr, 1);
				}

				//check 'A'
				if(wordProgress == 1 && (!strcmp(pStr,"a")||!strcmp(pStr,"A"))){
					strcpy(backup2,pStr);
					wordProgress++;
					read(p[0], pStr, 1);
				}else if(wordProgress == 1){
					write(STDOUT_FILENO, backup1, 1);

					write(STDOUT_FILENO, pStr, 1);
				}

				//check 'T'
				if(wordProgress == 2 && (!strcmp(pStr,"t")||!strcmp(pStr,"T"))){
					wordProgress++;

					//dont ask
					write(STDOUT_FILENO, "d", 1);
					write(STDOUT_FILENO, "o", 1);
					write(STDOUT_FILENO, "g", 1);
					//just dont

				}else if(wordProgress == 2){
					write(STDOUT_FILENO, backup1, 1);
					write(STDOUT_FILENO, backup2, 1);

					write(STDOUT_FILENO, pStr, 1);
				}

			}

			if(wordProgress==0)write(STDOUT_FILENO, pStr, 1);
		}
	
		close(p[0]);

		wait(NULL); 
		
	}
	

	return(0);
}

void catchSignal(int sigNum){
	//dogToCat and catToDog should not be on at same time
	if(sigNum == SIGUSR1){
		dogToCat = 1;
		catToDog = 0;
	}else if(sigNum == SIGUSR2){
		catToDog = 1;
		dogToCat = 0;
	}else if(sigNum == SIGALRM){
		dogToCat = 0;
		catToDog = 0;
	}
}
