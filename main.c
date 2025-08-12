#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char title[100];
    char director[50];
    int year;
} Book;

typedef struct Node {
    Book book;
    struct Node* left;
    struct Node* right;
} Node;

Node* initNode(char title[], char director[], int year) {
    Node* newNode = malloc(sizeof(Node));

    strcpy(newNode->book.title, title);
    strcpy(newNode->book.director, director);
    newNode->book.year = year;

    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertToTree(Node* root, char title[], char director[], int year) {
    if (root == NULL) {
        return initNode(title, director, year);
    }

    if (strcmp(title, root->book.title) < 0) {
        root->left = insertToTree(root->left, title, director, year);
    }
    else if (strcmp(title, root->book.title) > 0) {
        root->right = insertToTree(root->right, title, director, year);
    }
    return root;
}

void displayBook(Node* root) {
    if (root == NULL) {
        return;
    }
    displayBook(root->left);
    printf(" %s ", root->book.title);
    displayBook(root->right);
}

int findBook(Node* root, char title[]) {
    if (root == NULL) {
        return 0;
    }

    if (strcmp(title, root->book.title) == 0) {
        printf("found it!:\n %s %s %d", root->book.title, root->book.director, root->book.year);
        return 1;
    }

    if (strcmp(title, root->book.title) < 0) {
        return findBook(root->left, title);
    }
    else if (strcmp(title, root->book.title) > 0) {
        return findBook(root->right, title);
    }
}

Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root == root->left;
    }
    return root;
}

Node* deleteNode(Node* root, char title[]) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(title, root->book.title) < 0) {
        root->left = deleteNode(root->left, title);
    }
    else if (strcmp(title, root->book.title) > 0) {
        root->right = deleteNode(root->right, title);
    }
    else {
        // case 1: no child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        //case 2: 1 child
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root->left);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root->right);
            return temp;
        }

        //case 3: root (2 children)
        Node* temp = findMin(root->right);
        strcpy(root->book.title, temp->book.title);
        strcpy(root->book.director, temp->book.director);
        root->book.year = temp->book.year;

        root->right = deleteNode(root->right, temp->book.title);
    }
    return root;
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int left = countNodes(root->left);
    int right = countNodes(root->right);

    return 1 + left + right;

}

void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void menu() {
    printf("\nMenu=======================\n");
    printf("1. Add\n");
    printf("2. Display\n");
    printf("3. Find\n");
    printf("4. Delete\n");
    printf("5. CountNode\n");
    printf("6. Exit\n");
    printf("ur choice: \n");
}

int main(void) {
    Node* root = NULL;

    char title[100];
    char director[50];
    int year;

    int choice;
    do {
        menu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                printf("insert book title: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';

                printf("director: ");
                fgets(director, 50, stdin);
                director[strcspn(director, "\n")] = '\0';

                printf("year: ");
                scanf("%d", &year);
                getchar();

                root = insertToTree(root, title, director, year);
                break;
            }
            case 2: {
                if (root == NULL) {
                    printf("nothing in tree\n");
                    break;
                }
                displayBook(root);
                break;
            }
            case 3: {
                printf("title want to find: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';

                if (!findBook(root, title)) {
                    printf("cannot find the book\n");
                    break;
                }
                break;
            }

            case 4: {
                printf("title to delete: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';

                root = deleteNode(root, title);
                break;
            }

            case 5: {
                printf("total nodes: %d", countNodes(root));
                break;
            }

            case 6: {
                freeTree(root);
                printf("exiting...\n");
                break;
            }
            default:
                break;
        }

    } while (choice != 6);
    return 0;
}