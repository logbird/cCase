#define SNAKE_MAX 50


typedef int COORD_TYPE ;

//坐标
typedef struct coord{
	COORD_TYPE x;
	COORD_TYPE y;
}COORD_DATA;

//设置方向
typedef enum DIRECTION{
    up,down,left,right,none
} DIRECTION;

//蛇
typedef struct snakeNode{
	COORD_DATA *coord;
	struct snakeNode *next;
}SNAKE_NODE;
//蛇头
typedef struct snakeHead{
	size_t id;
    size_t length;
    DIRECTION dir;
	COORD_DATA *coord;
	SNAKE_NODE *next;
    SNAKE_NODE *end;
}SNAKE_HEAD;
//食物链
COORD_DATA *food[FOOD_SIZE];


void printMap();
void sigint_callback(int sig);


//创建蛇
SNAKE_HEAD *createSnake(int x, int y);
//蛇长大
void snakeGrowUp(SNAKE_HEAD *s, size_t length); 
//蛇行走
int walkSnake(SNAKE_HEAD *s, DIRECTION dir);
//获取蛇数目
size_t getSnakeTotal();
//蛇死亡
void snakeDie(SNAKE_HEAD *s);

//选择方向
DIRECTION findRoad(SNAKE_HEAD *s);
//枚举行进路径
DIRECTION enumRoad(COORD_DATA *coord, DIRECTION flg);
//判断前方是否可以行走
int isCross(int x, int y);
//放置食物
void setFood();















