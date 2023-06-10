#include <lib.h>
int global = 0;
int *test = NULL;
void handler_1(int num) {
    debugf("Reach handler_1, now the signum is %d!\n", num);
    global ++;
}
void handler_2(int num) {
    debugf("Reach handler_2, now the signum is %d!\n", num);
    global ++;
}
int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sig;
    sig.sa_handler = handler_1;
    sig.sa_mask = set;
    panic_on(sigaction(6, &sig, NULL));
    sig.sa_handler = handler_2;
    panic_on(sigaction(12, &sig, NULL));
    sigaddset(&set, 6);
    sigaddset(&set, 12);
    panic_on(sigprocmask(0, &set, NULL));
    kill(0,6);
    debugf("kill 6\n");
    int ret = fork();
    if (ret != 0) {
    	debugf("there is father\n");
	kill(ret, 12);
	debugf("send signal 12 to child\n");
	panic_on(sigprocmask(1, &set, NULL));
	debugf("father deal with %d signals\n",global);
	*test = 10;
	debugf("test father end\n");
    } else {
    	debugf("there is child\n");
	panic_on(sigprocmask(1, &set, NULL));
	debugf("child deal with %d signals\n",global);
	debugf("test child end\n");
    }
    return 0;
}

