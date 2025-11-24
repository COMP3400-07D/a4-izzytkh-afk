#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("ERROR: no arguments\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // child
        char* gargs[] = {"grep", "-s", "-q", (char*)argv[1], (char*)argv[2], NULL};
        execv("/usr/bin/grep", gargs);
        perror("execv");
        exit(2);
    }

    // parent
    int status;
    wait(&status);

    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) {
            printf("FOUND: %s\n", argv[1]);
            return 0;
        } else if (code == 1) {
            printf("NOT FOUND: %s\n", argv[1]);
            return 0;
        } else if (code == 2) {
            printf("ERROR: %s doesn't exist\n", argv[2]);
            return 2;
        } else {
            printf("ERROR: Unknown grep exit code %d\n", code);
            return 2;
        }
    }

    return 0;
}
