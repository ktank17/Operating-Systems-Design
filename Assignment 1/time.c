#include<sys/wait.h>
#include<time.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void parse_args(int len,char* array[])
{
	int i;
	for(i=0;i<len-1;i++)
		array[i]=array[i+1];
	array[len-1]=NULL;
}

int main(int argc,char **argv)
{
	parse_args(argc,argv);
	clock_t start,end;
	
	start=clock();
	switch(fork())
	{
		case (pid_t)-1:
				perror("Error while executing !!!");
				break;
		case (pid_t)0:
				execvp(argv[0],argv);
				_exit(15);
				break;
		default:
				wait(NULL);
				end=clock();
	}
	printf("\n\n\nProcess Execution Time:%f secs\n\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}

