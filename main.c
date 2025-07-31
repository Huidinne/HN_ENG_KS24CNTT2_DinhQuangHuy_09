#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
} Node;

typedef struct Folder {
    Node data;
    struct Folder *left;
    struct Folder *right;
} Folder;

Folder *createFolder(char *name) {
    Folder *newFolder = (Folder *) malloc(sizeof(Folder));
    strcpy(newFolder->data.name, name);
    newFolder->left = NULL;
    newFolder->right = NULL;
    return newFolder;
}

Folder *insertFolder(Folder *folder, char *name) {
    if (folder == NULL) {
        return createFolder(name);
    }
    int cmp = strcmp(name, folder->data.name);
    if (cmp == 0) {
        printf("%s da ton tai\n", name);
        return folder;
    } else if (cmp < 0) {
        return insertFolder(folder->left, name);
    } else if (cmp > 0) {
        return insertFolder(folder->right, name);
    }
}

Folder *appendFolder(Folder *folder, char *name) {
    if (folder == NULL) {
        return createFolder(name);
    }
    int cmp = strcmp(name, folder->data.name);
    if (cmp == 0) {
        printf("%s da ton tai\n", name);
        return folder;
    } else if (cmp < 0) {
        folder->left = appendFolder(folder->left, name);
    } else {
        folder->right = appendFolder(folder->right, name);
    }
}

void inoder(Folder *folder) {
    if (folder != NULL) {
        inoder(folder->left);
        printf("%s \n", folder->data.name);
        inoder(folder->right);
    }
}

Folder *searchFolder(Folder *folder, char *name) {
    if (folder == NULL) {
        return NULL;
    }
    int cmp = strcmp(name, folder->data.name);
    if (cmp == 0) {
        printf("%s \n", name);
        return folder;
    } else if (cmp < 0) {
        return searchFolder(folder->left, name);
    } else if (cmp > 0) {
        return searchFolder(folder->right, name);
    }
}

int height(Folder *folder) {
    if (folder == NULL) {
        return 0;
    }
    int leftHeight = height(folder->left);
    int rightHeight = height(folder->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int main(void) {
    int choice;
    Folder *root = NULL;
    do {
        printf("\n FOLDER MANAGER \n");
        printf("1. Tao thu muc goc \n");
        printf("2. Them thu muc con \n");
        printf("3. In cau truc thu muc \n");
        printf("4. Tim kiem thu muc theo ten \n");
        printf("5. Tinh chieu cao he thong thu muc \n");
        printf("6. In duong dan tu thu muc goc -> thu muc con \n");
        printf("7. Thoat \n");
        printf("Lua chon cua ban la: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                char name[50];
                printf("Nhap ten thu muc : ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';
                root = createFolder(name);
                break;
            }
            case 2: {
                char name[50];
                printf("Nhap ten thu muc con : ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';
                appendFolder(root, name);
                break;
            }
            case 3: {
                if (root == NULL) {
                    printf("Chua co thu muc");
                } else {
                    inoder(root);
                }
                break;
            }
            case 4: {
                char name[50];
                printf("Nhap ten thu muc can tim : ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';
                searchFolder(root, name);
                break;
            }
            case 5: {
                int result = height(root);
                printf("%d \n", result);
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                printf("Thoat \n");
                break;
            }
            default: {
                printf("Lua chon khong hop le \n");
                break;
            }
        }
    } while (choice != 7);
    free(root);
    return 0;
}
