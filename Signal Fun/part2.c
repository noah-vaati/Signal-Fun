//Noah Redden
//7841009
//COMP 3430, Assignment 1 
//part2 - signals 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

//what signal are we sending? Should be set to 1 or 2, later in the code
int signalSend = 0;

//prototype
//catches signals
void catchSignal(int);

int main(int argc, char *argv[]){
	
	if(argc>1){
		if(atoi(argv[1])==1){
			//if arg is 1, send signal USR1
			signalSend = 1;
		}else if(atoi(argv[1])==2){
			//if arg is 2, send signal USR2
			signalSend = 2;
		}else{
			printf("Please enter 1 or 2 in Arguments\n");
			return(0);
		}

		//set up pid
		int pid = getpid();
		pid++;//should be child id


		//fork
		int rc = fork();

		if(rc==0){
			//child

			signal(SIGUSR1, catchSignal);	
			signal(SIGUSR2, catchSignal);
			sleep(10);

		}else{
			//parent
			sleep(1);//wait a second for child...

			//send 1st signal to child
			printf("Parent sending 1st signal USR1...\n");
			kill(pid, SIGUSR1);

			//wait a little bit, then send another signal
			sleep(3);

			//send 2nd signal to child
			printf("Parent sending 2nd signal USR%i...\n",signalSend);
			if(signalSend==1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);

			printf("Parent finished, waiting for child now.\n");

			wait(NULL);
		}


	}else{
		printf("Please enter 1 or 2 in Arguments\n");
	}
	return(0);
}

//catches signals
void catchSignal(int sigNum){
	if(sigNum == SIGUSR1){
		printf("Recieved USR1!\n");
		for(int i = 0; i < 10; i++){
			printf("USR1 Loop...%i\n",i);
			sleep(1);
		}
		printf("USR1 Finished.\n");
	}else if(sigNum == SIGUSR2){
		printf("Recieved USR2!\n");
		for(int i = 0; i < 10; i++){
			printf("USR2 Loop...%i\n",i);
			sleep(1);
		}
		printf("USR2 Finished.\n");
	}
}

