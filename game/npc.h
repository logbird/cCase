#ifndef G_NPC_H
#define G_NPC_H

#define WORDLEN 3
#define NAME_MAX 12
#define NPC_MAX 1000

#define FN_MAX 100
#define BN_MAX 151
#define GN_MAX 133

typedef unsigned int g_attr;

typedef struct struct_npc{
    g_attr id;
    //姓名
    char name[NAME_MAX];
    //修为
    g_attr level;
    //境界
    g_attr state;
    //善恶
    g_attr goodevil;
    //资质
    g_attr apt;
    //悟性
    g_attr savvy;
    //机缘
    g_attr lucky;
    //魅力
    g_attr glam;
    //神识
    g_attr sense;
    //速度
    g_attr speed;
    //身份 0 散修
    g_attr identity;
    //门派
    g_attr group;
    //家族
    g_attr family;
}NPC;

int get_a_name(char *name, g_tiny sex, g_size len, char *firstname);


#endif
