#include <stdio.h>

struct Process {
    int pid; // Process ID
    int arrivalTime;
    int burstTime;
    int priority; // Lower number means higher priority
    int waitingTime;
    int turnaroundTime;
    int completed; // Flag to check if the process is completed
};

// Function to find the waiting and turnaround time for each process
void findWaitingAndTurnaroundTime(struct Process proc[], int n) {
    int time = 0, completed = 0;
    while (completed < n) {
        int highestPriority = 1e9, highestIndex = -1;

        // Find the process with the highest priority among those that have arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= time && !proc[i].completed && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                highestIndex = i;
            }
        }

        if (highestIndex == -1) {
            time++; // If no process is found, increase time and continue
            continue;
        }

        // Update time and calculate waiting and turnaround times
        time += proc[highestIndex].burstTime;
        proc[highestIndex].waitingTime = time - proc[highestIndex].arrivalTime - proc[highestIndex].burstTime;
        proc[highestIndex].turnaroundTime = time - proc[highestIndex].arrivalTime;
        proc[highestIndex].completed = 1;
        completed++;
    }
}

// Function to calculate average times and print details
void findAverageTime(struct Process proc[], int n) {
    findWaitingAndTurnaroundTime(proc, n);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].priority, proc[i].waitingTime, proc[i].turnaroundTime);
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
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
        proc[i].completed = 0; // Initially, no process is completed
    }

    findAverageTime(proc, n);

    return 0;
}

