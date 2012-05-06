#define TRUE 1
#define FALSE 0


typedef unsigned int COORD_TYPE ;

typedef struct coord{
	COORD_TYPE x;
	COORD_TYPE y;
}COORD_DATA;

typedef struct stackNode{
	int index;
	COORD_DATA *coord;
	struct stackNode *next;
}STACK_NODE;

void createStack();
void destructStack();
void push( COORD_DATA *c);
int pop();
COORD_DATA *top();
int isEmpty();
int checkStackExists( COORD_DATA *c);
int walk(COORD_DATA *c, COORD_DATA *l);

void printMap();
void sigint_callback(int sig);

