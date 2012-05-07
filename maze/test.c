#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <memory.h>


#include "stack.h"


#define MAP_SIZE 30
#define ROAD "  "
#define BARRIER "口" 
#define WAY "＊"

static STACK_NODE *stack;
static int map[][MAP_SIZE] = {
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,0,1},
	{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
	{1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,1,1,1,0,1,1,1,0,0,0,1},
	{1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,0,0,1,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,1,0,1,1,0,1,1,1,1},
	{1,0,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,0,1,0,1,1,1,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1},
	{1,0,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1},
	{1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1},
	{1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1},
	{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,0,1,1,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1}
};

void main()
{
	int delay = 0;

	signal(SIGINT, sigint_callback);	
	COORD_DATA *c, *nextWay, *lastWay;
	nextWay = malloc(sizeof(COORD_DATA));
	assert(nextWay != NULL);
	nextWay->x = 1;
	nextWay->y = 0;
	lastWay = malloc(sizeof(COORD_DATA));
	assert(lastWay != NULL);
	lastWay->x = -1;
	lastWay->y = -1;

	createStack();

	walk(nextWay, lastWay);

	while(TRUE)
	{
	    delay = 0;
		printMap();
		while(delay++ < 30000000);
		c = top();
		//Win
        /*
		if(c!= NULL)
		{
			printf("LENGTH:%d\n", c->y);
		}
        */
        if(c == NULL)
        {
            printf("You Loss!\nNo Way Out!\n");
            break;
        }
		if(c->y == MAP_SIZE - 1)
		{
            printf("You Win!\nMaze Over!\n");
			break;
		}
		//top
		nextWay->x = c->x;
		nextWay->y = c->y - 1;
		if(walk(nextWay, lastWay))
		{
			continue;
		}
		//bottom
		nextWay->x = c->x;
		nextWay->y = c->y + 1;
		if(walk(nextWay, lastWay))
		{
			continue;
		}
		//left
		nextWay->x = c->x - 1;
		nextWay->y = c->y;
		if(walk(nextWay, lastWay))
		{
			continue;
		}
		//right
		nextWay->x = c->x + 1;
		nextWay->y = c->y;
		if(walk(nextWay, lastWay))
		{
			continue;
		}
		map[c->y][c->x] = 3;
		lastWay->x = c->x;
		lastWay->y = c->y;
		pop();
	}
	free(lastWay);
	free(nextWay);
	destructStack();
}


void printMap()
{
	system("clear");
	int i = 0;
	int j = 0;
	for(i = 0; i < MAP_SIZE; i++)
	{
        /*
        if(i == 0)
        {
            printf(" 0");
            for(j = 0; j < MAP_SIZE; j++)
            {
                printf("%2d", j);
            }
            printf("\n");
        }
        printf("%2d", i);
        */
		for(j = 0; j < MAP_SIZE; j++)
		{
			if(map[i][j] == 1)
			{
				printf("%s", BARRIER);
			}else if(map[i][j] == 2)
			{
				printf("%s", WAY);
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


void createStack()
{
	stack = malloc(sizeof(STACK_NODE));
	assert(stack != NULL);
	stack->index = -1;
	stack->next = NULL;
	stack->coord = NULL;
}

void destructStack()
{
	while(top() != NULL)
	{
		pop();
	}
}

void push( COORD_DATA *c)
{
	STACK_NODE *ns = malloc(sizeof(STACK_NODE));
	assert(ns != NULL);
	COORD_DATA *nc = malloc(sizeof(COORD_DATA));
	assert(nc != NULL);
	nc->x = c->x;
	nc->y = c->y;
	ns->next = stack;
	ns->coord = nc;
	ns->index = stack->index+1;
	stack = ns;
}

int pop()
{
	STACK_NODE *ns;
	if(!isEmpty())
	{
		return FALSE;
	}
	ns = stack;
	stack = stack->next;
	free(ns->coord);
	free(ns);
	return TRUE;
}

COORD_DATA *top()
{
	if(!isEmpty())
	{
		return NULL;
	}
	return stack->coord;
}

int isEmpty()
{
	return (stack != NULL && stack->index >= 0 && stack->coord != NULL);
}

int checkStackExists( COORD_DATA *coord)
{
	STACK_NODE *tmp;
	COORD_DATA *c;
	if(!isEmpty())
	{
		return FALSE;
	}
	tmp = stack;
	while(tmp != NULL && tmp->index >= 0)
	{
		c = tmp->coord;
        //printf("[%d|%d]", c->x, c->y);
		if(c->x == coord->x && c->y == coord->y)
		{
			return TRUE;
		}
		tmp = tmp->next;
	}
    //printf("\n");
	return FALSE;
}

int walk(COORD_DATA *c, COORD_DATA *l)
{
	COORD_DATA *now;
    /*
    if(isEmpty())
    {
        now = top();
	    printf("%d|%d|%d|%d|%d|%d|now:|%d|%d\n", c->x, c->y, checkStackExists(c), map[c->y][c->x], l->x, l->y, now->x, now->y);
    }else
    {
        printf("%d|%d|%d|%d|%d|%d\n", c->x, c->y, checkStackExists(c), map[c->y][c->x], l->x, l->y);
    }
    */
	if(
		(l->x != c->x || l->y != c->y)
		&& c->x >= 0 
		&& c-> y >= 0 
		&& c->x < MAP_SIZE 
		&& c->y < MAP_SIZE 
		&& !checkStackExists(c)
		&& (map[c->y][c->x] == 0 || map[c->y][c->x] == 2)
	)
	{
		//设置上一步
		if(isEmpty())
		{
			now = top();
			l->x = now->x;
			l->y = now->y;
		}
		map[c->y][c->x] = 2;
		push(c);
		return TRUE;
	}
	//printf("R:1\n");
	return FALSE;
}




