#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct bNode{
    int key;
    struct bNode *left, *right, *p;
} *node;

typedef struct bst{
    node root;
} *tree;

node createNode(int);
node createTree(char*, int, int);
int findEnd(char*, int, int);
int getNum(char*, int*);
int kSmallest(tree, int);
int getKsmall(node, int*);
node search(tree, int);
node min(node);
node predecessor(tree, int);
node successor(tree, node);


int main()
{
    tree T = (tree)malloc(sizeof(tree));
    char s[1000];
    fgets(s, 1000, stdin);
    int n = strlen(s), k;
    T->root = createTree(s, 2, n-2);
    scanf("%d", &k);
    printf("%d\n", kSmallest(T, k+1));
    return 0;
}

int kSmallest(tree T, int k)
{
    return getKsmall(T->root, &k);
}

int getKsmall(node x, int *k)
{
    if(!x)
        return 0;
    int l = getKsmall(x->left, k);
    if(l)
        return l;
    if(!(--(*k)))
        return x->key;
    return getKsmall(x->right, k);
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
            t->p = root;
        t = createTree(s, i+4, end);
        root->right = t;
        if(t)
            t->p = root;
    }
    return root;
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
