#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <memory.h>




#define MAP_SIZE 30
#define FOOD_SIZE 2
#define ROAD "  "
#define BARRIER "口" 
#define SNAKE "＊"
#define FOOD "￥"

#include "stack.h"

static int mapInit[][MAP_SIZE] = {
    #include "map.h"
};

static int map[][MAP_SIZE] = {
    #include "map.h"
};

size_t snakeTotal = 0;
size_t foodTotal = 0;

int main(int argc, char** argv)
{
	int delay = 0;
    //异常退出信号
	signal(SIGINT, sigint_callback);
	srand((unsigned int)time(NULL));

    enum DIRECTION dir;
    SNAKE_HEAD *s = createSnake();
    snakeGrowUp(s, 5);
    while(1)
    {
		delay = 0;
		while(delay++ < 30000000);
		setFood();
        dir = findRoad(s);
        walkSnake(s, dir);
		displaySnake(s);
        printMap();
    }
    snakeDie(s);
    return EXIT_SUCCESS;
}



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
				case 3:
					printf("%s", FOOD);
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
	    coord->x = tmp->x;
	    coord->y = tmp->y;
	    sn = sn->next;
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
            if(isCross(coord->y-1, coord->x, s))
            {
                return up;
            }
        case down:
            if(isCross(coord->y+1, coord->x, s))
            {
                return down;
            }
        case left:
            if(isCross(coord->y, coord->x-1, s))
            {
                return left;
            }
        case right:
            if(isCross(coord->y, coord->x+1, s))
            {
                return right;
            }
        break;
    }
	if(isCross(coord->y-1, coord->x, s))
	{
		return up;
	}
	if(isCross(coord->y+1, coord->x, s))
	{
		return down;
	}
	if(isCross(coord->y, coord->x-1, s))
	{
		return left;
	}
	if(isCross(coord->y, coord->x+1, s))
	{
		return right;
	}
	printf("无路可走\n");
	exit(EXIT_FAILURE);
}
//显示蛇
void displaySnake(SNAKE_HEAD *s)
{
	int i = 0;
	SNAKE_NODE *sn = s->next;
	//设置蛇头
	map[s->coord->y][s->coord->x] = 2;
	while(sn != NULL)
	{
		if(!map[sn->coord->y][sn->coord->x])
		{
			map[sn->coord->y][sn->coord->x] = 2;
		}
		sn = sn->next;
	}
	for(i = 0; i < foodTotal; i++)
	{
		map[food[i]->y][food[i]->x] = 3;
	}
}
//判断前方是否可以行走
int isCross(int y, int x, SNAKE_HEAD *s)
{
	SNAKE_NODE *sn = s->next;
	//判断坐标处是否有蛇存在
	while(sn != NULL)
	{
		if(sn->coord->x == x && sn->coord->y == y)
		{
			return 0;
		}
		sn = sn->next;
	}
    if(x < 1 || y < 1 || x >= MAP_SIZE || y >= MAP_SIZE || (map[y][x] != 0 && map[y][x] != 3))
    {
        return 0;
    }
    return 1;
}

//放置食物
void setFood()
{
	int x, y;
	if(foodTotal < FOOD_SIZE)
	{
		do
		{
			x = rand() % (MAP_SIZE - 1);
			y = rand() % (MAP_SIZE - 1);
			printf("%d|%d\n", x, y);
		}while(map[y][x] != 0);
		//放置食物
		food[foodTotal] = calloc(1, sizeof(COORD_DATA));
		food[foodTotal]->x = x;
		food[foodTotal]->y = y;
		foodTotal++;
	}
}
























