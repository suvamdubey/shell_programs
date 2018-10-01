#include  <stdio.h>
#include  <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#define   MAX_COUNT  10

void  xProcess(pid_t);                /* x process prototype  */
void  yProcess(pid_t);               /* y process prototype */
/*void waitX();
void signalX();
void waitY();
void signalY();
*/
sem_t *X,*Y;
int  main()
{
     pid_t  x,y;
     X = sem_open("/x", O_CREAT, 0644, 1);
     Y = sem_open("/y", O_CREAT, 0644, 0);
     x = fork();
	//xProcess(getpid());
     
     if (x==0)
	xProcess(getpid());
     else
	{ y=fork();
          if (y==0)
          yProcess(getpid());
	}

}

void  xProcess(pid_t x)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
	{ sem_wait(X);
          printf("Process X with pid = %d is in iteration %d\n", x,i);
	  sem_post(Y);
	}
}

void  yProcess(pid_t y)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
         {sem_wait(Y);
	  printf("Process Y with pid = %d is in iteration %d\n", y,i);
	  sem_post(X);
	}
     
}
/*
void waitX()
{
	while(X<0);
	X--;
}
void signalX()
{
	X++;
}
void waitY()
{
	while(Y<0);
	Y--;
}
void signalY()
{
	Y++;
}
*/
