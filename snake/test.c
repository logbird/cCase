#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <memory.h>




#define MAP_SIZE 30
#define FOOD_SIZE 5
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

int snakeTotal = 0;

int main(int argc, char** argv)
{
	int delay = 0, sindex = 0, i = 0;
    //异常退出信号
	signal(SIGINT, sigint_callback);
	srand((unsigned int)time(NULL));

    DIRECTION dir;
    SNAKE_HEAD *snake[3];
    snake[0] = createSnake(1, 1);
    snake[1] = createSnake(1, 28);
    snake[2] = createSnake(28, 1);

    snakeGrowUp(snake[0], 5);
    snakeGrowUp(snake[1], 5);
    snakeGrowUp(snake[2], 5);
    while(1)
    {
        delay = 0;
		while(delay++ < 30000000);
		setFood();
        for(sindex = 0; sindex<3; sindex++)
        {
            if(snake[sindex] == NULL)continue;
            if(getSnakeTotal() <= 1)
            {
                printf("%d胜利\n", snake[sindex]->id);
				snakeDie(snake[sindex]);
				for(i = 0; i< FOOD_SIZE; i++)
				{
					if(food[i]!=NULL)free(food[i]);
				}
                exit(EXIT_SUCCESS);
            }
            dir = findRoad(snake[sindex]);
            if(dir == none)
            {
                snakeDie(snake[sindex]);
                snake[sindex] = NULL;
                continue;
            }
            
            walkSnake(snake[sindex], dir);
        }
        printMap();
    }
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
            //map[i][j] = mapInit[i][j];
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
SNAKE_HEAD * createSnake(int x, int y)
{
    SNAKE_HEAD *s;
    COORD_DATA *coord = calloc(1, sizeof(SNAKE_HEAD));
    //默认出生地 为 (1,1)
    coord->x = x;
    coord->y = y;
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
int walkSnake(SNAKE_HEAD *s, DIRECTION dir)
{
    SNAKE_NODE *sn = s->next;
    COORD_DATA *coord = calloc(1, sizeof(COORD_DATA));
    COORD_DATA *tmp = calloc(1, sizeof(COORD_DATA));
    coord->x = s->coord->x;
    coord->y = s->coord->y;
    int i = 0;
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
    
    for(i = 0; i < FOOD_SIZE; i++)
    {
        if(food[i] != NULL && food[i]->x == s->coord->x && food[i]->y == s->coord->y)
        {
            //吃到食物
            snakeGrowUp(s, 1);
            free(food[i]); 
            food[i] = NULL;
        }
    }
    while(sn != NULL)
    {
        if(map[sn->coord->y][sn->coord->x] != 1)
        {
            map[sn->coord->y][sn->coord->x] = 0;
        }
        if(!map[coord->y][coord->x])
        {
            map[coord->y][coord->x] = 2;
        }
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
    map[s->coord->y][s->coord->x] = 0;
    while(sn != NULL)
    {
        map[sn->coord->y][sn->coord->x] = 0;
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
DIRECTION findRoad(SNAKE_HEAD *s)
{
    COORD_DATA *coord = s->coord;
    int i, index = 0;
    unsigned int distance = 0;
    //找到最近的食物 然后前进
    for(i = 0; i < FOOD_SIZE; i++)
    {
        if(food[i] != NULL && (distance == 0 || distance > (abs(food[i]->y-coord->y) + abs(food[i]->x-coord->x))))
        {
            distance = (abs(food[i]->y-coord->y) + abs(food[i]->x-coord->x)); 
            index = i;
        }
    }
	//向最近的食物前进
    if(food[index] != NULL)
    {
        //up
        if((food[index]->y < coord->y) && isCross(coord->y-1, coord->x))
            return up;
        //down
        if((food[index]->y > coord->y) && isCross(coord->y+1, coord->x))
            return down;
        //left
        if((food[index]->x < coord->x) && isCross(coord->y, coord->x-1))
            return left;
        //right
        if((food[index]->x > coord->x) && isCross(coord->y, coord->x+1))
            return right;
    }
	//没有食物 自动行走
	return enumRoad(coord, s->dir);
}
//枚举行进路径 改成枚举
DIRECTION enumRoad(COORD_DATA *coord, DIRECTION flg)
{
    int index = 0;
    if((flg == none || flg == up) && isCross(coord->y-1, coord->x))
    {
    	return up;
    }
	if((flg == none || flg == down) && isCross(coord->y+1, coord->x))
    {
    	return down;
    }
	if((flg == none || flg == left) && isCross(coord->y, coord->x-1))
    {
    	return left;
    }
	if((flg == none || flg == right) && isCross(coord->y, coord->x+1))
    {
    	return right;
    }
    if(flg == none)
	{
		return none;
	}else
	{
		return enumRoad(coord, none);
	}
}
//判断前方是否可以行走
int isCross(int y, int x)
{
    if(x < 1 || y < 1 || x >= MAP_SIZE || y >= MAP_SIZE || (map[y][x] != 0 && map[y][x] != 3))
    {
        return 0;
    }
    return 1;
}

//放置食物
void setFood()
{
	int x, y, i;
    for(i = 0; i < FOOD_SIZE; i++)
	{
        if(food[i] != NULL)
        {
		    map[food[i]->y][food[i]->x] = 3;
        }else
        {
            do
            {
                x = rand() % (MAP_SIZE - 1);
                y = rand() % (MAP_SIZE - 1);
            }while(map[y][x] != 0);
            //放置食物
            food[i] = calloc(1, sizeof(COORD_DATA));
            food[i]->x = x;
            food[i]->y = y;
        }
	}
}
























