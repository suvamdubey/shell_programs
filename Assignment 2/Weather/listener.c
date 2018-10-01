#include <stdio.h>
#include <stdlib.h> // For exit() function
#include <unistd.h>
#include <string.h>
int main()
{
    char c[1000],p[1000];
    FILE *fptr;
    fork();
    while(1>0)
{

    if ((fptr = fopen("weather_report.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }

    // reads text until newline 
    fscanf(fptr,"%[^\n]", c);
	if (strcmp(c,p)!=0)

    	{
	printf("Listener #%d msg = $s\n", getpid(),c);
	strcpy(p,c);
	}
    fclose(fptr);
 }  
    return 0;
}
