#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct bNode{
    int key;
    struct bNode *left, *right, *p;
} *node;

typedef struct bTree{
    node root;
} *tree;

typedef struct bst{
    int s, c, min, max, is;
} deets;

deets findBST(node, int);
node createTree(char*, int, int);
int getNum(char*, int*);
int findEnd(char*, int, int);
node createNode(int);
int min(int, int, int);
int max(int, int, int);

int main()
{
    tree T = (tree)malloc(sizeof(struct bTree));
    char s[1000];
    int k;
    fgets(s, 1000, stdin);
    int n = strlen(s);
    T->root = createTree(s, 2, n-2);
    scanf("%d", &k);
    deets d = findBST(T->root, k);
    printf("%d %d %d %d", d.c, d.s, d.max, d.min);
    return 0;
}

deets findBST(node t, int k)
{
    deets d;
    d.s = d.c = 0;
    d.is = 1;
    d.max = -1000001;
    d.min = 1000001;
    if(!t)
        return d;
    if(!t->left && !t->right)
    {
        d.s = d.max = d.min = t->key;
        if(d.s==k)
            d.c = 1;
        return d;
    }
    deets l = findBST(t->left, k);
    deets r = findBST(t->right, k);
    d.min = min(t->key, l.min, r.min);
    d.max = max(t->key, l.max, r.max);
    d.s = l.s + r.s + t->key;
    if(l.is && r.is && t->key>l.max && t->key<r.min)
    {
        d.is = 1;
        if(d.s==k)
            d.c = 1 + l.c + r.c;
        else
            d.c = l.c + r.c;
    }
    else
    {
        d.is = 0;
        d.c = l.c + r.c;
    }
    return d;
}

node createTree(char* s, int start, int end)
{
    if(start>end)
        return NULL;
    node root = NULL;
    int f = 0;
    if(isdigit(s[start]))
    {
        root = createNode(getNum(s, &start));
        f = 1;
    }
    if(s[start]==' ')
        ++start;
    int i = -1;
    if(s[start]=='(')
        i = findEnd(s, start, end);
    if(f && i!=-1)
    {
        node t = createTree(s, start+2, i-2);
        root->left = t;
        if(t)
            t->p = root->left;
        t = createTree(s, i+4, end);
        root->right = t;
        if(t)
            t->p = root->right;
    }
    return root;
}

node createNode(int k)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = k;
    x->left = x->right = x->p = NULL;
    return x;
}

int min(int a, int b, int c)
{
    return (a<b ? a<c ? a : c : b<c ? b : c);
}

int max(int a, int b, int c)
{
    return (a>b ? a>c ? a : c : b>c ? b : c);
}

int getNum(char* s, int* i)
{
    int num = 0;
    while(isdigit(s[*i]))
        num = num*10 + (s[(*i)++]-'0');
    return num;
}

int findEnd(char* s, int start, int end)
{
    int c = 1;
    for(int i=start+2; i<end; i++)
    {
        if(s[i]==' ')
            continue;
        else if(s[i]=='(')
            c++;
        else if(s[i]==')')
            c--;
        if(c==0)
            return i;
    }
    return -1;
}
