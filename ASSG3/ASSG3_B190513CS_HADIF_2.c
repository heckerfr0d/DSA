#include <stdio.h>
#include <stdlib.h>

typedef struct bNode{
    int key, h, count;
    struct bNode *left, *right;
} *node;

// typedef struct bst{
//     node root;
// } *tree;
typedef node tree;

node createNode(int);
tree insert(tree, node);
node subInsert(node, node);
node leftRotate(tree, node);
node rightRotate(tree, node);
int getBalance(tree, int);
int balance(node);
int isAVL(tree);
tree delete(tree, int);
node search(tree, int);
node min(node);
void print(tree);
int height(node);
int max(int, int);

int main()
{
    tree T = NULL;
    node x;
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i=0; i<n; i++)
    {
        scanf("%d", a+i);
        T = insert(T, createNode(a[i]));
    }
    print(T);
    return 0;
}

node createNode(int c)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = c;
    x->left = x->right = NULL;
    x->h = 0;
    x->count = 1;
    return x;
}


tree insert(tree T, node x)
{
    if(!T)
        return T = x;
    if(T->key==x->key)
    {
        T->count++;
        return T;
    }
    if(T->key>x->key)
    {
        T->left = insert(T->left, x);
        if(balance(T)==2)
        {
            if(T->left->key>x->key)
                return rightRotate(T, T);
            else
            {
                T->left = leftRotate(T, T->left);
                return rightRotate(T, T);
            }
        }
    }
    else
    {
        T->right = insert(T->right, x);
        if(balance(T)==-2)
        {
            if(T->right->key<x->key)
                return leftRotate(T, T);
            else
            {
                T->right = rightRotate(T, T->right);
                return leftRotate(T, T);
            }
        }
    }
    T->h = max(height(T->left), height(T->right)) + 1;
    return T;
}

node leftRotate(tree T, node x)
{
    node p = x->right;
    x->right = p->left;
    p->left = x;
    x->h = max(height(x->left), height(x->right)) + 1;
    p->h = max(height(p->left), height(p->right)) + 1;
    return p;
}

node rightRotate(tree T, node x)
{
    node p = x->left;
    x->left = p->right;
    p->right = x;
    x->h = max(height(x->left), height(x->right)) + 1;
    p->h = max(height(p->left), height(p->right)) + 1;
    return p;
}

int balance(node x)
{
    return x ? height(x->left)-height(x->right) : 10;
}

void print(tree T)
{
    if(T)
    {
        print(T->left);
        for(int i=0; i<T->count; i++)
            printf("%d ", T->key);
        print(T->right);
    }
}

int height(node x)
{
    return x ? x->h : -1;
}

int max(int a, int b)
{
    return a>b ? a : b;
}