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
void transplant(tree, node, node);
int delete(tree, node);
node search(tree, int);
int level(tree, int);
node min(node);
int minVal(tree);
node max(node);
int maxVal(tree);
node predecessor(tree, int);
node successor(tree, int);
void inOrder(tree);
void preOrder(tree);
void postOrder(tree);

int main()
{
    tree T = (tree)malloc(sizeof(tree));
    node x;
    T->root = NULL;
    char c;
    do
    {
        scanf("%c", &c);
        int k;
        switch(c)
        {
        case 'a':
            scanf("%d", &k);
            insert(T, createNode(k));
            break;
        case 'd':
            scanf("%d", &k);
            printf("%d\n", delete(T, search(T, k)));
            break;
        case 's':
            scanf("%d", &k);
            search(T, k) ? printf("1\n") : printf("-1\n");
            break;
        case 'l':
            scanf("%d", &k);
            printf("%d\n", level(T, k));
            break;
        case 'm':
            printf("%d\n", minVal(T));
            break;
        case 'x':
            printf("%d\n", maxVal(T));
            break;
        case 'r':
            scanf("%d", &k);
            x = predecessor(T, k);
            x ? printf("%d\n", x->key) : printf("-1\n");
            break;
        case 'u':
            scanf("%d", &k);
            x = successor(T, k);
            x ? printf("%d\n", x->key) : printf("-1\n");
            break;
        case 'i':
            inOrder(T);
            printf("\n");
            break;
        case 'p':
            preOrder(T);
            printf("\n");
            break;
        case 't':
            postOrder(T);
            printf("\n");
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

void transplant(tree T, node x, node y)
{
    if(!x->p)
        T->root = y;
    else if(x==x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    if(y)
        y->p = x->p;
}

int delete(tree T, node x)
{
    if(!x)
        return -1;
    if(!x->left)
        transplant(T, x, x->right);
    else if(!x->right)
        transplant(T, x, x->left);
    else
    {
        node y = min(x->right);
        if(y->p!=x)
        {
            transplant(T, y, y->right);
            y->right = x->right;
            y->right->p = y;
        }
        transplant(T, x, y);
        y->left = x->left;
        y->left->p = y;
    }
    int k = x->key;
    free(x);
    return k;
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

int getlevel(node x, int k, int cl)
{
    if(!x)
        return -1;
    if(x->key==k)
        return cl;
    int pl = getlevel(x->left, k, cl+1);
    if(pl!=-1)
        return pl;
    return getlevel(x->right, k, cl+1);
}

int level(tree T, int k)
{
    return getlevel(T->root, k, 1);
}

node min(node x)
{
    node t = x;
    while(t->left)
        t = t->left;
    return t;
}

int minVal(tree T)
{
    return min(T->root)->key;
}

node max(node x)
{
    node t = x;
    while(t->right)
        t = t->right;
    return t;
}

int maxVal(tree T)
{
    return max(T->root)->key;
}

node predecessor(tree T, int k)
{
    node x = search(T, k);
    if(!x)
        return NULL;
    if(x->left)
        return max(x->left);
    node y = x->p;
    while(y && x==y->left)
    {
        x = y;
        y = y->p;
    }
    return y;
}

node successor(tree T, int k)
{
    node x = search(T, k);
    if(!x)
        return NULL;
    if(x->right)
        return min(x->right);
    node y = x->p;
    while(y && x==y->right)
    {
        x = y;
        y = y->p;
    }
    return y;
}

void inOrder(tree T)
{
    if(!T->root)
        return;
    struct bst t;
    if(T->root->left)
    {
        t.root = T->root->left;
        inOrder(&t);
    }
    printf("%d ", T->root->key);
    if(T->root->right)
    {
        t.root = T->root->right;
        inOrder(&t);
    }
}

void preOrder(tree T)
{
    if(!T->root)
        return;
    struct bst t;
    printf("%d ", T->root->key);
    if(T->root->left)
    {
        t.root = T->root->left;
        preOrder(&t);
    }
    if(T->root->right)
    {
        t.root = T->root->right;
        preOrder(&t);
    }
}

void postOrder(tree T)
{
    if(!T->root)
        return;
    struct bst t;
    if(T->root->left)
    {
        t.root = T->root->left;
        postOrder(&t);
    }
    if(T->root->right)
    {
        t.root = T->root->right;
        postOrder(&t);
    }
    printf("%d ", T->root->key);
}