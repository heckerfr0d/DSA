#include <stdio.h>
#include <stdlib.h>

typedef struct bNode{
    int key, h;
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
    char c;
    do
    {
        scanf("%c", &c);
        int k;
        switch(c)
        {
        case 'i':
            scanf("%d", &k);
            T = insert(T, createNode(k));
            break;
        case 'd':
            scanf("%d", &k);
            T = delete(T, k);
            break;
        case 's':
            scanf("%d", &k);
            search(T, k) ? printf("TRUE\n") : printf("FALSE\n");
            break;
        case 'b':
            scanf("%d", &k);
            k = getBalance(T, k);
            k==10  ? printf("FALSE\n") : printf("%d\n", k);
            break;
        case 'p':
            print(T);
            printf("\n");
            break;
        }
    } while (c != 'e');
    return 0;
}

node createNode(int c)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = c;
    x->left = NULL;
    x->right = NULL;
    x->h = 0;
    return x;
}


tree insert(tree T, node x)
{
    if(!T)
        return T = x;
    if(T->key==x->key)
        return T;
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

int getBalance(tree T, int k)
{
    node x = search(T, k);
    return balance(x);
}

tree delete(tree T, int k)
{
    if(!T)
        return T;
    if(T->key==k)
    {
        printf("%d\n", T->key);
        if(T->left && T->right)
        {
            node y = min(T->right);
            T->key = y->key;
            T->right = delete(T->right, y->key);
        }
        else
        {
            node y = T->left ? T->left : T->right;
            if(y)
            {
                *T = *y;
                free(y);
                return T;
            }
            free(T);
            return NULL;
        }
    }
    else if(T->key>k)
        T->left = delete(T->left, k);
    else
        T->right = delete(T->right, k);
    T->h = max(height(T->left), height(T->right)) + 1;
    if(balance(T)==2)
    {
        if(balance(T->left)>=0)
            return rightRotate(T, T);
        else
        {
            T->left = leftRotate(T, T->left);
            return rightRotate(T, T);
        }
    }
    if(balance(T)==-2)
    {
        if(balance(T->right)<=0)
            return leftRotate(T, T);
        else
        {
            T->right = rightRotate(T, T->right);
            return leftRotate(T, T);
        }
    }
    return T;
}

node search(tree T, int k)
{
    node t = T;
    while(t && t->key!=k)
    {
        if(k>t->key)
            t = t->right;
        else
            t = t->left;
    }
    return t;
}

node min(node x)
{
    node t = x;
    while(t->left)
        t = t->left;
    return t;
}

void print(tree T)
{
    printf("( ");
    if(T)
    {
        printf("%d ", T->key);
        print(T->left);
        print(T->right);
    }
    printf(") ");
}

int height(node x)
{
    return x ? x->h : -1;
}

int max(int a, int b)
{
    return a>b ? a : b;
}