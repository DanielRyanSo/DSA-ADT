#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(char *arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

void heapify(char *arr[], int n, int i) {
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;

        if (l < n && strcmp(arr[largest], arr[l]) < 0) largest = l;
        if (r < n && strcmp(arr[largest], arr[r]) < 0) largest = r;
        if (largest == i) return;

        char *temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        i = largest;
    }
}

void heapSort(char *arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        char *temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main() {
    char *arr[] = {"Charlie", "Alice", "Bob", "Eve", "David", "Frank"};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array of names: ");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array of names:   ");
    printArray(arr, n);

    return 0;
}
