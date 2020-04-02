/* xsh_go.c - main, printName */

#include <xinu.h>
#include <stdio.h>

int printName();
pid32 apid, bpid, cpid;

shellcmd xsh_go(int nargs, char *args[])
{
	apid = create(printName, 1024,  5, "process2", 1, "process2");
	bpid = create(printName, 1024, 10, "process3", 1, "process3");
	cpid = create(printName, 1024, 20, "process4", 1, "process4");	
	
	resume(apid);
	resume(bpid);
	resume(cpid);

	
}


/* Print the process name, sleep for 15 seconds, print process name 10 more times */
int printName(char* c) {

	kprintf("%s is running\n", c);
	sleepms(5000);

	int32 i;
	
	for (i = 1; i < 12; i++ ){
		kprintf("%s is running\n", c);
	}
	return OK;
	
}