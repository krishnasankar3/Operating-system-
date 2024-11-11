#include <stdio.h>

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time of the process
    int remainingTime;  // Remaining time for the process to complete
    int waitingTime;    // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
};

void findWaitingAndTurnaroundTime(struct Process proc[], int n, int quantum) {
    int time = 0;  // Current time
    int completed = 0;

    while (completed < n) {
        int allIdle = 1;  // Flag to check if all processes are idle

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= time && proc[i].remainingTime > 0) {
                allIdle = 0;  // At least one process is available for execution

                if (proc[i].remainingTime > quantum) {
                    time += quantum;
                    proc[i].remainingTime -= quantum;
                } else {
                    time += proc[i].remainingTime;
                    proc[i].waitingTime = time - proc[i].arrivalTime - proc[i].burstTime;
                    proc[i].turnaroundTime = time - proc[i].arrivalTime;
                    proc[i].remainingTime = 0;
                    completed++;
                }
            }
        }

        // If all processes are idle, increment time to the next arrival
        if (allIdle) time++;
    }
}

void findAverageTime(struct Process proc[], int n, int quantum) {
    findWaitingAndTurnaroundTime(proc, n, quantum);

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
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;  // Initialize remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    findAverageTime(proc, n, quantum);

    return 0;
}

