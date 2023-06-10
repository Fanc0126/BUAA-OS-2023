#include <lib.h>
sigset_t set_2;
int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, 1);
    sigaddset(&set, 9);
    sigaddset(&set, 11);
    sigaddset(&set, 15);
    panic_on(sigprocmask(0, &set, NULL));
    debugf("block all\n");
    kill(0,1);
    debugf("kill 1\n");
    sigaddset(&set_2, 1);
    panic_on(sigprocmask(1, &set_2, NULL));
    int ret = fork();
    if (ret != 0) {
	ret=fork();
	if(ret!=0){
	debugf("Father begin,and kill 9\n");
	kill(0,9);
	sigemptyset(&set_2);
	sigaddset(&set_2, 9);
	debugf("cancel  block 9\n");
	panic_on(sigprocmask(1, &set_2, NULL));
	debugf("Father end\n");
	}
	else{
	debugf("Child2 begin,and kill 11\n");
	kill(0,11);
	sigemptyset(&set_2);
	sigaddset(&set_2, 11);
	debugf("cancel  block 11\n");
	panic_on(sigprocmask(1, &set_2, NULL));
	debugf("Child2 end\n");
	}
    } else {
	debugf("Child1 begin,and kill 15\n");
	kill(0,15);
	sigemptyset(&set_2);
	sigaddset(&set_2, 15);
	debugf("cancel  block 15\n");
	panic_on(sigprocmask(1, &set_2, NULL));
	debugf("Child1 end\n");
    }
    return 0;
}

