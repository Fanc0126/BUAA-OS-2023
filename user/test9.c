#include <lib.h>

int global = 0;
void handler(int num) {
    debugf("Reach handler, now the signum is %d!\n", num);
    sigset_t set;
    sigset_t oldset;
    sigprocmask(0, &set, &oldset);
    debugf("Processing:blocked signal 2? : %d\n",sigismember(&oldset, 2)); 
    debugf("Processing:blocked signal 3? : %d\n",sigismember(&oldset, 3));
    global = 1;
}

#define TEST_NUM 2
int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sig;
    sig.sa_handler = handler;
    sigaddset(&set, TEST_NUM);
    sigaddset(&set, 3);
    sig.sa_mask = set;
    panic_on(sigaction(TEST_NUM, &sig, NULL));
    panic_on(sigprocmask(0, &set, NULL));
    kill(0, TEST_NUM);
    int ans = 0;
    for (int i = 0; i < 10000000; i++) {
        ans += i;
    }
    sigdelset(&set,3);
    panic_on(sigprocmask(1, &set, NULL));
    sigset_t oldset;
    sigemptyset(&set);
    sigprocmask(0, &set, &oldset);
    debugf("blocked signal 2? : %d\n",sigismember(&oldset, 2));
    debugf("blocked signal 3? : %d\n",sigismember(&oldset, 3));
    debugf("global = %d.\n", global);
    return 0;
}

