#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    char *word;
    struct node *next;
} *Node;

Node insert(Node, char*);
void print(Node*, int);
Node createNode(char*);
int mystrcmp(char*, char*);

int main()
{
    int k, c = 0;
    char s[500];
    char *word = (char*)calloc(50, sizeof(char));
    scanf("%d\n", &k);
    fgets(s, 500, stdin);
    Node *T = (Node*)calloc(k, sizeof(Node));
    for(int i=0; s[i]; i++)
    {
        if(s[i]==' ' || s[i]=='\n')
        {
            word[c] = '\0';
            int j = (c*c)%k;
            T[j] = insert(T[j], word);
            c = 0;
            word = (char*)calloc(50, sizeof(char));
        }
        else
            word[c++] = s[i];
    }
    print(T, k);
    return 0;
}

Node createNode(char* word)
{
    Node w = (Node)malloc(sizeof(Node));
    w->word = word;
    w->next = NULL;
    return w;
}

Node insert(Node T, char *word)
{
    if(!T)
        return T = createNode(word);
    Node t = T, prev = NULL;
    while(t && mystrcmp(t->word, word))
    {
        prev = t;
        t = t->next;
    }
    if(!t)
        prev->next = createNode(word);
    return T;
}

void print(Node *T, int k)
{
    for(int i=0; i<k; i++)
    {
        printf("%d:", i);
        Node t = T[i];
        if(!t)
            printf("null ");
        while(t)
        {
            printf("%s-", t->word);
            t = t->next;
        }
        printf("\b \n");
    }
}

int mystrcmp(char* word1, char* word2)
{
    for(int i=0; word1[i] && word2[i]; i++)
        if(tolower(word1[i]) != tolower(word2[i]))
            return 1;
    return 0;
}