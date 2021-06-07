#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>

int main(void) {
	pid_t tid = getpid();
	int nicevalue, pid, flag, prio_user, nice_user, *prio, *nice;
	prio = &prio_user;
	nice = &nice_user;

	printf("Pid of current process is %d.\n", tid);
	printf("Please input process pid:");
	scanf("%d", &pid);

	if (kill(pid, 0)) {
		printf("Process doesn't exist.\n");
		return 1;
	}

	printf("Please input flag:");
	scanf("%d", &flag);

	if (flag == 1) {
		printf("Please input nice value:");
		scanf("%d", &nicevalue);
	} else
		nicevalue = 0;
	

	int ret = syscall(500, pid, flag, nicevalue, prio, nice);
	if (ret == EFAULT) {
		printf("Operation failed. Error occoured.\n");
		return 1;
	} else {
		printf("Operation proceed. Nice value is %d, prio is %d.\n", nice_user, prio_user);
		return 0;
	}
}

