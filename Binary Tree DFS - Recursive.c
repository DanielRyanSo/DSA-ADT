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

/* DFS traversals */

void preorder(Node *root) {        /* Root, Left, Right */
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root) {         /* Left, Root, Right */
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void postorder(Node *root) {       /* Left, Right, Root */
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

int main(void) {
    Node *root = newNode(1);
    root->left  = newNode(2);
    root->right = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right= newNode(7);

    printf("Preorder DFS:  ");
    preorder(root);
    printf("\n");

    printf("Inorder DFS:   ");
    inorder(root);
    printf("\n");

    printf("Postorder DFS: ");
    postorder(root);
    printf("\n");

    return 0;
}
