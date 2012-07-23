#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int BUF_SIZE = atoi(argv[1]);
    char row[BUF_SIZE];
    int len = 0;
    int flag = open("./f", O_RDWR);
    
    while( (len = read(flag, row, BUF_SIZE)) > 0)
    {
        printf("%d\n", len);
        write(STDOUT_FILENO, row, len);
    }
    close(flag);
    return 1;
}

