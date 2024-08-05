#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_BG_PROCESSES 10

enum mode {
    mode_foreground,
    mode_background
};

struct command {
    char argv[MAX_COMMAND_LENGTH];
    enum mode mode;
    pid_t pid;
};

struct command bg_processes[MAX_BG_PROCESSES];
int num_bg_processes = 0;

void execute_command(struct command* c) {
    if (c->argv[0] == '\0') {
        return;
    }
  
    pid_t pid = fork(); 
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(c->argv, c->argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        c->pid = pid;
        if (c->mode == mode_foreground) {
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        } else { 
            printf("Background PID running: %d, Command: %s\n\n", pid, c->argv);
        }
    }
}

void check_bg_processes() {
    int i;
    for (i = 0; i < num_bg_processes; ++i) {
        int wstatus;
        pid_t child_pid = waitpid(bg_processes[i].pid, &wstatus, WNOHANG);
        if (child_pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        } else if (child_pid > 0) {
            printf("Background PID finished running: %d, Command: %s\n\n", child_pid, bg_processes[i].argv);
            // Remove the finished background process from the list
            memmove(&bg_processes[i], &bg_processes[i + 1], (num_bg_processes - i - 1) * sizeof(struct command));
            num_bg_processes--;
        }
    }
}

int main() {
    while (1) {
        printf("Enter command: ");
        struct command c;
        fgets(c.argv, MAX_COMMAND_LENGTH, stdin);
        // Remove newline character
        c.argv[strcspn(c.argv, "\n")] = '\0';

        // Check if the command is to run in background
        if (c.argv[strlen(c.argv) - 1] == '&') {
            c.mode = mode_background;
            // Remove '&' from the command
            c.argv[strlen(c.argv) - 1] = '\0';
        } else {
            c.mode = mode_foreground;
        }

        if (strcmp(c.argv, "exit") == 0) {
            break;
        }

        execute_command(&c);

        // Check for finished background processes
        check_bg_processes();
    }

    return 0;
}
