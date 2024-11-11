#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES] = {3, 3, 2}; // Available instances of each resource
int maximum[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3}, 
    {3, 2, 2}, 
    {9, 0, 2}, 
    {2, 2, 2}, 
    {4, 3, 3}
};
int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0}, 
    {2, 0, 0}, 
    {3, 0, 2}, 
    {2, 1, 1}, 
    {0, 0, 2}
};

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    
    // Initialize work array with available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    // Try to find a safe sequence
    for (int count = 0; count < MAX_PROCESSES; count++) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int can_finish = 1;
                // Check if process can finish
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (maximum[i][j] - allocation[i][j] > work[j]) {
                        can_finish = 0;
                        break;
                    }
                }
                if (can_finish) {
                    // Process can finish, update work array
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    found = 1;
                    break;
                }
            }
        }
        if (!found) {
            return 0; // Not in safe state
        }
    }
    return 1; // In safe state
}

int request_resources(int process_num, int request[]) {
    // Check if request is valid
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > available[i] || request[i] > (maximum[process_num][i] - allocation[process_num][i])) {
            return 0; // Invalid request
        }
    }

    // Temporarily allocate resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_num][i] += request[i];
    }

    // Check if system is in safe state
    if (is_safe()) {
        return 1; // Request granted
    } else {
        // Rollback if not safe
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_num][i] -= request[i];
        }
        return 0; // Request denied
    }
}

int main() {
    int process_num, request[MAX_RESOURCES];
    
    // Get process number and resource request
    printf("Enter process number (0 to 4): ");
    scanf("%d", &process_num);
    printf("Enter resource request (e.g., 0 1 0): ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }

    // Request resources for the process
    if (request_resources(process_num, request)) {
        printf("Request granted.\n");
    } else {
        printf("Request denied. System is not in safe state.\n");
    }

    return 0;
}

