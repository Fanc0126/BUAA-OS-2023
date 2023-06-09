#include <lib.h>
int global = 0;
int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int *test = NULL;
void handler_2(int num){
	debugf("Reach handler_2, now the signum is %d!\n", num);
	global=2;
}
void sgv_handler(int num) {
    debugf("Segment fault appear!\n");
    test = &a[6];
    debugf("test = %d.\n", *test);
    exit();
}
void handler(int num) {
    debugf("Reach handler, now the signum is %d!\n", num);
    debugf("global = %d.\n", global);
    sigset_t set;
    sigaddset(&set, 3);
    kill(0, 3);
    panic_on(sigprocmask(1, &set, NULL));
    debugf("global = %d.\n", global);
    *test = 10;
    global = 1;
}

#define TEST_NUM 2
int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sig;
    sig.sa_handler = handler;
    sig.sa_mask = set;
    panic_on(sigaction(TEST_NUM, &sig, NULL));
    sig.sa_handler = handler_2;
    panic_on(sigaction(3, &sig, NULL));
    sigaddset(&set, TEST_NUM);
    sigaddset(&set, 3);
    panic_on(sigprocmask(0, &set, NULL));
    kill(0, TEST_NUM);
    sig.sa_handler = sgv_handler;
    sig.sa_mask = set;
    panic_on(sigaction(11, &sig, NULL));
    int ans = 0;
    for (int i = 0; i < 10000000; i++) {
        ans += i;
    }
    panic_on(sigprocmask(1, &set, NULL));
    debugf("global = %d.\n", global);
    return 0;
}

