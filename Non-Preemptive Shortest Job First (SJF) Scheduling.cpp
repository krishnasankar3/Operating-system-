#include <stdio.h>

struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time of the process
    int burstTime;     // Burst time of the process
    int waitingTime;   // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
    int completed;     // Flag to check if the process is completed
};

// Function to find the waiting and turnaround times for each process
void findWaitingAndTurnaroundTime(struct Process proc[], int n) {
    int time = 0, completed = 0;
    
    while (completed < n) {
        int shortestIndex = -1;
        int shortestBurst = 1e9; // Set to a large value initially

        // Find the process with the shortest burst time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= time && !proc[i].completed && proc[i].burstTime < shortestBurst) {
                shortestBurst = proc[i].burstTime;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1) {
            time++; // If no process is found, increment time and continue
            continue;
        }

        // Update time and mark the selected process as completed
        time += proc[shortestIndex].burstTime;
        proc[shortestIndex].waitingTime = time - proc[shortestIndex].arrivalTime - proc[shortestIndex].burstTime;
        proc[shortestIndex].turnaroundTime = time - proc[shortestIndex].arrivalTime;
        proc[shortestIndex].completed = 1;
        completed++;
    }
}

// Function to calculate average waiting and turnaround times
void findAverageTime(struct Process proc[], int n) {
    findWaitingAndTurnaroundTime(proc, n);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time = %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].completed = 0; // Initially, no process is completed
    }

    findAverageTime(proc, n);

    return 0;
}

