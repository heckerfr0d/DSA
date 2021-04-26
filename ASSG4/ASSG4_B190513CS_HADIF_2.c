#include<stdio.h>
#include<stdlib.h>


typedef struct node{
    int vertex, weight;
    struct node *next;
} node;

typedef struct setNode{
    struct setNode *p;
    int rank, key;
} *snode;

typedef struct edge{
    int u, v, w;
} *edge;


int kruskal(node**, edge, int, int);
int prim(node**, int);
node* addEdge(node*, int);
snode makeSet(int);
void Union(snode*, int, int);
snode linkR(snode, snode);
snode findP(snode);
void merge_sort(edge, int, int);
void merge(edge, int, int, int);
int extractMin(int*, int*, int);


int main()
{
    char c;
    node **G;
    scanf("%c", &c);
    int n, ok, ik;
    scanf("%d", &n);
    G = (node**)calloc(n, sizeof(node*));
    if(c=='a')
    {
        edge E = (edge)calloc(n*n, sizeof(struct edge));
        int e = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%d%c", &ok, &c);
            if(c != '\n')
            {
                do
                {
                    scanf("%d%c", &ik, &c);
                    G[ok]=addEdge(G[ok], ik);
                    E[e].u = ok;
                    E[e++].v = ik;
                } while (c!='\n');
            }
        }
        e = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%d%c", &ok, &c);
            if(c != '\n')
            {
                node* t = G[ok];
                do
                {
                    scanf("%d%c", &ik, &c);
                    t->weight = ik;
                    t = t->next;
                    E[e++].w = ik;
                } while (c!='\n');
            }
        }
        printf("%d\n", kruskal(G, E, n, e));
    }
    else if(c=='b')
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d%c", &ok, &c);
            if(c != '\n')
            {
                do
                {
                    scanf("%d%c", &ik, &c);
                    G[ok]=addEdge(G[ok], ik);
                } while (c!='\n');
            }
        }
        for(int i=0;i<n;i++)
        {
            scanf("%d%c", &ok, &c);
            if(c != '\n')
            {
                node* t = G[ok];
                do
                {
                    scanf("%d%c", &ik, &c);
                    t->weight = ik;
                    t = t->next;
                } while (c!='\n');
            }
        }
        printf("%d\n", prim(G, n));
    }
    return 0;
}

int kruskal(node** G, edge E, int n, int e)
{
    snode *A = (snode*)calloc(n, sizeof(snode));
    for(int i=0; i<n; i++)
        A[i] = makeSet(i);
    merge_sort(E, 0, e-1);
    int mc=0;
    for(int i=0; i<e; i++)
    {
        if(findP(A[E[i].u]) != findP(A[E[i].v]))
        {
            mc += E[i].w;
            Union(A, E[i].u, E[i].v);
        }
    }
    return mc;
}

int prim(node** G, int n)
{
    int *in = (int*)calloc(n, sizeof(int));
    int *key = (int*)calloc(n, sizeof(int));
    int *p = (int*)calloc(n, sizeof(int));
    key[0] = 0;
    p[0] = -1;
    for(int i=1; i<n; i++)
    {
        key[i] = 10000;
        p[i] = -1;
    }
    int mc=0;
    for(int i=0; i<n; i++)
    {
        int u = extractMin(key, in, n);
        in[u] = 1;
        for(node *t = G[u]; t; t = t->next)
        {
            if(!in[t->vertex] && t->weight<key[t->vertex])
            {
                p[t->vertex] = u;
                key[t->vertex] = t->weight;
            }
        }
        mc += key[u];
    }
    return mc;
}

int extractMin(int *key, int *in, int n)
{
    int min = 10000, u = -1;
    for(int i=0; i<n; i++)
        if(!in[i] && key[i]<min)
            min = key[u=i];
    return u;
}

node* addEdge(node *chead, int newv)
{
    node* temp=(node*)malloc(sizeof(node));
    temp->vertex=newv;
    temp->weight = 0;
    temp->next = NULL;
    if(!chead)
        return temp;
    node* t = chead, *prev = NULL;
    while(t && t->vertex<newv)
    {
        prev = t;
        t = t->next;
    }
    if(!prev)
    {
        temp->next=chead;
        return temp;
    }
    prev->next = temp;
    temp->next = t;
    return chead;
}

snode makeSet(int x)
{
    snode t = (snode)malloc(sizeof(struct setNode));
    t->p = t;
    t->rank = 0;
    t->key = x;
    return t;
}

snode linkR(snode x, snode y)
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

snode link(snode x, snode y)
{
    y->p = x;
    return x;
}

void Union(snode *S, int x, int y)
{
    if(!S[x] || !S[y])
        return;
    else
        linkR(findP(S[x]), findP(S[y]));
}

snode findP(snode x)
{
    if(x!=x->p)
        x->p = findP(x->p);
    return x->p;
}

void merge_sort(edge a, int p, int r)
{
    if(p<r)
    {
        int q = p+(r-p)/2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
    }
}

void merge(edge a, int p, int q, int r)
{
    int i, j, n1=q-p+1, n2=r-q;
    struct edge L[n1], R[n2];
    for(i=0;i<n1;i++)
        L[i]=a[p+i];
    for(i=0;i<n2;i++)
        R[i]=a[q+1+i];
    i=j=0;
    int k = p;
    while(i<n1 && j<n2)
    {
        if(L[i].w && L[i].w<=R[j].w)
            a[k++]=L[i++];
        else
            a[k++]=R[j++];
    }
    while(i<n1 && L[i].w)
        a[k++]=L[i++];

    while(j<n2 && R[j].w)
        a[k++]=R[j++];
}
