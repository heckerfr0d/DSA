#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct bNode{
    int key;
    struct bNode *left, *right;
} *node;

typedef struct bst{
    node root;
} *tree;

int kSmallest(tree, int);
int kLargest(tree, int);
int getKsmall(node, int*);
void inOrder(tree);
node predecessor(tree, int);
node successor(tree, int);
node createNode(int);
node createTree(char*, int, int);
int findEnd(char*, int, int);
int getNum(char*, int*);
int c = 0;

int main()
{
    tree T = (tree)malloc(sizeof(tree));
    node x = NULL;
    char s[1000];
    fgets(s, 1000, stdin);
    int n = strlen(s), k;
    T->root = createTree(s, 2, n-2);
    char ch;
    do
    {
        scanf("%c", &ch);
        switch(ch)
        {
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
            break;
        case 'l':
            scanf("%d", &k);
            k = kLargest(T, k);
            k != -1000001 ? printf("%d\n", k) : printf("-1\n");
            break;
        case 's':
            scanf("%d", &k);
            k = kSmallest(T, k);
            k != -1000001 ? printf("%d\n", k) : printf("-1\n");
            break;
        }
    } while (ch != 'e');
    return 0;
}

int kSmallest(tree T, int k)
{
    return getKsmall(T->root, &k);
}

int getKsmall(node x, int *k)
{
    if(!x)
        return -1000001;
    int l = getKsmall(x->left, k);
    if(l!=-1000001)
        return l;
    if(!(--(*k)))
        return x->key;
    return getKsmall(x->right, k);
}

int kLargest(tree T, int k)
{
    int k1 = c-k+1;
    return getKsmall(T->root, &k1);
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

node predecessor(tree T, int k)
{
    node x = search(T, k);
    if(!x)
        return NULL;
    if(x->left)
        return max(x->left);
    node y = T->root, pred = NULL;
    while(y)
    {
        if(y->key<k)
        {
            pred = y;
            y = y->right;
        }
        else
            y = y->left;
    }
    return pred;
}

node successor(tree T, int k)
{
    node x = search(T, k);
    if(!x)
        return NULL;
    if(x->right)
        return min(x->right);
    node y = T->root, succ = NULL;
    while(y)
    {
        if(y->key>k)
        {
            succ = y;
            y = y->left;
        }
        else
            y = y->right;
    }
    return succ;
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

node createNode(int k)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = k;
    x->left = NULL;
    x->right = NULL;
    return x;
}

node createTree(char* s, int start, int end)
{
    if(start>end)
        return NULL;
    node root = NULL;
    int f = 0;
    if(isdigit(s[start]) || s[start]=='-')
    {
        root = createNode(getNum(s, &start));
        f = 1;
        c++;
    }
    if(s[start]==' ')
        ++start;
    int i = -1;
    if(s[start]=='(')
        i = findEnd(s, start, end);
    if(f && i!=-1)
    {
        root->left = createTree(s, start+2, i-2);
        root->right = createTree(s, i+4, end-2);
    }
    return root;
}


int getNum(char* s, int* i)
{
    int num = 0, neg = 0;
    if(s[*i]=='-')
    {
        neg = 1;
        (*i)++;
    }
    while(isdigit(s[*i]))
        num = num*10 + (s[(*i)++]-'0');
    if(neg)
	    return -num;
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
