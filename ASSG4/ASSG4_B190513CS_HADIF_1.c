#include <stdio.h>
#include <stdlib.h>

void print(int n, int G[n][n])
{
    for(int i=0; i<n; i++)
    {
        printf("%d ", i);
        for(int j=0; j<n; j++)
            if(G[i][j])
                printf("%d ", j);
        printf("\n");
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int G[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &G[i][j]);
    print(n, G);
    return 0;
}