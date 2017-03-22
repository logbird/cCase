
#define HASH_FUNCS_MAX 3

typedef unsigned long long offset_t;

//获取bucket长度
size_t getBitmapSize();
//获取在bucket中的索引
unsigned int getBitmapIdx(unsigned int hash_value);
void setFilter(char *bitmap, char *buf, int len);
unsigned int check(char *bitmap, char *buf, int len);


/* bit map ops*/
void debugBitMap(unsigned char *bitmap);
int bitmapTestBit(unsigned char *bitmap, int pos);
void bitmapClearBit(unsigned char *bitmap, int pos);
void bitmapSetBit(unsigned char *bitmap, int pos);
