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

typedef struct queue{
    node *A;
    int head, tail;
} *Q;

int n;

node createNode(int);
node createTree(char*, int, int);
int getNum(char*, int*);
int findEnd(char*, int, int);
void printC(tree, int);
void enq(Q, node);
node deq(Q);

int main()
{
    tree T = (tree)malloc(sizeof(struct bTree));
    char s[1000];
    int k;
    fgets(s, 1000, stdin);
    n = strlen(s);
    T->root = createTree(s, 2, n-2);
    scanf("%d", &k);
    printC(T, k);
    return 0;
}

node createNode(int k)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = k;
    x->left = x->right = x->p = NULL;
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
        t = createTree(s, i+4, end-2);
        root->right = t;
        if(t)
            t->p = root;
    }
    return root;
}

void printC(tree T, int k)
{
    node t = T->root;
    Q q = (Q)malloc(sizeof(struct queue));
    q->A = (node*)malloc((n/4)*sizeof(node));
    q->head = q->tail = -1;
    int f = 0;
    if(t->key==k)
    {
        printf("-1\n");
        return;
    }
    enq(q, t);
    int c = 1, t1 = 0;
    while(q->head!=-1 && !f)
    {
        t1 = 0;
        while(c)
        {
            t = deq(q);
            if((t->left && t->left->key==k) || (t->right && t->right->key==k))
                f = 1;
            else
            {
                if(t->left)
                {
                    enq(q, t->left);
                    t1++;
                }
                if(t->right)
                {
                    enq(q, t->right);
                    t1++;
                }
            }
            c--;
        }
        c = t1;
    }
    if(f)
    {
        if(!t1)
            printf("-1\n");
        else
        {
            while(q->head!=-1)
                printf("%d ", deq(q)->key);
        }
    }
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

void enq(Q Q, node k)
{
    if(Q->head==-1)
    {
        Q->A[++Q->head] = k;
        Q->tail = 1;
    }
    else if(Q->head!=Q->tail && Q->head!=-1)
    {
        Q->A[Q->tail] = k;
        Q->tail = (Q->tail+1)%(n/4);
    }
    else
        printf("-1\n");
}

node deq(Q Q)
{
    if(Q->head!=-1)
    {
        int t = Q->head;
        Q->head = (Q->head+1)%(n/4);
        if(Q->head==Q->tail)
            Q->head = Q->tail = -1;
        return Q->A[t];
    }
    return NULL;
}