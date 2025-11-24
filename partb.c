#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("ERROR: no arguments\n");
        return 1;
    }

    int start = (argc - 1) / 2;  
    int count = ((argc - 1) % 2 == 0) ? 1 : 2;  

    char* eargs[4];
    eargs[0] = "echo";
    eargs[1] = (char*)argv[start + 1];
    if (count == 2)
        eargs[2] = (char*)argv[start + 2];
    eargs[count + 1] = NULL;

 
    if (execv("/bin/echo", eargs) == -1) {
        perror("exec");
        return 1;
    }

    return 0;
}
