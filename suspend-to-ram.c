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
    printf("[+] unloading radeon\n");
    if(system("/sbin/rmmod radeon") < 0)
        diep("system");

    printf("[+] setting power management to sync-mode\n");
    set("/sys/power/pm_async", "0");
}

void suspend() {
    set("/sys/power/state", "mem");
}

void post_suspend() {
    printf("[+] loading radeon\n");
    if(system("/sbin/modprobe radeon") < 0)
        diep("system");
}


int main(void) {
    if(setuid(0))
        diep("setuid");

    printf("[+] preparing system\n");
    pre_suspend();

    printf("[+] entering suspend-to-ram\n");
    printf("[+] ======================================\n");
    suspend();
    printf("[+] ======================================\n");

    printf("[+] post-processing\n");
    post_suspend();

    return 0;
}
