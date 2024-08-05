#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void display_proc() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("PID %d - PPID %d\n", pid, ppid);
}

int main() {
    printf("Test\n");

    display_proc();

    pid_t p2 = fork();

    if (p2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (p2 == 0) {
        sleep(1);
        display_proc();

        pid_t p3 = fork();

        if (p3 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (p3 == 0) {
            sleep(2);
            display_proc();

            pid_t p4 = fork();

            if (p4 == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (p4 == 0) {
                display_proc();
                execlp("ps", "ps", "-f", NULL);
                perror("execlp");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
            }
        } else {
            wait(NULL);
        }
    } else {
        wait(NULL); 
    }

    return EXIT_SUCCESS;
}
