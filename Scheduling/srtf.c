#include <stdio.h>

void srtf(int processes[], int arrival_time[], int burst_time[], int n) {
    int remaining_time[n];
    int completion_time[n];
    int current_time = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        completion_time[i] = 0;
    }

    while (completed != n) {
        int shortest_job = -1;
        int shortest_time = 99999;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] < shortest_time && remaining_time[i] > 0) {
                shortest_time = remaining_time[i];
                shortest_job = i;
            }
        }

        if (shortest_job == -1) {
            current_time++;
        } else {
            remaining_time[shortest_job]--;
            current_time++;

            if (remaining_time[shortest_job] == 0) {
                completed++;
                completion_time[shortest_job] = current_time;
            }
        }
    }

    // Calculate turnaround time and wait time
    int total_turnaround_time = 0, total_wait_time = 0;
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWait Time\n");
    for (int i = 0; i < n; i++) {
        int turnaround_time = completion_time[i] - arrival_time[i];
        int wait_time = turnaround_time - burst_time[i];
        total_turnaround_time += turnaround_time;
        total_wait_time += wait_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i], arrival_time[i], burst_time[i], completion_time[i], turnaround_time, wait_time);
    }

    // Calculate and display average turnaround time and average wait time
    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_wait_time = (float)total_wait_time / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Wait Time: %.2f\n", avg_wait_time);
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

    srtf(processes, arrival_time, burst_time, n);

    return 0;
}
