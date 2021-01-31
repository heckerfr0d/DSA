#include <stdio.h>
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

node insert(tree, int);
void print(tree);
void enq(Q, node);
node deq(Q);

int main()
{
    tree T = (tree)malloc(sizeof(struct bTree));
    char c;
    do
    {
        int a;
        scanf("%c", &c);
        switch (c)
        {
        case 'i':
            scanf("%d", &a);
            T->root = insert(T, a);
            break;
        case 'p':
            print(T);
            printf("\n");
            break;
        }
    } while (c!='e');
    return 0;
}

node insert(tree T, int k)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = k;
    x->left = x->right = x->p = NULL;
    Q q = (Q)malloc(sizeof(struct queue));
    q->A = (node*)malloc(500009*sizeof(node));
    q->head = q->tail = -1;
    if(!T->root)
        T->root = x;
    else
    {
        node t = T->root;
        while(t)
        {
            if(t->left)
                enq(q, t->left);
            else
            {
                t->left = x;
                x->p = t;
                return T->root;
            }
            if(t->right)
                enq(q, t->right);
            else
            {
                t->right = x;
                x->p = t;
                return T->root;
            }
            t = deq(q);
        }
    }
    return T->root;
}

void print(tree T)
{
    struct bTree t;
    t.root = NULL;
    printf("( ");
    if(T->root)
    {
        printf("%d ", T->root->key);
        t.root = T->root->left;
        print(&t);
        t.root = T->root->right;
        print(&t);
    }
    printf(") ");
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