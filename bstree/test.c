#include <stdio.h>
#include <stdlib.h>


#define TREE_TYPE int

typedef struct Tree{
    struct Tree *l;
    struct Tree *r;
    struct Tree *n;
    TREE_TYPE value;
}Tree;

int createTree(Tree **t);
int insert(Tree *t, TREE_TYPE value);
int NLReach(Tree *t, TREE_TYPE *(*callback)(Tree*));
int treeEmpty(Tree *t);




int main(int argc, char **argv)
{
    int n;
    for(n = 1; n <8 ;n++)
    {
        printf("%5d|%5d|%5d\n", n, n*2, n*2+1);
    }
    exit(EXIT_SUCCESS);
    TREE_TYPE treeData[] = {352, 632, 148, 574, 237, 965, 471, 546, 315, 478, 158, 115, 1, 3, 6, 8, 7};
    int i = 0;
    Tree *t;
    createTree(&t);
    for(i = 0; i < 17; i++)
    {
       insert(t, treeData[i]);
    }
}




int createTree(Tree **t)
{
    Tree *tmp = malloc(sizeof(Tree));
    if(tmp == NULL)
    {
        return 0;
    }
    tmp->n = NULL;
    tmp->l = NULL;
    tmp->r = NULL;
    tmp->value = 0;
    *t = tmp;
    return 1;
}
int insert(Tree *t, TREE_TYPE value)
{
    Tree *new, *tmp;
    tmp = t;
    while(tmp != NULL)
    {
        if(tmp->value >= value && tmp->r != NULL)
        {
            tmp = tmp->r;
        }else if(tmp->value < value && tmp->l != NULL)
        {
            tmp = tmp->l;
        }else
        {
            new = malloc(sizeof(Tree));
            if(new == NULL)
            {
                return 0;
            }
            new->value = value;
            new->n = tmp;
            if(tmp->value >= value)
            {
                tmp->r = tmp;
            }else
            {
                tmp->l = tmp;
            }
            return 1;
        }
    }
    return 0;
}
int treeEmpty(Tree *t)
{
    if(t->n == NULL && t->l == NULL && t->r == NULL)
    {
        return 1;
    }
    return 0;
}
int NLReach(Tree *t, TREE_TYPE *(*callback)(Tree*))
{
    //
    return 1;
}














