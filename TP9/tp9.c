#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

#define N 100

volatile int n = 0;
unsigned long long k = 0;

/* Function to call upon signal reception */
void hello(int signo) {
    n++;
    k--;
    if (n % 10 == 0) {
        printf("Hello! n %d\n", n);
    }
}

int main(int argc, char **argv) {
    int signo = SIGALRM;
    unsigned long long ref = 0;

    struct sigaction s;
    s.sa_handler = hello;

    /* Install the signal handler */
    printf("Installing signal handler for signal %d\n", signo);

    int retval = sigaction(signo, &s, NULL);
    if (retval < 0) {
        perror("sigaction failed");
        abort();
    }

    printf("n: %d\n", n);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, signo);

    /* Mask the signal */
    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    /* Wait to receive signals */
    while (n < N) {
        ualarm(1000, 0); // Send SIGALRM every 1 ms
        printf("\n%d\n", n);

        /* Increment k while signals are masked */
        k++;
        ref++;
        
        /* Unblock the signal temporarily to handle it */
        sigsuspend(&oldmask);
    }

    /* Unmask the signal */
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    printf("Diff: %lld\n", ref - k);

    return EXIT_SUCCESS;
}
