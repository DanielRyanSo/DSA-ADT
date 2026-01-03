#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

/**
 * @brief Deletes a node with the given key from the BST.
 * @param root The current root of the BST.
 * @param key_data The string key to delete.
 * @return BST The new root of the BST after deletion.
 */
BST deleteNode(BST root, const char *key_data) {

    Node *current = root;
    Node *parent = NULL;

    // 1. Search for the node
    while (current != NULL && strcmp(current->key, key_data) != 0) {
        parent = current;
        if (strcmp(key_data, current->key) < 0)
            current = current->LC;
        else
            current = current->RC;
    }

    // Not found
    if (current == NULL) return root;

    // Helper child pointer
    Node *child;

    // 2. Case 3: Node has 2 children
    if (current->LC != NULL && current->RC != NULL) {

        // Find inorder successor
        Node *succParent = NULL;
        Node *succ = current->RC;

        while (succ->LC != NULL) {
            succParent = succ;
            succ = succ->LC;
        }

        // Copy successor key
        current->key = succ->key;

        // Delete successor instead
        current = succ;
        parent = succParent;
    }

    // 3. Now node has 0 or 1 child
    if (current->LC != NULL && current->RC == NULL)child = current->LC;
    if (current->RC != NULL && current->LC == NULL)child = current->RC;
    if (current->LC == NULL && current->RC == NULL)child = NULL;
    
    if (parent == NULL) {
        // Deleting the root
        root = child;
    }
    else if (parent->LC == current) {
        parent->LC = child;
    }
    else {
        parent->RC = child;
    }

    free(current);
    return root;
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Building BST for Deletion Test ---\n");
    // Keys: Apple, Banana, Grape, Kiwi, Mango(ROOT), Orange, Pineapple
    insert(&myTree, "Mango");      // Root
    insert(&myTree, "Apple");      // Left of Mango
    insert(&myTree, "Pineapple");  // Right of Mango
    insert(&myTree, "Banana");     // Right of Apple
    insert(&myTree, "Grape");      // Left of Pineapple
    insert(&myTree, "Orange");     // Right of Grape
    insert(&myTree, "Kiwi");       // Left of Orange

    printf("\nInitial In-Order Traversal:\n   ");
    inorderTraversal(myTree);
    printf("\n");

    // --- Deletion Tests ---

    printf("\n--- Test 1: Delete Leaf Node (Kiwi) ---\n");
    // Kiwi is a leaf node (0 children)
    myTree = deleteNode(myTree, "Kiwi");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 2: Delete Node with 1 Child (Apple) ---\n");
    // Apple has 1 child (Banana)
    myTree = deleteNode(myTree, "Apple");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 3: Delete Node with 2 Children (Mango - the Root) ---\n");
    // Mango is replaced by its successor (Orange)
    myTree = deleteNode(myTree, "Mango");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 4: Delete Non-Existent Key (Zebra) ---\n");
    myTree = deleteNode(myTree, "Zebra");
    printf("No change expected: ");
    inorderTraversal(myTree);
    printf("\n");

    // 2. Clean up memory
    destroyTree(myTree);
    printf("\nTree destroyed and memory freed.\n");

    return 0;
}


#ifndef TYPES_H
#define TYPES_H

// Define a maximum length for the key
#define MAX_KEY_LEN 100

// 1. Structure Definition
typedef struct node {
   char *key;          // The string element used for comparison and storage
   struct node* LC;   // Left Child pointer
   struct node* RC;   // Right Child pointer
} Node, *BST;

#endif
