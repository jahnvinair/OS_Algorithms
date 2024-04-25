#include <stdio.h>

void priority_preemptive(int n, int processes[], int arrival_time[], int burst_time[], int priority[]) {
    int remaining_time[n];
    int completion_time[n];
    int turnaround_time[n];
    int wait_time[n];
    int current_time = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    while (completed != n) {
        int highest_priority = 9999;
        int highest_priority_process = -1;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0 && priority[i] < highest_priority) {
                highest_priority = priority[i];
                highest_priority_process = i;
            }
        }

        if (highest_priority_process == -1) {
            current_time++; // If no process is available, move to next time unit
        } else {
            remaining_time[highest_priority_process]--;

            if (remaining_time[highest_priority_process] == 0) {
                completed++;
                completion_time[highest_priority_process] = current_time + 1;
                turnaround_time[highest_priority_process] = completion_time[highest_priority_process] - arrival_time[highest_priority_process];
                wait_time[highest_priority_process] = turnaround_time[highest_priority_process] - burst_time[highest_priority_process];
            }
            current_time++;
        }
    }

    // Display process table
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWait Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", processes[i], arrival_time[i], burst_time[i], priority[i], completion_time[i], turnaround_time[i], wait_time[i]);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int arrival_time[n];
    int burst_time[n];
    int priority[n];

    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Process %d Priority: ", i + 1);
        scanf("%d", &priority[i]);
        processes[i] = i + 1; // Process IDs
    }

    priority_preemptive(n, processes, arrival_time, burst_time, priority);

    return 0;
}
