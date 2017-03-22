#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boomfilter.h"
#include "hash_func.h"

//#define __DEBUG__ 1

//实际长度为 bitmap_bytes * 8
offset_t bitmap_bytes = 2048;

//处理hash函数的列表
unsigned int (*hash_funcs[HASH_FUNCS_MAX])(const unsigned char *buf, int len) = {
    djb_hash,
    murmur_hash,
    crc16
};

void main(int argc, char* argv) {
    unsigned int offset;
    char *bucket;

    bucket = calloc(bitmap_bytes, sizeof(char));

    setFilter(bucket, "logbird", 7);
    printf("test %d is %d\n", "abcd", check(bucket, "abcd", 4));
    printf("test %d is %d\n", "logbird", check(bucket, "logbird", 7));

#ifdef __DEBUG__
    debugBitMap(bucket);
#endif
    free(bucket);
}

unsigned int check(char *bitmap, char *buf, int len) {
    unsigned int i;
    unsigned int is = 1;
    unsigned int hash_value, idx;
    for (i = 0; i < HASH_FUNCS_MAX; i++) {
        hash_value = hash_funcs[i](buf, len);
        idx = getBitmapIdx(hash_value);
        is &= bitmapTestBit(bitmap, idx);
        if (is == 0)
            break;
    }
    return is;
}

void setFilter(char *bitmap, char *buf, int len) {
    unsigned int i;
    unsigned int hash_value, idx;
    for (i = 0; i < HASH_FUNCS_MAX; i++) {
        hash_value = hash_funcs[i](buf, len);
        idx = getBitmapIdx(hash_value);
        bitmapSetBit(bitmap, idx);
    }
}

unsigned int getBitmapIdx(unsigned int hash_value) {
    unsigned int idx = 0;
    idx = hash_value & (getBitmapSize() - 1);
#ifdef __DEBUG__
    printf("hash:%d\tidx:%d\n", hash_value, idx);
#endif
    return idx;
}

size_t getBitmapSize()
{
    return bitmap_bytes * 8;
}

/* Set the bit at position 'pos' in a bitmap. */
void bitmapSetBit(unsigned char *bitmap, int pos) {
    off_t byte = pos/8;
    int bit = pos&7;
    bitmap[byte] |= 1<<bit;
}

/* Clear the bit at position 'pos' in a bitmap. */
void bitmapClearBit(unsigned char *bitmap, int pos) {
    off_t byte = pos/8;
    int bit = pos&7;
    bitmap[byte] &= ~(1<<bit);
}

int bitmapTestBit(unsigned char *bitmap, int pos) {
    unsigned int byte = pos/8;
    int bit = pos&7;
    return (bitmap[byte] & (1<<bit)) != 0;
}

void debugBitMap(unsigned char *bitmap) {
    unsigned int i, j;
    for (i = 1; i <= bitmap_bytes; i++) {
        printf("%04d\t", i);
        for ( j = 8; j >= 1; j--) {
            printf("%d", bitmapTestBit(bitmap, (i-1)*8 + j - 1));
        }
        printf("\n");
    }
}
