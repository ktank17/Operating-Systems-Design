#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>

int cnt = 0;
clock_t start = 0;
struct timeval begin;

char arr[100][100] = {{0}};

void sig_hand(int num)
{

	cnt += 10;
	printf("tick %d\n", cnt);
 
	alarm(100);
}

void sig_int(int num)
{
	printf("Caught Signal %s\n", strsignal(num));

	clock_t finish = clock();
	struct timeval end;
	gettimeofday(&end, NULL);
	double past= (double) (finish - start) / CLOCKS_PER_SEC;

	struct timeval variation = { end.tv_sec - begin.tv_sec, end.tv_usec - begin.tv_usec };
	if(variation.tv_usec < 0) { variation.tv_usec += 1000000; variation.tv_sec -= 1; }

	printf("%15s %s\n", "Systime", "Usrtime");
	printf("%15f %ld.%06ld\n", past, variation.tv_sec, variation.tv_usec);
}

void sig_stop(int num)
{
	 printf("Caught Signal %s\n", strsignal(num));
	 int i=0;
	 for(i=0; i< 10; i++)
	 if(strlen(arr[i]))
	 printf("%s\n", arr[i]);
	 printf("\n");
}

void sig_term(int num)
{
	printf("Caught Signal %s\n", strsignal(num));
	struct timeval end;
	clock_t finish = clock();
	gettimeofday(&end, NULL);
	double past= (double) (finish - start) / CLOCKS_PER_SEC;
	struct timeval variation = { end.tv_sec - begin.tv_sec, end.tv_usec - begin.tv_usec };
	if(variation.tv_usec < 0) { variation.tv_usec += 1000000; variation.tv_sec -= 1; }
	printf("%15s %s\n", "Systime", "Usrtime");
	printf("%15f %ld.%06ld\n", past, variation.tv_sec, variation.tv_usec);
	exit(EXIT_SUCCESS);
} 

int main()
{

	start = clock();
	gettimeofday(&begin, NULL);
	int i, arrCnt = 0;
	char tempstr[80]; 
	signal(SIGALRM, sig_hand); 
	signal(SIGINT , sig_int); 
	signal(SIGTERM, sig_term);
	signal(SIGTSTP, sig_stop);
	printf("tick %d\n", cnt);
	alarm(100);
 
	while(1)
	{

		 fgets(tempstr, 79, stdin);

		if(arrCnt >= 10)
		{
			for(i=1; i< 10; i++)
				strcpy(arr[i-1], arr[i]);
				arrCnt--;
		}

	strcpy(arr[arrCnt], tempstr);

	printf("%s\n", arr[arrCnt]);

	arrCnt++;
	
	}
	
	return 0;
}




