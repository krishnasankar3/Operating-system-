#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_RECORD_SIZE 50

typedef struct {
    int id;
    char data[MAX_RECORD_SIZE];
} Record;

void addRecord(Record records[], int *recordCount, int id, char data[]) {
    if(*recordCount >= MAX_RECORDS) {
        printf("Error: Cannot add more records, storage is full.\n");
        return;
    }
    
    records[*recordCount].id = id;
    strncpy(records[*recordCount].data, data, MAX_RECORD_SIZE);
    (*recordCount)++;
    printf("Record added: ID = %d, Data = %s\n", id, data);
}

void readRecords(Record records[], int recordCount) {
    if(recordCount == 0) {
        printf("No records to read.\n");
        return;
    }
    
    printf("Reading records sequentially:\n");
    for(int i = 0; i < recordCount; i++) {
        printf("Record ID: %d, Data: %s\n", records[i].id, records[i].data);
    }
}

int main() {
    Record records[MAX_RECORDS];
    int recordCount = 0;
    int choice, id;
    char data[MAX_RECORD_SIZE];
    
    while(1) {
        printf("\nSequential File Allocation Simulation\n");
        printf("1. Add a Record\n");
        printf("2. Read All Records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter Record ID: ");
                scanf("%d", &id);
                printf("Enter Record Data: ");
                scanf(" %[^\n]", data);  // Read input with spaces
                addRecord(records, &recordCount, id, data);
                break;
                
            case 2:
                readRecords(records, recordCount);
                break;
                
            case 3:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

