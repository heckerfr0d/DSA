#include <stdio.h>
#include <stdlib.h>

typedef struct bHeap{
    int key, degree;
    struct bHeap *p, *child, *sibling;
} *heap;

typedef struct queue{
    heap *A;
    int head, tail;
} *Q;

heap makeHeap();
heap insert(heap, int);
heap min(heap);
heap extractMin(heap);
int decreaseKey(heap, int, int);
heap delete(heap, int);
heap Union(heap, heap);
heap link(heap, heap);
heap merge(heap, heap);
heap reverse(heap);
heap search(heap, int);
void enq(Q, heap);
heap deq(Q);
void udayip(heap);
void print(heap);

int main()
{
    heap H = NULL, x = NULL;
    char c;
    do
    {
        scanf("%c", &c);
        int k, z;
        switch(c)
        {
        case 'i':
            scanf("%d", &k);
            H = insert(H, k);
            break;
        case 'm':
            x = min(H);
            x ? printf("%d\n", x->key) : printf("-1\n");
            break;
        case 'x':
            H = extractMin(H);
            break;
        case 'r':
            scanf("%d%d", &k, &z);
            decreaseKey(H, k, z);
            break;
        case 'd':
            scanf("%d", &k);
            H = delete(H, k);
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
    heap H = (heap)malloc(sizeof(struct bHeap));
    H->p = H->child = H->sibling = NULL;
    H->key = H->degree = 0;
}

heap min(heap H)
{
    if(!H)
        return NULL;
    heap y = NULL;
    heap x = H;
    int min = 1000001;
    while(x)
    {
        if(x->key<min)
        {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

heap link(heap H1, heap H2)
{
    H1->p = H2;
    H1->sibling = H2->child;
    H2->child = H1;
    H2->degree++;
    return H2;
}

heap merge(heap H1, heap H2)
{
    heap H3 = makeHeap();
    heap t = H3;
    while(H1 && H2)
    {
        if(H1->degree<H2->degree)
        {
            t->sibling = H1;
            H1 = H1->sibling;
        }
        else
        {
            t->sibling = H2;
            H2 = H2->sibling;
        }
        t = t->sibling;
    }
    if(H1)
        t->sibling = H1;
    if(H2)
        t->sibling = H2;
    return H3->sibling;

}

heap Union(heap H1, heap H2)
{
    heap H = merge(H1, H2);
    if(!H)
        return H;
    heap prev = NULL, x = H, next = H->sibling;
    while(next)
    {
        if((x->degree!=next->degree) || (next->sibling && next->sibling->degree==x->degree))
        {
            prev = x;
            x = next;
        }
        else if(x->key<=next->key)
        {
            x->sibling = next->sibling;
            x = link(next, x);
        }
        else
        {
            if(!prev)
                H = next;
            else
                prev->sibling = next;
            x = link(x, next);
        }
        next = x->sibling;
    }
    return H;
}

heap insert(heap H, int k)
{
    heap h1 = makeHeap();
    h1->key = k;
    return H = Union(H, h1);
}

heap reverse(heap H)
{
    if(!H)
        return NULL;
    heap prev = NULL, x = H, next = NULL;
    while(x)
    {
        x->p = NULL;
        next = x->sibling;
        x->sibling = prev;
        prev = x;
        x = next;
    }
    return prev;
}

heap extractMin(heap H)
{
    if(!H)
    {
        printf("-1\n");
        return NULL;
    }
    heap y = H, prev = NULL, z = NULL;
    heap x = H;
    int min = H->key;
    while(x->sibling)
    {
        if(x->sibling->key<min)
        {
            min = x->sibling->key;
            prev = x;
            y = x->sibling;
        }
        x = x->sibling;
    }
    if(prev)
        prev->sibling = y->sibling;
    else
        H = y->sibling;
    if(y->key)
        printf("%d\n", y->key);
    return H = Union(H, reverse(y->child));
}

heap search(heap H, int x)
{
    if(!H)
        return H;
    if(H->key==x)
        return H;
    heap f = search(H->child, x);
    return f ? f : search(H->sibling, x);
}

int decreaseKey(heap H, int x, int k)
{
    heap t = search(H, x);
    if(!t || x<k || k<0)
    {
        printf("-1\n");
        return 0;
    }
    t->key = x - k;
    x-k ? printf("%d\n", x-k) : printf("%d\n", x);
    heap z = t->p;
    while(z && t->key<z->key)
    {
        t->key = z->key;
        z->key = x - k;
        t = z;
        z = t->p;
    }
    return 1;
}

heap delete(heap H, int x)
{
    if(decreaseKey(H, x, x))
        return H = extractMin(H);
    return H;
}

void print(heap H)
{
    if(!H)
        return;
    Q q = (Q)malloc(sizeof(struct queue));
    q->A = (heap*)calloc(500009, sizeof(heap));
    q->head = q->tail = -1;
    heap t = H, t1 = NULL;
    while(t)
    {
        printf("%d ", t->key);
        enq(q, t->child);
        while(t1 = deq(q))
        {
            while(t1)
            {
                printf("%d ", t1->key);
                if(t1->child)
                    enq(q, t1->child);
                t1 = t1->sibling;
            }
        }
        t = t->sibling;
    }
}

void enq(Q Q, heap k)
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

heap deq(Q Q)
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