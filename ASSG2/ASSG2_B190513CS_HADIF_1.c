#include <stdio.h>
#include <stdlib.h>

typedef struct hashTable{
    int product_id;
} *table;

table* hashTable(int);
void insert(table*, int);
void delete(table*, int);
int search(table*, int);
void print(table*);
int dhash(int, int);
int qhash(int, int);
int sPrime(int);

char a;
int c1, c2, m, R;

int main()
{
    int k;
    char ch;
    scanf("%c%d", &a, &m);
    if(a == 'a')
        scanf("%d%d", &c1, &c2);
    else
        R = sPrime(m);
    table *T = hashTable(m);
    do
    {
        scanf("%c", &ch);
        switch(ch)
        {
        case 'i':
            scanf("%d", &k);
            insert(T, k);
            break;
        case 's':
            scanf("%d", &k);
            search(T, k)==-1 ? printf("-1\n") : printf("1\n");
            break;
        case 'd':
            scanf("%d", &k);
            delete(T, k);
            break;
        case 'p':
            print(T);
            break;
        }
    } while (ch!='t');
    
    return 0;
}

table* hashTable(int m)
{
    return (table*)calloc(m, sizeof(table));
}

int qhash(int k, int i)
{
    return (k%m + c1*i + c2*i*i)%m;
}

int dhash(int k, int i)
{
    return (k%m + i*(R-k%R))%m;
}

void insert(table* T, int k)
{
    for(int i=0; i<m; i++)
    {
        int j = a=='a' ? qhash(k, i) : dhash(k, i);
        if(!T[j])
        {
            T[j] = (table)malloc(sizeof(struct hashTable));
            T[j]->product_id = k;
            return;
        }
    }
}

int search(table* T, int k)
{
    for(int i=0; i<m; i++)
    {
        int j = a=='a' ? qhash(k, i) : dhash(k, i);
        if(T[j] && T[j]->product_id==k)
            return j;
    }
    return -1;
}

void delete(table* T, int k)
{
    int j = search(T, k);
    free(T[j]);
    T[j] = NULL;
}

void print(table* T)
{
    for(int i=0; i<m; i++)
    {
        printf("%d (", i);
        if(T[i])
            printf("%d", T[i]->product_id);
        printf(")\n");
    }
}

int isPrime(int n)
{
    if(n<2)
        return 0;
    if(n<4)
        return 1;
    if(!(n%2) || !(n%3))
        return 0;
    for(int i=5; i*i<n; i+=6)
        if(!(n%i) || !(n%(i+2)))
            return 0;
    return 1;
}

int sPrime(int n)
{
    int i = (n%2 && n!=3) ? n-2 : n-1;
    for(; i>=2; i-=2)
        if(isPrime(i))
            return i;
}