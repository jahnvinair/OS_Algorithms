#include <stdio.h>

int main() {
    int n, time_quantum, time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[n], burst_time[n], remaining_burst_time[n], completion_time[n], turnaround_time[n], waiting_time[n];

    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        remaining_burst_time[i] = burst_time[i];
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    int remaining_processes = n;
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (remaining_burst_time[i] > 0) {
                if (remaining_burst_time[i] <= time_quantum) {
                    time += remaining_burst_time[i];
                    remaining_burst_time[i] = 0;
                    completion_time[i] = time;
                    remaining_processes--;
                } else {
                    time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                }
            }
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
        total_turnaround_time += turnaround_time[i];
        total_waiting_time += waiting_time[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], turnaround_time[i], waiting_time[i]);
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
