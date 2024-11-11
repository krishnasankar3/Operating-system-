#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define BLOCK_SIZE 50

typedef struct Block {
    int blockNumber;
    char data[BLOCK_SIZE];
    struct Block *next;
} Block;

typedef struct {
    char fileName[20];
    Block *start;
    Block *end;
} File;

File files[MAX_FILES];
int blockCounter = 0;

Block* createBlock(char *data) {
    Block *newBlock = (Block *)malloc(sizeof(Block));
    if (!newBlock) {
        printf("Memory allocation error!\n");
        return NULL;
    }
    newBlock->blockNumber = blockCounter++;
    strncpy(newBlock->data, data, BLOCK_SIZE);
    newBlock->next = NULL;
    return newBlock;
}

void createFile(char *fileName, char *data) {
    int fileIndex = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (strlen(files[i].fileName) == 0) {
            fileIndex = i;
            break;
        }
    }
    if (fileIndex == -1) {
        printf("Error: Maximum file limit reached.\n");
        return;
    }
    strncpy(files[fileIndex].fileName, fileName, 20);
    files[fileIndex].start = NULL;
    files[fileIndex].end = NULL;
    int dataLength = strlen(data);
    for (int i = 0; i < dataLength; i += BLOCK_SIZE) {
        Block *newBlock = createBlock(data + i);
        if (!newBlock) {
            printf("Error: Not enough memory to store the file.\n");
            return;
        }
        if (files[fileIndex].start == NULL) {
            files[fileIndex].start = newBlock;
        } else {
            files[fileIndex].end->next = newBlock;
        }
        files[fileIndex].end = newBlock;
    }
    printf("File '%s' created successfully.\n", fileName);
}

void readFile(char *fileName) {
    int fileIndex = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].fileName, fileName) == 0) {
            fileIndex = i;
            break;
        }
    }
    if (fileIndex == -1) {
        printf("Error: File not found.\n");
        return;
    }
    printf("Reading file '%s':\n", fileName);
    Block *current = files[fileIndex].start;
    while (current != NULL) {
        printf("Block %d: %s\n", current->blockNumber, current->data);
        current = current->next;
    }
    printf("\n");
}

void deleteFile(char *fileName) {
    int fileIndex = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].fileName, fileName) == 0) {
            fileIndex = i;
            break;
        }
    }
    if (fileIndex == -1) {
        printf("Error: File not found.\n");
        return;
    }
    Block *current = files[fileIndex].start;
    while (current != NULL) {
        Block *nextBlock = current->next;
        free(current);
        current = nextBlock;
    }
    files[fileIndex].fileName[0] = '\0';
    files[fileIndex].start = NULL;
    files[fileIndex].end = NULL;
    printf("File '%s' deleted successfully.\n", fileName);
}

int main() {
    int choice;
    char fileName[20], data[500];

    while (1) {
        printf("\nLinked File Allocation Simulation\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter file data: ");
                scanf(" %[^\n]", data);
                createFile(fileName, data);
                break;
            case 2:
                printf("Enter file name to read: ");
                scanf("%s", fileName);
                readFile(fileName);
                break;
            case 3:
                printf("Enter file name to delete: ");
                scanf("%s", fileName);
                deleteFile(fileName);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

