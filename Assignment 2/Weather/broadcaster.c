#include <stdio.h>
#include <stdlib.h>  /* For exit() function */
#include <unistd.h>
int main()
{
   FILE *fptr;

   
   
   for (int i=0;i<10;i++)

   {
	fptr = fopen("weather_report.txt", "w");
   	if(fptr == NULL)
   	{
      	printf("Error!");
      	exit(1);
   	}
	fprintf(fptr,"msg #%d", i);
	fclose(fptr);
	sleep(rand()%5);

}
   return 0;
}
