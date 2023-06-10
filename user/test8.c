#include <lib.h>
int global = 0;
void handler(int num) {
    debugf("Reach handler, now the signum is %d!\n", num);
    global = 1;
}

int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sig;
    sig.sa_handler = handler;
    sig.sa_mask = set;
    panic_on(sigaction(6, &sig, NULL));
    sigaddset(&set, 6);
    panic_on(sigprocmask(0, &set, NULL));
    int ret = fork();
    if (ret != 0) {
    	debugf("there is father\n");
	kill(ret, 6);
	debugf("test father end\n");
    } else {
    	debugf("there is child\n");
	panic_on(sigprocmask(1, &set, NULL));
	debugf("global = %d.\n", global);
	debugf("test child end\n");
    }
    return 0;
}

