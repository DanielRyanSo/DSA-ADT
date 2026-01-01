#include <stdio.h>
#include <string.h>

#define MAX_CELLS 20
#define TITLE_LEN 64
#define CONTENT_LEN 255

typedef struct {
    int id;
    char title[TITLE_LEN + 1];
    char content[CONTENT_LEN + 1];
    int next;
} Cell;

typedef struct {
    Cell heap[MAX_CELLS];
    int avail;
} VHeap;

typedef int List;

void initVHeap(VHeap *vh) {
    vh->avail = 0;
    for (int i = 0; i < MAX_CELLS - 1; i++) {
        vh->heap[i].next = i + 1;
    }
    vh->heap[MAX_CELLS - 1].next = -1;
}

int allocCell(VHeap *vh) {
    int idx = vh->avail;
    if (idx != -1) {
        vh->avail = vh->heap[idx].next;
    }
    return idx;
}

void freeCell(VHeap *vh, int idx) {
    vh->heap[idx].next = vh->avail;
    vh->avail = idx;
}

void initList(List *L) {
    *L = -1;
}

int getNextId(VHeap *vh, List L) {
    int maxId = 0;
    for (int cur = L; cur != -1; cur = vh->heap[cur].next) {
        if (vh->heap[cur].id > maxId) maxId = vh->heap[cur].id;
    }
    return maxId + 1;
}

void insertArticle(VHeap *vh, List *L, const char *title, const char *content, int position) {
    int idx = allocCell(vh);
    if (idx == -1) {
        printf("No space left in virtual heap.\n");
        return;
    }

    vh->heap[idx].id = getNextId(vh, *L);
    strncpy(vh->heap[idx].title, title, TITLE_LEN);
    vh->heap[idx].title[TITLE_LEN] = '\0';
    strncpy(vh->heap[idx].content, content, CONTENT_LEN);
    vh->heap[idx].content[CONTENT_LEN] = '\0';

    if (*L == -1) {
        vh->heap[idx].next = -1;
        *L = idx;
        return;
    }

    if (position == -1) {
        int cur = *L;
        while (vh->heap[cur].next != -1) cur = vh->heap[cur].next;
        vh->heap[cur].next = idx;
        vh->heap[idx].next = -1;
        return;
    }

    if (position <= 0) {
        vh->heap[idx].next = *L;
        *L = idx;
        return;
    }

    int prev = *L;
    int k = 0;
    while (prev != -1 && k < position - 1) {
        prev = vh->heap[prev].next;
        k++;
    }

    if (prev == -1) {
        int cur = *L;
        while (vh->heap[cur].next != -1) cur = vh->heap[cur].next;
        vh->heap[cur].next = idx;
        vh->heap[idx].next = -1;
    } else {
        vh->heap[idx].next = vh->heap[prev].next;
        vh->heap[prev].next = idx;
    }
}

int searchArticle(VHeap *vh, List L, int id) {
    for (int cur = L; cur != -1; cur = vh->heap[cur].next) {
        if (vh->heap[cur].id == id) return cur;
    }
    return -1;
}

void deleteArticle(VHeap *vh, List *L, int id) {
    if (*L == -1) return;

    int cur = *L;
    int prev = -1;

    while (cur != -1 && vh->heap[cur].id != id) {
        prev = cur;
        cur = vh->heap[cur].next;
    }

    if (cur == -1) {
        printf("Article with id %d not found.\n", id);
        return;
    }

    if (prev == -1) {
        *L = vh->heap[cur].next;
    } else {
        vh->heap[prev].next = vh->heap[cur].next;
    }
    freeCell(vh, cur);
}

void displayArticles(VHeap *vh, List L) {
    printf("\nArticles:\n");
    for (int cur = L; cur != -1; cur = vh->heap[cur].next) {
        printf("ID: %d | Title: %s\n", vh->heap[cur].id, vh->heap[cur].title);
    }
}

void viewArticle(VHeap *vh, List L, int id) {
    int idx = searchArticle(vh, L, id);
    if (idx == -1) {
        printf("Article not found.\n");
        return;
    }
    printf("\nID: %d\nTitle: %s\nContent:\n%s\n",
           vh->heap[idx].id,
           vh->heap[idx].title,
           vh->heap[idx].content);
}

int main(void) {
    VHeap vh;
    List L;
    initVHeap(&vh);
    initList(&L);

    int choice;
    char title[TITLE_LEN + 1];
    char content[CONTENT_LEN + 1];
    int pos, id;

    do {
        printf("\nKnowledge Base Menu\n");
        printf("1. Insert article\n");
        printf("2. View list of articles\n");
        printf("3. Search article by ID\n");
        printf("4. Delete article by ID\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("Enter title: ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0';

            printf("Enter content: ");
            fgets(content, sizeof(content), stdin);
            content[strcspn(content, "\n")] = '\0';

            printf("Enter position (-1 for end): ");
            scanf("%d", &pos);
            getchar();

            insertArticle(&vh, &L, title, content, pos);
            break;

        case 2:
            displayArticles(&vh, L);
            break;

        case 3:
            printf("Enter ID to search: ");
            scanf("%d", &id);
            getchar();
            viewArticle(&vh, L, id);
            break;

        case 4:
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            getchar();
            deleteArticle(&vh, &L, id);
            break;

        case 0:
            break;

        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
