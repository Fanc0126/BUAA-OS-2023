// User-level IPC library routines

#include <env.h>
#include <lib.h>
#include <mmu.h>

// Send val to whom.  This function keeps trying until
// it succeeds.  It should panic() on any error other than
// -E_IPC_NOT_RECV.
//
// Hint: use syscall_yield() to be CPU-friendly.
void ipc_send(u_int whom, u_int val, const void *srcva, u_int perm) {
	int r;
	while ((r = syscall_ipc_try_send(whom, val, srcva, perm)) == -E_IPC_NOT_RECV) {
		syscall_yield();
	}
	user_assert(r == 0);
}

// Receive a value.  Return the value and store the caller's envid
// in *whom.
//
// Hint: use env to discover the value and who sent it.
u_int ipc_recv(u_int *whom, void *dstva, u_int *perm) {
	int r = syscall_ipc_recv(dstva);
	if (r != 0) {
		user_panic("syscall_ipc_recv err: %d", r);
	}

	if (whom) {
		*whom = env->env_ipc_from;
	}

	if (perm) {
		*perm = env->env_ipc_perm;
	}

	return env->env_ipc_value;
}
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact){
	if(oldact!=NULL)
	memset(oldact,0,sizeof(struct sigaction));
	return syscall_sigaction(signum,act,oldact);
}
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
	if(oldset!=NULL)
	memset(oldset,0,sizeof(sigset_t));
	return syscall_sigprocmask(how,set,oldset);
}
void sigemptyset(sigset_t *set){
	memset(set->sig,0,sizeof(set->sig));
}
void sigfillset(sigset_t *set){
	memset(set->sig,255,sizeof(set->sig));
}
void sigaddset(sigset_t *set, int signum){
	if(signum>32){
		set->sig[1]=set->sig[1]|(1<<(signum%32-1));
	}else{
		set->sig[0]=set->sig[0]|(1<<(signum-1));
	}
}
void sigdelset(sigset_t *set, int signum){
	if(signum>32){
		set->sig[1]=set->sig[1]&(~(1<<(signum%32-1)));
	}else{
		set->sig[0]=set->sig[0]&(~(1<<(signum-1)));
	}
}
int sigismember(const sigset_t *set, int signum){
	if(signum>32){
		return (set->sig[1]&(1<<(signum%32-1)))==0?0:1;
	}else{
		return (set->sig[0]&(1<<(signum-1)))==0?0:1;
	}
}
int kill(u_int envid, int sig){
	return syscall_kill(envid,sig);
}
