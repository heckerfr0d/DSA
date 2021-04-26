#include<stdio.h>
#include<stdlib.h>

typedef struct queue{
    int *A;
    int head, tail;
} *Q;

void bfs(int, int, int**);
void dfs(int, int**);
void dfsV(int, char*, int, int**);
void enq(Q, int);
int deq(Q);

int main()
{
    int n, m, v1, v2;
    scanf("%d%d", &n, &m);
    int *G[n];
    for(int i=0; i<n; i++)
        G[i] = (int*)calloc(n, sizeof(int));
    for(int i=0;i<m;i++)
    {
        scanf("%d%d", &v1, &v2);
        G[v1][v2] = 1;
    }
    scanf("%d", &v1);
    bfs(v1, n, G);
    dfs(n, G);
    return 0;
}

void bfs(int v, int n, int** G)
{
    Q q = (Q)malloc(sizeof(struct queue));
    q->A = (int*)calloc(1000, sizeof(int));
    q->head = q->tail = -1;
    char* color = (char*)calloc(n, sizeof(char));
    color[v] = 'G';
    enq(q, v);
    int k=deq(q);
    while(k!=-1)
    {
        printf("%d ", k);
        for(int j=0; j<n; j++)
        {
            if(G[k][j] && !color[j])
            {
                color[j] = 'G';
                enq(q, j);
            }
        }
        color[k] = 'B';
        k = deq(q);
    }
    printf("\n");
}

void dfs(int n, int** G)
{
    char* color = (char*)calloc(n, sizeof(char));
    for(int i=0; i<n; i++)
        if(!color[i])
            dfsV(i, color, n, G);
}

void dfsV(int v1, char* color, int n, int** G)
{
    color[v1] = 'G';
    printf("%d ", v1);
    for(int j=0; j<n; j++)
        if(G[v1][j] && !color[j])
            dfsV(j, color, n, G);
    color[v1] = 'B';
}

void enq(Q Q, int k)
{
    if(Q->head==-1)
    {
        Q->A[++Q->head] = k;
        Q->tail = 1;
    }
    else if(Q->head!=Q->tail && Q->head!=-1)
    {
        Q->A[Q->tail] = k;
        Q->tail = (Q->tail+1)%1000;
    }
    else
        printf("-1\n");
}

int deq(Q Q)
{
    if(Q->head!=-1)
    {
        int t = Q->head;
        Q->head = (Q->head+1)%1000;
        if(Q->head==Q->tail)
            Q->head = Q->tail = -1;
        return Q->A[t];
    }
    return -1;
}