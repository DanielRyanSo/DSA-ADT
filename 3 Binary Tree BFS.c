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
    Node *arr[100];
    int front, rear;
} Queue;

void qInit(Queue *q) { q->front = q->rear = 0; }
int  qEmpty(Queue *q) { return q->front == q->rear; }
void enqueue(Queue *q, Node *n) { q->arr[q->rear++] = n; }
Node *dequeue(Queue *q) { return q->arr[q->front++]; }

void bfs(Node *root) {
    if (!root) return;

    Queue q;
    qInit(&q);
    enqueue(&q, root);

    while (!qEmpty(&q)) {
        Node *cur = dequeue(&q);
        printf("%d ", cur->key);

        if (cur->left)  enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
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

    printf("BFS (level-order) traversal: ");
    bfs(root);
    printf("\n");

    return 0;
}
