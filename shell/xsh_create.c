/* xsh_create.c - xsh_create */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*--------------------------------------------------------------------
 * xsh_create - shell command to create
 *--------------------------------------------------------------------
 */
shellcmd xsh_create(int nargs, char *args[])
{
    int32   priority;	
    char    ch;
    char    *chprio;
    pid32   pid;
    
    if (nargs == 1) {
        priority=20;
        
    }
    else if (nargs == 2) {
        chprio = args[1];
        ch = *chprio++;
        priority = 0;
        while (ch != NULLCH) {
            if ((ch < '0') || (ch > '9')) {
                kprintf("%s: non-digit in priority\n", args[1]);
                return 1;
            }
            priority = 10*priority + (ch - '0');
            ch = *chprio++;
        }
        if (priority < (pri16)MINKEY) {
            kprintf("%s: invalid priority\n", args[1]);
            return 1;
        }
    }
    else {
        kprintf("Too many arguments\n");
        return 1;
    }
    pid = create(runforever, 1024, priority, "Test", 1, priority);
    resume(pid);
	
    return 0;
}
