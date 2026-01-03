#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node *newNode(int key) {
    Node *n = malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

typedef struct {
    Node *data[100];
    int top;
} Stack;

void sInit(Stack *s) { s->top = -1; }
int  sEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, Node *n) { s->data[++s->top] = n; }
Node *pop(Stack *s) { return s->data[s->top--]; }
Node *peek(Stack *s) { return s->data[s->top]; }

void iterativePreorder(Node *root) {
    if (!root) return;
    Stack s; sInit(&s);
    push(&s, root);
    while (!sEmpty(&s)) {
        Node *cur = pop(&s);
        printf("%d ", cur->key);
        if (cur->right) push(&s, cur->right);
        if (cur->left)  push(&s, cur->left);
    }
}

void iterativeInorder(Node *root) {
    Stack s; sInit(&s);
    Node *cur = root;
    while (cur != NULL || !sEmpty(&s)) {
        while (cur != NULL) {
            push(&s, cur);
            cur = cur->left;
        }
        cur = pop(&s);
        printf("%d ", cur->key);
        cur = cur->right;
    }
}

void iterativePostorder(Node *root) {
    if (!root) return;
    Stack s1, s2;
    sInit(&s1); sInit(&s2);

    push(&s1, root);
    while (!sEmpty(&s1)) {
        Node *cur = pop(&s1);
        push(&s2, cur);
        if (cur->left)  push(&s1, cur->left);
        if (cur->right) push(&s1, cur->right);
    }
    while (!sEmpty(&s2)) {
        Node *cur = pop(&s2);
        printf("%d ", cur->key);
    }
}

int main(void) {
    Node *root = newNode(1);
    root->left  = newNode(2);
    root->right = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right= newNode(7);

    printf("Iterative Preorder:  ");
    iterativePreorder(root);
    printf("\n");

    printf("Iterative Inorder:   ");
    iterativeInorder(root);
    printf("\n");

    printf("Iterative Postorder: ");
    iterativePostorder(root);
    printf("\n");

    return 0;
}
