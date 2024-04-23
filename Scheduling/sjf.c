#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[], int n, int bt[], int tat[], int wt[]) {
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("\nAverage turnaround time = %.2f", (float)total_tat / (float)n);
}

void sortProcesses(int processes[], int n, int bt[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                int temp_process = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp_process;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n];
    int burst_time[n];
    int waiting_time[n];
    int turnaround_time[n];
    int arrival_time[n];
    
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        arrival_time[i] = 0;
    }
    
    sortProcesses(processes, n, burst_time);
    findWaitingTime(processes, n, burst_time, waiting_time, arrival_time);
    findTurnAroundTime(processes, n, burst_time, waiting_time, turnaround_time);
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time");
    
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t\t%d\t\t%d\t\t%d", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    
    int total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += waiting_time[i];
    }
    
    printf("\n\nAverage waiting time = %.2f", (float)total_wt / (float)n);
    findAvgTime(processes, n, burst_time, turnaround_time, waiting_time);
    
    return 0;
}
