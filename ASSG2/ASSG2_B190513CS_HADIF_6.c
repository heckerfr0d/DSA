#include <stdio.h>
#include <stdlib.h>

typedef struct bNode{
    int key;
    struct bNode *left, *right, *p;
} *node;

typedef struct bst{
    node root;
} *tree;

node createNode(int);
void insert(tree, node);
node search(tree, int);
int maxPath(tree, int, int);
int tmax(node, int);

int main()
{
    tree T = (tree)malloc(sizeof(tree));
    T->root = NULL;
    int a, b;
    char c;
    do
    {
        scanf("%d%c", &a, &c);
        insert(T, createNode(a));
    } while (c!='\n');
    scanf("%d%d", &a, &b);
    printf("%d\n", maxPath(T, a, b));
    return 0;
}

int tmax(node x, int a)
{
    node t = x;
    int max = t->key;
    while(t->key!=a)
    {
        if(t->key<a)
            t = t->right;
        else if(t->key>a)
            t = t->left;
        max = (t->key>max && t->key!=a) ? t->key : max;
    }
    return max;
}

int maxPath(tree T, int a, int b)
{
    node t = T->root;
    int mx = 0;
    while((a<t->key && b<t->key) || (a>t->key && b>t->key))
    {
        if(a<t->key && b<t->key)
            t = t->left;
        else if(a>t->key && b>t->key)
            t = t->right;
    }
    if(t->key==a || t->key==b)
    {
        if((t->left && (t->left->key==a || t->left->key==b)) || (t->right && (t->right->key==a || t->right->key==b)))
            return -1000001;
        if(a<t->key || b<t->key)
            mx = a<b ? tmax(t->left, a) : tmax(t->left, b);
        else if(a>t->key || b>t->key)
            mx = a>b ? tmax(t->right, a) : tmax(t->right, b);
    }
    return mx ? mx : (a>b ? tmax(t, a) : tmax(t, b));
}

node createNode(int c)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = c;
    x->left = NULL;
    x->right = NULL;
    x->p = NULL;
    return x;
}

void insert(tree T, node x)
{
    node y = NULL, t = T->root;
    while(t)
    {
        y = t;
        if(x->key>t->key)
            t = t->right;
        else
            t = t->left;
    }
    if(!y)
        T->root = x;
    else if(x->key<y->key)
        y->left = x;
    else
        y->right = x;
    x->p = y;
}

node search(tree T, int k)
{
    node t = T->root;
    while(t && t->key!=k)
    {
        if(k>t->key)
            t = t->right;
        else
            t = t->left;
    }
    return t;
}
