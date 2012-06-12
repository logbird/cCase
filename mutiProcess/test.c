#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>



void waitCp(int flg);

int main(int argc, char **argv)
{
    pid_t pid;
    signal(SIGCHLD, waitCp);
    pid = vfork();
    printf("%d Starting...\n", pid);
    if(pid < 0)
    {
        printf("Err\n");
    }else if(pid == 0)
    {
        execl("/home/logbird/c/mutiProcess/cp", "/home/logbird/c/mutiProcess/cp", NULL);
        printf("Child Process Back!\n");
    }else
    {
        printf("Parent UID:%d GID:%d EUID:%d EGID:%d GRPID:%d PID:%d\n", getuid(), getgid(), geteuid(), getegid(), getpgrp(), getpid());
    }
    exit(EXIT_SUCCESS);
}

void waitCp(int flg)
{
    int i = 0;
    printf("signal handdle,wait for 20s!\n");
    wait(&i);
    printf("wait for child process!\n", i);
}
