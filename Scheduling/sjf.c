#include <stdio.h>

// Function to implement SJF non-preemptive scheduling
void sjf_non_preemptive(int processes[], int arrival_time[], int burst_time[], int n) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0;
    int completed[n]; // To track completed processes

    // Initialize completed array
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    int current_time = 0; // Current time
    int completed_processes = 0; // Number of completed processes

    // Perform scheduling
    while (completed_processes < n) {
        int shortest_job = -1;
        int shortest_time = 99999;

        // Find the shortest job that has arrived
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && !completed[i] && burst_time[i] < shortest_time) {
                shortest_time = burst_time[i];
                shortest_job = i;
            }
        }

        if (shortest_job == -1) {
            current_time++; // If no process is available, move to next time unit
        } else {
            ct[shortest_job] = current_time + burst_time[shortest_job];
            current_time = ct[shortest_job];
            tat[shortest_job] = ct[shortest_job] - arrival_time[shortest_job];
            wt[shortest_job] = tat[shortest_job] - burst_time[shortest_job];
            total_wt += wt[shortest_job];
            total_tat += tat[shortest_job];
            completed[shortest_job] = 1;
            completed_processes++;
        }
    }

    // Display process table
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWait Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], ct[i], tat[i], wt[i]);
    }

    // Calculate average turnaround time and average wait time
    float avg_tat = (float)total_tat / n;
    float avg_wt = (float)total_wt / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Wait Time: %.2f\n", avg_wt);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int arrival_time[n];
    int burst_time[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1; // Process IDs
    }

    sjf_non_preemptive(processes, arrival_time, burst_time, n);

    return 0;
}
