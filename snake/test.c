#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <memory.h>


#include "stack.h"


#define MAP_SIZE 30
#define ROAD "  "
#define BARRIER "口" 
#define SNAKE "＊"

static int mapInit[][MAP_SIZE] = {
    #include "map.h"
};

static int map[][MAP_SIZE] = {
    #include "map.h"
};

int main(int argc, char** argv)
{
	int delay = 0;
    //异常退出信号
	signal(SIGINT, sigint_callback);

    enum DIRECTION dir;
    SNAKE_HEAD *s = createSnake();
    snakeGrowUp(s, 5);
    while(1)
    {
        dir = findRoad(s);
        walkSnake(s, dir);
        printMap();
		while(delay++ < 30000000);
    }
    snakeDie(s);
    return EXIT_SUCCESS;
}

size_t snakeTotal = 0;

void printMap()
{
	system("clear");
	int i = 0;
	int j = 0;
	for(i = 0; i < MAP_SIZE; i++)
	{
		for(j = 0; j < MAP_SIZE; j++)
		{
            switch(map[i][j])
			{
                case 1:
				    printf("%s", BARRIER);
                break;
                case 2:
                	printf("%s", SNAKE);
                break;
                default:
                    printf("%s", ROAD);
                break;
			}
            //初始化地图
            map[i][j] = mapInit[i][j];
		}
		printf("\n");
	}
}

void sigint_callback(int sig)
{
	printf("\nMaze Over!\n");
	exit(EXIT_SUCCESS);
}

//创建蛇
SNAKE_HEAD * createSnake()
{
    SNAKE_HEAD *s;
    COORD_DATA *coord = calloc(1, sizeof(SNAKE_HEAD));
    //默认出生地 为 (1,1)
    coord->x = 1;
    coord->y = 1;
    s = calloc(1, sizeof(SNAKE_HEAD));
    s->id = getSnakeTotal()+1;
    s->dir = right;
    s->length = 0;
    s->coord = coord;
    s->next = NULL; 
    s->end = NULL; 
    snakeTotal += 1;
    return s;
}
//蛇长大
void snakeGrowUp(SNAKE_HEAD *s, size_t length)
{
    SNAKE_NODE *sn, *body;
    COORD_DATA *coord;
    while(length-- > 0)
    {
        //蛇尾
        sn = s->end;
        body = calloc(1, sizeof(SNAKE_NODE)); 
        coord = calloc(1, sizeof(COORD_DATA));
        body->coord = coord;
        body->next = NULL;
        if(sn != NULL)
        {
            sn->next = body;
        }else
        {
            s->next = body;
        }
        //新蛇尾
        s->end = body;
    }
    s->length += length;
}
//蛇行走
int walkSnake(SNAKE_HEAD *s, enum DIRECTION dir)
{
    SNAKE_NODE *sn = s->next;
    COORD_DATA *coord = calloc(1, sizeof(COORD_DATA));
    COORD_DATA *tmp = calloc(1, sizeof(COORD_DATA));
    coord->x = s->coord->x;
    coord->y = s->coord->y;

    switch(dir)
    {
        case up:
		    s->coord->y -= 1;
        break;
        case down:
		    s->coord->y += 1;
        break;
        case left:
            s->coord->x -= 1;
        break;
        case right:
            s->coord->x += 1;
        break;
        default:
            return 0;
        break;
    } 
    s->dir = dir;
    while(sn != NULL)
    {
       tmp->x = sn->coord->x;
       tmp->y = sn->coord->y;
       sn->coord->x = coord->x;
       sn->coord->y = coord->y;
       coord->x = sn->coord->x;
       coord->y = sn->coord->y;
    }
    free(tmp);
    free(coord);
    return 1;
}
//获取蛇数目
size_t getSnakeTotal()
{
    return snakeTotal;
}
//蛇死亡
void snakeDie(SNAKE_HEAD *s)
{
    SNAKE_NODE *tmp,*sn = s->next;
    while(sn != NULL)
    {
        free(sn->coord);
        tmp = sn->next;
        free(sn);
        sn = tmp;
    }
    free(s->coord);
    free(s);
    snakeTotal -= 1;
}
//选择方向
enum DIRECTION findRoad(SNAKE_HEAD *s)
{
    COORD_DATA *coord = s->coord;
    switch(s->dir)
    {
        case up:
            if(isCross(coord->y-1, coord->x))
            {
                return up;
            }
        case down:
            if(isCross(coord->y+1, coord->x))
            {
                return down;
            }
        case left:
            if(isCross(coord->y, coord->x-1))
            {
                return left;
            }
        case right:
            if(isCross(coord->y, coord->x+1))
            {
                return right;
            }
        break;
    }
}
//显示蛇
void displaySnake(SNAKE_HEAD *s);
//判断前方是否可以行走
int isCross(int x, int y)
{
    if(x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE || map[y][x] == 1 || map[y][x] == 2)
    {
        return 0;
    }
    return 1;
}

























