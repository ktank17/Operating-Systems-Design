#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

void tw(int fs,int bs)
{
	int i,j;
	char fn[50];
	int total_fs=fs*1024;
	char buffer[total_fs];
	for(i=0;i<total_fs;i++)
	{
		buffer[i]='0';
	}
	struct timeval start,end;
	int calls=0;
	gettimeofday(&start,NULL);
	for(i=0;i<10;i++)
	{

		char temp[20];
		snprintf(temp,20,"%d",bs);
		strcat(fn,temp);
		snprintf(temp,20,"%d",i);
		strcat(fn,temp);
		strcat(fn,"w.txt");
		int fd=open(fn,O_WRONLY|O_CREAT);
		for(j=0;j<total_fs;j=j+bs)
		{
			write(fd,buffer,bs);
			calls++;
		}
		close(fd);
		memset(fn,0,50);
	}
	gettimeofday(&end,NULL);
	
	printf("\n%12d %15e %20d",bs,(end.tv_sec*1e6 + end.tv_usec) - (start.tv_sec*1e6 + start.tv_usec),calls);	
	
}

void test_f(int fs,int bs)
{
	int i,j;
	char fn[50];
	int total_fs=fs*1024;
	char buffer[total_fs];
	for(i=0;i<total_fs;i++)
	{
		buffer[i]='0';
	}
	struct timeval start,end;
	int calls=0;	
	gettimeofday(&start,NULL);
	for(i=0;i<10;i++)
	{

		char temp[20];
		snprintf(temp,20,"%d",bs);
		strcat(fn,temp);
		snprintf(temp,20,"%d",i);
		strcat(fn,temp);
		strcat(fn,"f.txt");
		FILE* fd=fopen(fn,"w");
		for(j=0;j<total_fs;j=j+bs)
		{
			calls++;
			fwrite(buffer,1,bs,fd);
		}
		fclose(fd);
		memset(fn,0,50);
	}
	gettimeofday(&end,NULL);
	
	printf("\n%12d %15e %20d",bs,(end.tv_sec*1e6 + end.tv_usec) - (start.tv_sec*1e6 + start.tv_usec),calls);	
	
}
void perform()
{
	
	printf("Execution started");
	int bytes[]={2,16,128,1024,8192,65536};
	int fs=128;
	char buffer[fs*1024];
	int i;
	printf("\nwrite() function call");
	printf("\n%12s %15s %20s","Buffer size","Elapsed time","Number of function calls");	
	for(i=0;i<6;i++)
	{
		tw(fs,bytes[i]);
	}
	printf("\nfwrite() function call");
	printf("\n%12s %15s %20s","Buffer size","Elapsed time","Number of function calls");
	for(i=0;i<6;i++)
	{
		test_f(fs,bytes[i]);
	}
	printf("\n");

}
int main()
{
	perform();
	return 0;
}


