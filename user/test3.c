#include <lib.h>

sigset_t set2;

int main(int argc, char **argv) {
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, 1);
	sigaddset(&set, 2);
	panic_on(sigprocmask(0, &set, NULL));
	sigdelset(&set, 2);
	int ret = fork();
	if (ret != 0) {
		debugf("father ok\n");
		panic_on(sigprocmask(0, &set2, &set));
		int fc=sigismember(&set, 2);
		//printf("Father: %d.\n", sigismember(&set, 2));
		debugf("Father: %d.\n", fc);
	} else {
		debugf("child ok\n");
		int fc=sigismember(&set, 2);
		//printf("Child: %d.\n", sigismember(&set, 2));
		debugf("Child: %d.\n", fc);
	       }
	   return 0;
}
