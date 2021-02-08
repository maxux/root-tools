#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void diep(char *str) {
    perror(str);
    exit(EXIT_FAILURE);
}

//
// write content to a file
//
int set(char *filename, char *str) {
    int fd;
    ssize_t length = strlen(str);

    if((fd = open(filename, O_WRONLY)) < 0)
        diep("open");

    if(write(fd, str, length) != length)
        diep("write");

    close(fd);

    return 0;
}


//
// hooks
//
void pre_suspend() {
    printf("[+] setting power management to sync-mode\n");
    set("/sys/power/pm_async", "0");

    system("/usr/bin/nvidia-sleep.sh suspend");
}

void suspend() {
    set("/sys/power/state", "mem");
}

void post_suspend() {
    system("/usr/bin/nvidia-sleep.sh resume");
}


int main(void) {
    if(setuid(0))
        diep("setuid");

    printf("[+] preparing system\n");
    pre_suspend();

    printf("[+] ======================================\n");
    printf("[+] entering suspend-to-ram\n");
    suspend();
    printf("[+] ======================================\n");

    printf("[+] post-processing\n");
    post_suspend();

    return 0;
}
