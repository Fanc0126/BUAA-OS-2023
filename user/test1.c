#include <lib.h>

int global = 0;
void handler(int num) {
	debugf("just test Signal registration\n");
	global = 1;
}

int main(int argc, char **argv) {
	int n;
	sigset_t set;
	set.sig[0]=1;
	set.sig[1]=1;
	sigemptyset(&set);
	debugf("sig[0] = %d.\n", set.sig[0]);
	debugf("sig[1] = %d.\n", set.sig[1]);
	sigfillset(&set);
	debugf("sig[0] = %d.\n", set.sig[0]);
	debugf("sig[1] = %d.\n", set.sig[1]);
	sigdelset(&set,32);
	sigdelset(&set,64);
	debugf("sig[0] = %d.\n", set.sig[0]);
	debugf("sig[1] = %d.\n", set.sig[1]);
	sigaddset(&set,32);
	sigaddset(&set,64);
	debugf("sig[0] = %d.\n", set.sig[0]);
	debugf("sig[1] = %d.\n", set.sig[1]);
	sigdelset(&set,1);
	n=sigismember(&set,1);
	debugf("0 = %d.\n", n);
	n=sigismember(&set,33);
	debugf("1 = %d.\n", n);
	struct sigaction sig;
	sig.sa_handler = handler;
	sig.sa_mask = set;
	sigset_t set_2;
	struct sigaction sig_2;
	sig_2.sa_handler = handler;
	panic_on(sigaction(2, &sig, NULL));
	panic_on(sigaction(2, &sig_2, &sig_2));
	debugf("old = %d.\n", sig_2.sa_mask.sig[1]);
	panic_on(sigprocmask(0, &set, &set_2));
	debugf("old = %d.\n", set_2.sig[0]);
	sigemptyset(&set);
	sigaddset(&set,64);
	panic_on(sigprocmask(1, &set, &set_2));
	debugf("old = %d.\n", set_2.sig[1]);
	sigfillset(&set);  
	panic_on(sigprocmask(2, &set, &set_2));
	debugf("old = %d.\n", set_2.sig[1]); 
	panic_on(sigprocmask(0, &set, &set_2));
	debugf("old = %d.\n", set_2.sig[0]);
	return 0;
}
