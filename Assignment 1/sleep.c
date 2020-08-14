#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>

void handler()
{
	printf("\nThis is a sleep function !!!");
}

void CustSleep(int secs)
{
	sigset_t SigMask;
	struct sigaction SigAction,OldAction;
	
	if(sigaddset(&SigMask,SIGTERM)==-1||sigprocmask(SIG_SETMASK,&SigMask,0)==-1)
		perror("[Error]:Setting signal");

	SigAction.sa_handler=(void*)handler;
	
	SigAction.sa_flags=0;
	
	if(sigaction(SIGALRM,&SigAction,&OldAction)==-1)
		perror("[Error]:Signal action");

	alarm(secs);
	
	pause();
}

int main()
{
	printf("\nInitiated !!!");
	CustSleep(2);
	return 0;
}


