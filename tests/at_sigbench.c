#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <err.h>

void sigusr1_sigaction(int signal, siginfo_t *si, void *arg) {

}

static void sigbench_sigusr1() {
	pid_t pid;

	struct sigaction sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sigusr1_sigaction;
	sa.sa_flags = SA_NODEFER;
	sigaction(SIGUSR1, &sa, NULL);

	pid = getpid();
	if (kill(pid, SIGUSR1) < 0)
		perror("SIGUSR1 is not possible");
}

static void sigbench_sigign() {
	pid_t pid;

	if (signal(SIGUSR1, SIG_IGN) < 0)
		perror("cannot set signal handler");

	pid = getpid();
	if (kill(pid, SIGUSR1) < 0)
		perror("SIGUSR1 is not possible");
}

int main(void)
{
	return 0;
}
