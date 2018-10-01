#include  <stdio.h>
#include  <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define   MAX_COUNT  10

void  xProcess(pid_t);                /* x process prototype  */
void  yProcess(pid_t);               /* y process prototype */

int  main()
{
     pid_t  x,y;
	
     x = fork();
     y = fork();
     if (x==0)
	xProcess(x);
     if (y==0)
         yProcess(y);
}

void  xProcess(pid_t x)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("Process X with pid = %d is in iteration %d\n", x,i);
     srand(time(0));
     sleep(rand()%10);
}

void  yProcess(pid_t y)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
         printf("Process Y with pid = %d is in iteration %d\n", y,i);
     srand(time(0));
     sleep(rand()%10);
}

