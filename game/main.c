#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "npc.h"

int main(int argc, char *argv[])
{
    char name[NAME_MAX];
    srand(time(NULL));
    get_a_name(name, 1, 0, "李");
    return 1;
}
