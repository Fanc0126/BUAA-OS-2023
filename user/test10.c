#include <lib.h>

int global = 0;
void handler_1(int num) {
    debugf("Reach handler_1, now the signum is %d!\n", num);
    sigset_t set;
    sigset_t oldset;
    sigprocmask(0, &set, &oldset);
    debugf("the handler_1 has blocked 2:%d ; 3:%d ; 4:%d ; 5:%d\n",sigismember(&oldset, 2),sigismember(&oldset, 3),sigismember(&oldset, 4),sigismember(&oldset, 5));
    global++;
}
void handler_2(int num) {
    debugf("Reach handler_2, now the signum is %d!\n", num);
    sigset_t set;
    sigset_t oldset;
    sigprocmask(0, &set, &oldset);
 debugf("the handler_2 has blocked(before reentry) 2:%d ; 3:%d ; 4:%d ; 5:%d\n",sigismember(&oldset, 2),sigismember(&oldset, 3),sigismember(&oldset, 4),sigismember(&oldset, 5));
    sigaddset(&set, 4);
    kill(0, 4);
    sigprocmask(1, &set, NULL);
    sigemptyset(&set);
    sigprocmask(0, &set, &oldset);
debugf("the handler_2 has blocked(after reentry) 2:%d ; 3:%d ; 4:%d ; 5:%d\n",sigismember(&oldset, 2),sigismember(&oldset, 3),sigismember(&oldset, 4),sigismember(&oldset, 5));
    global++;
}
void handler_3(int num) {
    debugf("Reach handler_3, now the signum is %d!\n", num);
    sigset_t set;
    sigset_t oldset;
    sigprocmask(0, &set, &oldset);
    debugf("the handler_3 has blocked 2:%d ; 3:%d ; 4:%d ; 5:%d\n",sigismember(&oldset, 2),sigismember(&oldset, 3),sigismember(&oldset, 4),sigismember(&oldset, 5));
    global++;
}

int main(int argc, char **argv) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sig;
    sig.sa_handler = handler_1;
    sigaddset(&set, 2);
    sigaddset(&set, 3);
    sig.sa_mask = set;
    panic_on(sigaction(2, &sig, NULL));
     sig.sa_handler = handler_2;
     sigaddset(&set, 4);
     sig.sa_mask = set;
     panic_on(sigaction(3, &sig, NULL));
     sig.sa_handler = handler_3;
     sigaddset(&set, 5);
     sig.sa_mask = set;
     panic_on(sigaction(4, &sig, NULL));
    panic_on(sigprocmask(0, &set, NULL));
    kill(0, 2);
    kill(0, 3);
    int ans = 0;
    for (int i = 0; i < 10000000; i++) {
        ans += i;
    }
    panic_on(sigprocmask(1, &set, NULL));
    sigemptyset(&set);
    sigset_t oldset;
    sigprocmask(0, &set, &oldset);
    debugf("the main has blocked 2:%d ; 3:%d ; 4:%d ; 5:%d\n",sigismember(&oldset, 2),sigismember(&oldset, 3),sigismember(&oldset, 4),sigismember(&oldset, 5));
    debugf("global = %d.\n", global);
    return 0;
}

