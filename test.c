#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int f = open("b", O_CREAT | O_RDONLY | O_WRONLY);
    write(f, "logbird000", 10);
    lseek(f, 10, SEEK_SET);
    write(f, "\nlogbird000", 10);
    lseek(f, 100, SEEK_END);
    write(f, "\nend", 10);
    close(f);
    return 1;
}

