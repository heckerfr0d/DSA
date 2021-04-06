#include <stdio.h>
#include <stdlib.h>

typedef struct rbNode{
    int key;
    char color;
    struct rbNode *left, *right;
} * node;

typedef struct rbt{
    node root;
} *tree;

node createNode(int);
tree insert(tree, int);
node rbInsert(node, node);
node subInsert(node, node);
node leftRotate(node);
node rightRotate(node);
void print(node);

node nil;

int main()
{
    tree T = (tree)malloc(sizeof(struct rbt));
    nil = (node)malloc(sizeof(struct rbNode));
    nil->color = 'B';
    nil->key = -1;
    nil->left = nil->right = NULL;
    T->root = nil;
    int x;
    while(scanf("%d", &x))
    {
        T = insert(T, x);
        print(T->root);
        printf("\n");
    }
    return 0;
}

node createNode(int c)
{
    node x = (node)malloc(sizeof(struct rbNode));
    x->key = c;
    x->left = nil;
    x->right = nil;
    x->color = 'R';
    return x;
}


tree insert(tree T, int k)
{
    node x = createNode(k);
    T->root = rbInsert(T->root, x);
    if(T->root->color=='R')
        T->root->color = 'B';
    return T;
}

node rbInsert(node t, node x)
{
    if(t==nil)
        return t = x;
    if(t->key<x->key)
    {
        t->right = rbInsert(t->right, x);
        if(t->right->color=='R' && t->right->left->color+t->right->right->color!=132)
        {
            if(t->left->color=='R')
            {
                t->left->color = t->right->color = 'B';
                t->color = 'R';
                return t;
            }
            if(t->right->left->color=='R')
                t->right = rightRotate(t->right);
            t = leftRotate(t);
            t->left->color = 'R';
            t->color = 'B';
        }
    }
    else if(t->key>x->key)
    {
        t->left = rbInsert(t->left, x);
        if(t->left->color=='R' && t->left->left->color+t->left->right->color!=132)
        {
            if(t->right->color=='R')
            {
                t->left->color = t->right->color = 'B';
                t->color = 'R';
                return t;
            }
            if(t->left->right->color=='R')
                t->left = leftRotate(t->left);
            t = rightRotate(t);
            t->right->color = 'R';
            t->color = 'B';
        }
    }
    return t;
}

node leftRotate(node x)
{
    node p = x->right;
    x->right = p->left;
    p->left = x;
    return p;
}

node rightRotate(node x)
{
    node p = x->left;
    x->left = p->right;
    p->right = x;
    return p;
}

void print(node T)
{
    printf("( ");
    if(T!=nil)
    {
        printf("%d %c ", T->key, T->color);
        print(T->left);
        print(T->right);
    }
    printf(") ");
}
