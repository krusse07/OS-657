/* xsh_rend.c - xsh_rend */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

sid32 sem_a, sem_b;
pid32 spid, wpid, apid, bpid;
void alice1();
void bob1();
int32 aprio, bprio;
int32 counter;


/*-------------------------------------------------------------------
 * xsh_rend - shell command for lab 4 synchronization problem
 *-------------------------------------------------------------------
 */
shellcmd xsh_rend(int nargs, char *args[])
{
	sem_a = semcreate(0);
    sem_b = semcreate(0);
	
	counter = 0;

    srand(getpid());
    int32 rand_num = rand();

    int32 aprio, bprio;
    bprio = 15;

    if (rand_num % 2 == 0) {
	aprio = 20;
    } else {
	aprio = 10;
    } 

    apid = create(alice1, 1024, aprio, "alice", 0);
    bpid = create(bob1, 1024, bprio, "bob", 0);

    resume(apid);
    resume(bpid); 

}

void alice1() {
    kprintf("A1: My first statement appears before Bob's second statement\n");
	counter++;
	if (counter > 1){ // bob went first;
		chprio(apid, 15);
		semdelete(sem_a);
		semdelete(sem_b);
	} else { // alice went first
		wait(sem_b);
	}
    kprintf("A2: This is Alice's second statement\n");
}

void bob1() {
    kprintf("B1: My first statement appears before Alice's second statement\n");
	counter++;
	if (counter > 1) { // alice went first
		chprio(bpid, 20);
		semdelete(sem_a);
		semdelete(sem_b);
	} else {
		wait(sem_a);
	}
    kprintf("B2: This is Bob's second statement\n");
}
