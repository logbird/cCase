#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>



int main(int argc, char** argv)
{
    int i = 0;
    struct stat buf;
    char *ptr;

    if(argc < 2)
    {
        printf("parameter count error!\n");
        return -1;
    }
    for(i = 1; i < argc; i++)
    {
        if(lstat(argv[i], &buf) < 0)
        {
            printf(" open %s failed!\n", argv[i]);
            return -1;
        }
        if(S_ISREG(buf.st_mode))
        {
            ptr = "regular file";
        }else if(S_ISDIR(buf.st_mode))
        {
            ptr = "directory file";
        }else if(S_ISCHR(buf.st_mode))
        {
            ptr = "character special file";
        }else if(S_ISBLK(buf.st_mode))
        {
            ptr = "block special file";
        }else if(S_ISFIFO(buf.st_mode))
        {
            ptr = "FIFO file";
        }else if(S_ISLNK(buf.st_mode))
        {
            ptr = "symbolic link";
        }else if(S_ISSOCK(buf.st_mode))
        {
            ptr = "socket";
        }else if(S_TYPEISMQ(&buf))
        {
            ptr = "MQ file";
        }else if(S_TYPEISSEM(&buf))
        {
            ptr = "SEM file";
        }else if(S_TYPEISSHM(&buf))
        {
            ptr = "SHM file";
        }else
        {
            ptr = " unknow mode";
        }
        printf("'%s' is a %s\n", argv[i], ptr);
    }
    return 1;
}

