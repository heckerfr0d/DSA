#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node *p;
    int rank, key;
} *node;

node makeSet(int);
void Union(node**, int, int);
node linkR(node, node);
node link(node, node);
node findP(node, int);
node find(node, int);

int *s;

int main()
{
    node *S[4];
    s = (int*)calloc(4, sizeof(int));
    for(int i=0; i<4; i++)
        S[i] = (node*)calloc(10000, sizeof(node));
    char c;
    node x;
    do
    {
        scanf("%c", &c);
        int k, z;
        switch(c)
        {
        case 'm':
            scanf("%d", &k);
            if(S[0][k])
                printf("-1\n");
            else
            {
                S[0][k] = makeSet(k);
                S[1][k] = makeSet(k);
                S[2][k] = makeSet(k);
                S[3][k] = makeSet(k);
                printf("%d\n", k);
            }
            break;
        case 'f':
            scanf("%d", &k);
            if(!S[0][k])
                printf("-1\n");
            else
            {
                printf("%d ", find(S[0][k], 0)->key);
                printf("%d ", find(S[1][k], 1)->key);
                printf("%d ", findP(S[2][k], 2)->key);
                printf("%d\n", findP(S[3][k], 3)->key);
            }
            break;
        case 'u':
            scanf("%d%d", &k, &z);
            Union(S, k, z);
            break;
        }
    } while (c != 's');
    printf("%d %d %d %d\n", s[0], s[1], s[2], s[3]);
    return 0;
}


node makeSet(int x)
{
    node t = (node)malloc(sizeof(struct Node));
    t->p = t;
    t->rank = 0;
    t->key = x;
    return t;
}

node linkR(node x, node y)
{
    if(y->rank>x->rank)
    {
        x->p = y;
        return y;
    }
    else
        y->p = x;
    if(x->rank==y->rank)
        x->rank++;
    return x;
}

node link(node x, node y)
{
    y->p = x;
    return x;
}

void Union(node *S[4], int x, int y)
{
    if(!S[0][x] || !S[0][y])
        printf("-1\n");
    else
    {
        node x1 = find(S[0][x], 0), y1 = find(S[0][y], 0);
        if(!x1 || !y1)
            printf("-1\n");
        else
        {
            printf("%d ", link(x1, y1)->key);
            printf("%d ", linkR(find(S[1][x], 1), find(S[1][y], 1))->key);
            printf("%d ", link(findP(S[2][x], 2), findP(S[2][y], 2))->key);
            printf("%d\n", linkR(findP(S[3][x], 3), findP(S[3][y], 3))->key);
        }
    }
}


node findP(node x, int i)
{
    s[i]++;
    if(x!=x->p)
        x->p = findP(x->p, i);
    return x->p;
}

node find(node x, int i)
{
    s[i]++;
    if(x!=x->p)
        x = find(x->p, i);
    return x->p;
}

