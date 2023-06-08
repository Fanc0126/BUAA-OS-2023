#include <lib.h>
int global=0;
void handler(int num) {
    debugf("test the Non-blocking signal\n");
    global++;
}

#define TEST_NUM 9
int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sig;
    sig.sa_handler = handler;
    sig.sa_mask = set;
    panic_on(sigaction(TEST_NUM, &sig, NULL));
    sigaddset(&set, TEST_NUM);
    panic_on(sigprocmask(0, &set, NULL));
    debugf("Signal blocked\n");
    kill(0, TEST_NUM);
//    debugf("Signal blocked\n");
    int ans = 0;
    for (int i = 0; i < 10000000; i++) {
        ans += i;
    }
    debugf("Signal unblocking\n");
    panic_on(sigprocmask(1, &set, NULL));
    
    debugf("global = %d.\n", global);
    return 0;
}

