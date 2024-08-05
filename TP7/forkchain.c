#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    printf("I am process %d. My PPID: %d\n", getpid(), getppid());
    pid_t ret_val = fork();
    if (ret_val == 0) {
        printf("I’m the child process. PID = %d, PPID = %d\n", getpid(), getppid());
        execlp("ps", "ps", "-l", NULL);
        printf("This is printed only if execlp fails\n");
        abort();
    } else if (ret_val > 0) {
        printf("I’m the parent process. PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(1);
    }
    return EXIT_SUCCESS;
}
