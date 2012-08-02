#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    while(*argv != NULL)
    {
        printf("%s\n", *argv);
        argv++;
    }
    printf("child GRPID:%d PID:%d\n", getpgrp(), getpid());

    return 1;
}
