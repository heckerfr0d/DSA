#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
    char *string;
    struct node *next;
} *Node;

int hash(char*);
Node insert(Node, char*);
void print(Node*);
Node createNode(char*);
int isLess(char*, char*);

int main()
{
    int n;
    char *word = (char*)calloc(50, sizeof(char));
    Node *T = (Node*)calloc(255, sizeof(Node));
    scanf("%d\n", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%s", word);
        getc(stdin);
        int j = hash(word);
        T[j] = insert(T[j], word);
        word = (char*)calloc(50, sizeof(char));
    }
    print(T);
    return 0;
}

int hash(char *word)
{
    int *av = (int*)calloc(8, sizeof(int));
    int c = 0;
    for(int i=0; word[i]; i++)
    {
        if(!(av[word[i]-'a']++))
            c += pow(2, word[i]-'a');
    }
    free(av);
    return c%255;
}

Node createNode(char* word)
{
    Node w = (Node)malloc(sizeof(Node));
    w->string = word;
    w->next = NULL;
    return w;
}

Node insert(Node T, char *word)
{
    if(!T)
        return T = createNode(word);
    Node t = T, prev = NULL;
    while(t && isLess(t->string, word))
    {
        prev = t;
        t = t->next;
    }
    if(!prev)
    {
        t = createNode(word);
        t->next = T;
        T = t;
    }
    else
    {
        prev->next = createNode(word);
        prev->next->next = t;
    }
    return T;
}

void print(Node *T)
{
    for(int i=1; i<255; i++)
    {
        if(!T[i])
            continue;
        Node t = T[i];
        while(t)
        {
            printf("%s ", t->string);
            t = t->next;
        }
        printf("\n");
    }
    if(T[0])
    {
        Node t = T[0];
        while(t)
        {
            printf("%s ", t->string);
            t = t->next;
        }
        printf("\n");
    }
}

int isLess(char *s1, char *s2)
{
    int i;
    for(i=0; s1[i] == s2[i]; i++);
    if(s1[i] < s2[i])
        return 1;
    return 0;
}
