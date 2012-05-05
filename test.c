#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "stack.h"

#define TRUE 1
#define FALSE 0

#define MAP_SIZE 10
#define ROAD "  "
#define BARRIER "口" 

void printMap(int map[][10]);
void sigint_callback(int sig);


void main()
{
	int map[][MAP_SIZE] = {
		{1,0,1,1,1,1,1,1,1,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,1,1,0,1},
		{1,0,1,1,1,0,1,0,0,1},
		{1,0,0,0,1,0,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,0,1,0,1},
		{1,0,1,1,0,1,1,1,0,1},
		{1,0,1,1,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1},
	};

	signal(SIGINT, sigint_callback);

	while(TRUE)
	{
		printMap(map);
		sleep(1);
	}
}

void printMap(int map[][10])
{
	system("clear");
	int i = 0;
	int j = 0;
	for(i = 0; i < MAP_SIZE; i++)
	{
		for(j = 0; j < MAP_SIZE; j++)
		{
			if(map[i][j] == 1)
			{
				printf("%s", BARRIER);
			}else
			{
				printf("%s", ROAD);
			}
		}
		printf("\n");
	}
}

void sigint_callback(int sig)
{
	printf("\nMaze Over!\n");
	exit(EXIT_SUCCESS);

}
