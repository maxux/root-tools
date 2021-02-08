#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void diep(char *str) {
    perror(str);
    exit(EXIT_FAILURE);
}

int main(void) {
    if(setuid(0))
        diep("setuid");

    if(system("/usr/sbin/vlock-main all new nosysrq framebuffer") < 0)
        diep("system");

    return 0;
}
