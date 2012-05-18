#define TRUE 1
#define FALSE 0


typedef unsigned int COORD_TYPE ;
//坐标
typedef struct coord{
	COORD_TYPE x;
	COORD_TYPE y;
}COORD_DATA;
//堆栈节点
typedef struct stackNode{
	int index;
	COORD_DATA *coord;
	struct stackNode *next;
}STACK_NODE;
//设置方向
enum DIRECTION{
    up,down,left,right
};

void createStack();
void destructStack();
void push( COORD_DATA *c);
int pop();
COORD_DATA *top();
int isEmpty();
int checkStackExists( COORD_DATA *c);
//判断坐标是否可以行走，可以则前进
int walk(COORD_DATA *c, COORD_DATA *l);
//尝试像某个方向行走，如果不能行走 返回 FALSE
int checkNearByPos(COORD_DATA *next, COORD_DATA *c, COORD_DATA *last, enum DIRECTION dir);

void printMap();
void sigint_callback(int sig);

