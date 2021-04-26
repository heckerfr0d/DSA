#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INT_MIN -1000001

typedef struct Node{
    int key, degree, mark;
    struct Node *p, *child, *left, *right;
} *node;

typedef struct fHeap{
    int n;
    node min;
} *heap;

typedef struct queue{
    node *A;
    int head, tail;
} *Q;

heap makeHeap();
node createNode(int);
heap insert(heap, node);
node min(heap);
heap consolidate(heap);
node extractMin(heap);
node search(node, int);
node decreaseKey(heap, node, int);
heap cut(heap, node, node);
heap cascadeCut(heap, node);
heap delete(heap, node);
heap Union(heap, heap);
node link(heap, node, node);
heap merge(heap, heap);
node search(node, int);
void enq(Q, node);
node deq(Q);
void print(heap);

int main()
{
    heap H = makeHeap();
    node x = NULL;
    char c;
    do
    {
        scanf("%c", &c);
        int k, z;
        switch(c)
        {
        case 'i':
            scanf("%d", &k);
            H = insert(H, createNode(k));
            break;
        case 'm':
            x = min(H);
            x ? printf("%d\n", x->key) : printf("-1\n");
            break;
        case 'x':
            x = extractMin(H);
            x ? printf("%d\n", x->key) : printf("-1\n");
            break;
        case 'r':
            scanf("%d%d", &k, &z);
            x = search(H->min, k);
            decreaseKey(H, x, z);
            break;
        case 'd':
            scanf("%d", &k);
            x = search(H->min, k);
            H = delete(H, x);
            break;
        case 'p':
            print(H);
            printf("\n");
            break;
        }
    } while (c != 'e');
    return 0;
}

heap makeHeap()
{
    heap H = (heap)malloc(sizeof(struct fHeap));
    H->n = 0;
    H->min = NULL;
    return H;
}

node createNode(int k)
{
    node x = (node)malloc(sizeof(struct Node));
    x->child = x->p = NULL;
    x->left = x->right = x;
    x->degree = x->mark = 0;
    x->key = k;
    return x;
}

heap insert(heap H, node x)
{
    if(!H->min)
        H->min = x;
    else
    {
        x->right = H->min;
        x->left = H->min->left;
        H->min->left->right = x;
        H->min->left = x;
        if(x->key<H->min->key)
            H->min = x;
    }
    H->n++;
    return H;
}

node min(heap H)
{
    if(!H)
        return NULL;
    return H->min;
}

heap Union(heap H1, heap H2)
{
    if(!H1->min || !H2->min)
        return H1->min ? H1 : H2;
    heap H = makeHeap();
    H->min = H1->min;
    H->min->right->left = H2->min->left;
    H2->min->left->right = H->min->right;
    H->min->right = H2->min;
    H2->min->left = H->min;
    if(H2->min->key<H->min->key)
        H->min = H2->min;
    H->n = H1->n + H2->n;
    return H;
}

node extractMin(heap H)
{
    if(!H || !H->min)
        return NULL;
    node z = H->min;
    node x = z->child;
    if(x)
    {
        do
        {
            x->p = NULL;
            x = x->right;
        } while (x != z->child);
    }
    if(z==z->right)
        H->min = x;
    else if(x)
    {
        z->right->left = x->left;
        x->left->right = z->right;
        z->left->right = x;
        x->left = z->left;
        H->min = z->right;
    }
    else
    {
        z->right->left = z->left;
        z->left->right = z->right;
        H->min = z->right;
    }
    H = consolidate(H);
    H->n--;
    return z;
}

heap consolidate(heap H)
{
    if(!H->min)
        return H;
    int n = (int)ceil(log(H->n)/0.2089876);
    node *A = (node*)calloc(n, sizeof(node));
    node t = H->min;
    do
    {
        node x = t;
        t = t->right;
        int d = x->degree;
        while(A[d])
        {
            node y = A[d];
            if(x->key>y->key)
            {
                node t1 = x;
                x = y;
                y = t1;
            }
            if(y==H->min)
                H->min = x;
            x = link(H, y, x);
            A[d++] = NULL;
        }
        A[d] = x;
    } while (t!=H->min);
    H->min = NULL;
    for(int i=0; i<n; i++)
    {
        if(A[i])
        {
            A[i]->left = A[i]->right = A[i];
            if(!H->min)
                H->min = A[i];
            else
            {
                A[i]->right = H->min;
                H->min->left->right = A[i];
                A[i]->left = H->min->left;
                H->min->left = A[i];
                if(A[i]->key<H->min->key)
                    H->min = A[i];
            }
        }
    }
    return H;
}


node link(heap H, node y, node x)
{
    y->left->right = y->right;
    y->right->left = y->left;
    y->left = y->right = y;
    y->p = x;
    y->mark = 0;
    if(!x->child)
        x->child = y;
    else
    {
        y->right = x->child;
        x->child->left->right = y;
        y->left = x->child->left;
        x->child->left = y;
        if(y->key<x->child->key)
            x->child = y;
    }
    x->degree++;
    return x;
}

node search(node min, int k)
{
    if(!min)
        return NULL;
    Q q = (Q)malloc(sizeof(struct queue));
    q->A = (node*)calloc(500009, sizeof(node));
    q->head = q->tail = -1;
    node t = min;
    do
    {
        node t1 = t;
        do
        {
            if(t->key==k)
                return t;
            if(t->key<k && t->child)
                enq(q, t->child);
            t = t->right;
        } while(t != t1);
        t = deq(q);
    } while(t && t != min);
    return NULL;
}


node decreaseKey(heap H, node x, int k)
{
    if(!x || x->key<k)
    {
        printf("-1\n");
        return NULL;
    }
    k==INT_MIN ? printf("%d\n", x->key) : printf("%d\n", k);
    x->key = k;
    if(x->p && x->key<x->p->key)
    {
        node y = x->p;
        H = cut(H, x, y);
        H = cascadeCut(H, y);
    }
    if(x->key<H->min->key)
        H->min = x;
    return x;
}

heap cut(heap H, node x, node y)
{
    if(x==x->right)
        y->child = NULL;
    else if(x==y->child)
        y->child = x->right;
    x->left->right = x->right;
    x->right->left = x->left;
    x->p = NULL;
    x->mark = 0;
    y->degree--;
    H = insert(H, x);
    H->n--;
    return H;
}

heap cascadeCut(heap H, node y)
{
    if(!y)
        return H;
    if(y->p)
    {
        if(!y->mark)
            y->mark = 1;
        else
        {
            node z = y->p;
            H = cut(H, y, z);
            H = cascadeCut(H, z);
        }
    }
    return H;
}

heap delete(heap H, node x)
{
    if(decreaseKey(H, x, INT_MIN))
        extractMin(H);
    return H;
}

void print(heap H)
{
    node t = H->min;
    do
    {
        printf("%d ", t->key);
        t = t->right;
    } while(t != H->min);
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
        Q->tail = (Q->tail+1)%500009;
    }
    else
        printf("-1\n");
}

node deq(Q Q)
{
    if(Q->head!=-1)
    {
        int t = Q->head;
        Q->head = (Q->head+1)%500009;
        if(Q->head==Q->tail)
            Q->head = Q->tail = -1;
        return Q->A[t];
    }
    return NULL;
}