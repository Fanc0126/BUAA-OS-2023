#include <lib.h>

int global = 0;
void handler1(int num) {
    debugf("Reach handler1, now the signum is %d!\n", num);
    global ++;
}
void handler2(int num) {
    debugf("Reach handler2, now the signum is %d!\n", num);
    global ++;
}
void handler3(int num) {
    debugf("Reach handler3, now the signum is %d!\n", num);
    global ++;
}
#define TEST_NUM_1 2
#define TEST_NUM_2 6
#define TEST_NUM_3 12
int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sig;
    sig.sa_handler = handler1;
    sig.sa_mask = set;
    panic_on(sigaction(TEST_NUM_1, &sig, NULL));

    sig.sa_handler = handler2;
    panic_on(sigaction(TEST_NUM_2, &sig, NULL));

    sig.sa_handler = handler3;
    panic_on(sigaction(TEST_NUM_3, &sig, NULL));
	
    sigaddset(&set, TEST_NUM_1);
    sigaddset(&set, TEST_NUM_2);
    sigaddset(&set, TEST_NUM_3);
    panic_on(sigprocmask(0, &set, NULL));
    kill(0, TEST_NUM_1);
    kill(0, TEST_NUM_2);
    kill(0, TEST_NUM_3);
    int ans = 0;
    for (int i = 0; i < 10000000; i++) {
        ans += i;
    }
    panic_on(sigprocmask(1, &set, NULL));
    debugf("global = %d.\n", global);
    return 0;
}

