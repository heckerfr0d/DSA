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
node search(tree, int);
node min(node);
node max(node);
int predecessor(tree, int);
int successor(tree, int);
int level(tree, int);
int delete(tree, node);
void insert(tree, node);
void transplant(tree, node, node);
void inOrder(tree);
void preOrder(tree);
void postOrder(tree);

int main()
{
    tree T = (tree)malloc(sizeof(tree));
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
            printf("%d\n", min(T->root)->key);
            break;
        case 'x':
            printf("%d\n", max(T->root)->key);
            break;
        case 'r':
            scanf("%d", &k);
            printf("%d\n", predecessor(T, k));
            break;
        case 'u':
            scanf("%d", &k);
            printf("%d\n", successor(T, k));
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

node min(node x)
{
    node t = x;
    while(t->left)
        t = t->left;
    return t;
}

node max(node x)
{
    node t = x;
    while(t->right)
        t = t->right;
    return t;
}

int predecessor(tree T, int k)
{
    node x = search(T, k);
    if(!x)
        return -1;
    if(x->left)
        return max(x->left)->key;
    node y = x->p;
    while(y && x==y->left)
    {
        x = y;
        y = y->p;
    }
    return y->key;
}

int successor(tree T, int k)
{
    node x = search(T, k);
    if(!x)
        return -1;
    if(x->right)
        return min(x->right)->key;
    node y = x->p;
    while(y && x==y->right)
    {
        x = y;
        y = y->p;
    }
    return y->key;
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