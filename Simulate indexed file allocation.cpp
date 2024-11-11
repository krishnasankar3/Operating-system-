#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100     // Maximum number of data blocks
#define MAX_FILES 10       // Maximum number of files
#define BLOCK_SIZE 50      // Maximum size of each block

typedef struct {
    int indexBlock[MAX_BLOCKS]; // Index block with pointers to data blocks
    int blockCount;             // Number of blocks the file occupies
    char fileName[20];          // File name
} File;

File files[MAX_FILES];
char dataBlocks[MAX_BLOCKS][BLOCK_SIZE];  // Data blocks to hold content
int blockUsed[MAX_BLOCKS] = {0};          // Track used blocks (0 = free, 1 = used)

int findFreeBlock() {
    for(int i = 0; i < MAX_BLOCKS; i++) {
        if(blockUsed[i] == 0) {
            blockUsed[i] = 1;
            return i;
        }
    }
    return -1; // No free block found
}

void createFile(char *fileName, char *data) {
    int fileIndex = -1;
    for(int i = 0; i < MAX_FILES; i++) {
        if(strlen(files[i].fileName) == 0) {  // Check for an empty file slot
            fileIndex = i;
            break;
        }
    }

    if(fileIndex == -1) {
        printf("Error: Maximum file limit reached.\n");
        return;
    }

    // Initialize file metadata
    strncpy(files[fileIndex].fileName, fileName, 20);
    files[fileIndex].blockCount = 0;

    // Split data into blocks and allocate
    int dataLength = strlen(data);
    for(int i = 0; i < dataLength; i += BLOCK_SIZE) {
        int blockIndex = findFreeBlock();
        if(blockIndex == -1) {
            printf("Error: Not enough memory to store the file.\n");
            files[fileIndex].blockCount = 0;
            return;
        }

        strncpy(dataBlocks[blockIndex], data + i, BLOCK_SIZE); // Copy data to the block
        files[fileIndex].indexBlock[files[fileIndex].blockCount++] = blockIndex;
    }

    printf("File '%s' created successfully using %d blocks.\n", fileName, files[fileIndex].blockCount);
}

void readFile(char *fileName) {
    int fileIndex = -1;
    for(int i = 0; i < MAX_FILES; i++) {
        if(strcmp(files[i].fileName, fileName) == 0) {
            fileIndex = i;
            break;
        }
    }

    if(fileIndex == -1) {
        printf("Error: File not found.\n");
        return;
    }

    printf("Reading file '%s':\n", fileName);
    for(int i = 0; i < files[fileIndex].blockCount; i++) {
        int blockIndex = files[fileIndex].indexBlock[i];
        printf("%s", dataBlocks[blockIndex]);
    }
    printf("\n");
}

void deleteFile(char *fileName) {
    int fileIndex = -1;
    for(int i = 0; i < MAX_FILES; i++) {
        if(strcmp(files[i].fileName, fileName) == 0) {
            fileIndex = i;
            break;
        }
    }

    if(fileIndex == -1) {
        printf("Error: File not found.\n");
        return;
    }

    // Free the data blocks
    for(int i = 0; i < files[fileIndex].blockCount; i++) {
        int blockIndex = files[fileIndex].indexBlock[i];
        blockUsed[blockIndex] = 0; // Mark block as free
    }

    // Clear file entry
    files[fileIndex].fileName[0] = '\0';
    files[fileIndex].blockCount = 0;

    printf("File '%s' deleted successfully.\n", fileName);
}

int main() {
    int choice;
    char fileName[20], data[500];

    while(1) {
        printf("\nIndexed File Allocation Simulation\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter file data: ");
                scanf(" %[^\n]", data);  // Read entire line of data with spaces
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

