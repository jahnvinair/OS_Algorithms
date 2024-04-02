#include <stdio.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

void sort_processes_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sort_processes_by_priority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Take input from the user
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d:\n", processes[i].id);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }

    sort_processes_by_arrival_time(processes, n);

    int current_time = processes[0].arrival_time;
    int completed = 0;
    int previous_priority = 0;

    while (completed != n) {
        sort_processes_by_priority(processes, n);

        int highest_priority_index = -1;
        int highest_priority = 100;  // Assuming maximum priority is 99

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }

        if (highest_priority_index != -1) {
            processes[highest_priority_index].remaining_time--;
            current_time++;
            previous_priority = processes[highest_priority_index].priority;

            if (processes[highest_priority_index].remaining_time == 0) {
                completed++;
                processes[highest_priority_index].turnaround_time = current_time - processes[highest_priority_index].arrival_time;
                processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
            }
        } else {
            current_time++;
        }
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    printf("       \tTime\tTime\t        \tTime\tTime\n");
    printf("-------\t-------\t-----\t--------\t-------\t----------\n");

    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        printf("%7d\t%7d\t%5d\t%9d\t%7d\t%10d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("-------\t-------\t-----\t--------\t-------\t----------\n");

    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}