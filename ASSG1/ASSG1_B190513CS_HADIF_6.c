#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct bNode{
    int key;
    struct bNode *left, *right, *p;
} *node;

typedef struct bst{
    node root;
} *tree;

node createBST(int*, int, int);
node createNode(int);
void getLsum(node, int*, int);
void print(tree);

int main()
{
    tree T = (tree)malloc(sizeof(struct bst));
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    T->root = createBST(a, 0, n-1);
    print(T);
    printf("\n");
    int k = log2(n)+1;
    int* sum = (int*)calloc(k, sizeof(int));
    getLsum(T->root, sum, 0);
    for(int i=0; i<k; i++)
        printf("%d ", sum[i]);
    return 0;
}

node createBST(int* a, int start, int end)
{
    if(start>end)
        return NULL;
    int m = (start+end)/2;
    node x = createNode(a[m]);
    x->left = createBST(a, start, m-1);
    x->right = createBST(a, m+1, end);
    return x;
}

node createNode(int c)
{
    node x = (node)malloc(sizeof(struct bNode));
    x->key = c;
    x->left = NULL;
    x->right = NULL;
    x->p = NULL;
    return x;
}

void print(tree T)
{
    struct bst t;
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

void getLsum(node x, int* sum, int l)
{
    if(!x)
        return;
    sum[l] += x->key;
    getLsum(x->left, sum, l+1);
    getLsum(x->right, sum, l+1);
}
