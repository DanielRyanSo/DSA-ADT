#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum length for the key
#define MAX_KEY_LEN 100

// 1. Structure Definition
typedef struct node {
   char *key;          // The string element used for comparison and storage
   struct node* LC;   // Left Child pointer
   struct node* RC;   // Right Child pointer
} Node, *BST;


void insert(BST *tree, const char *key_data) {
    // TODO...
    Node* newnode = malloc(sizeof(Node));
    newnode->key = malloc(strlen(key_data)+1);
    strcpy(newnode->key, key_data);
    newnode->LC = newnode->RC = NULL;
    
    if(*tree == NULL){
        *tree = newnode; 
        printf("Inserted key: \"%s\" \n", newnode->key);
        return;
    }
    
    Node* curr = *tree;
    Node* prev = NULL;
    
    while(curr != NULL){
        if(strcmp(key_data, curr->key) == 0){
            printf("Key \"%s\" already exists. Ignoring.\n");return;
        }
        if(strcmp(key_data, curr->key) < 0){
            prev = curr; 
            curr = curr->LC;
        }else{
            prev = curr; 
            curr = curr->RC;
        }
    }
    
    if(strcmp(key_data, prev->key) < 0){
        prev->LC = newnode;
        printf("Inserted key: \"%s\" \n", key_data);
    }else{
        prev->RC = newnode;
        printf("Inserted key: \"%s\" \n", key_data);
    }
}

void inorderTraversal(BST tree) {
    // TODO...
    BST stack[20];
    int top = -1;
    
    Node *curr = tree;
    
    while(curr != NULL || top != -1){
        while(curr != NULL){
            stack[++top] = curr;
            curr = curr->LC;
        }
        
        curr = stack[top--];
        printf("\"%s\" ", curr->key);
        curr = curr->RC;
    }
}

void preorderTraversal(BST tree) {
    BST stack[20];
    int top = -1;
    
    stack[++top] = tree;
    
    while(top != -1){
        Node *curr = stack[top--];
        printf("\"%s\" ", curr->key);
        
        if(curr->RC) stack[++top] = curr->RC;
        if(curr->LC) stack[++top] = curr->LC;
        
    }
}

void postorderTraversal(BST tree) {
    // TODO...
    if (tree == NULL) return;

    BST stack1[20], stack2[20];
    int top1 = -1, top2 = -1;

    stack1[++top1] = tree;

    while (top1 != -1) {
        Node *curr = stack1[top1--];
        stack2[++top2] = curr;

        if (curr->LC) stack1[++top1] = curr->LC;
        if (curr->RC) stack1[++top1] = curr->RC;
    }

    while (top2 != -1) {
        Node *node = stack2[top2--];
        printf("\"%s\" ", node->key);
}

    
}

/**
 * @brief Frees all memory allocated for the BST nodes, including the string keys.
 * * @param tree The root of the tree to destroy.
 */
void destroyTree(BST tree) {
    if (tree != NULL) {
        destroyTree(tree->LC);
        destroyTree(tree->RC);

        if (tree->key != NULL) {
            free(tree->key);
        }

        free(tree);
    }
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Initializing and Inserting String Data into BST ---\n");

    // Root: 'Mango'
    // Left: 'Apple', 'Banana'
    // Right: 'Pineapple', 'Grape', 'Orange', 'Kiwi'
    insert(&myTree, "Mango");
    insert(&myTree, "Apple");
    insert(&myTree, "Pineapple");
    insert(&myTree, "Banana");
    insert(&myTree, "Grape");
    insert(&myTree, "Orange");
    insert(&myTree, "Kiwi");

    // Test duplicate handling
    insert(&myTree, "Mango");

    printf("\n\n--- BST Traversal Results ---\n");

    // In-Order: Sorted (A, B, G, K, M, O, P)
    printf("1. In-Order Traversal (Left-Root-Right, Sorted):\n");
    printf("   ");
    inorderTraversal(myTree);
    printf("\n\n");

    // Pre-Order: Root first (M, A, B, P, G, K, O)
    printf("2. Pre-Order Traversal (Root-Left-Right):\n");
    printf("   ");
    preorderTraversal(myTree);
    printf("\n\n");

    // Post-Order: Root last (B, A, K, O, G, P, M)
    printf("3. Post-Order Traversal (Left-Right-Root):\n");
    printf("   ");
    postorderTraversal(myTree);
    printf("\n\n");

    // 3. Clean up memory
    destroyTree(myTree);
    printf("Tree destroyed and memory freed.\n");

    return 0;
}
