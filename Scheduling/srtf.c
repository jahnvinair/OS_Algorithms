#include <stdio.h>
#include <limits.h> // for INT_MAX

struct Process {
  int pid; // Process ID
  int arrival_time;
  int burst_time;
  int remaining_time;
};

int find_shortest_remaining_time(struct Process processes[], int n, int current_time) {
  int index = -1, min_remaining_time = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_remaining_time && processes[i].remaining_time > 0) {
      min_remaining_time = processes[i].remaining_time;
      index = i;
    }
  }
  return index;
}

void SRTF(struct Process processes[], int n) {
  int time = 0, completed = 0;
  int waiting_time[n], turnaround_time[n];

  for (int i = 0; i < n; i++) {
    waiting_time[i] = 0;
    turnaround_time[i] = 0;
    processes[i].remaining_time = processes[i].burst_time;
  }

  while (completed != n) {
    int shortest_process = find_shortest_remaining_time(processes, n, time);

    if (shortest_process == -1) {
      // No process ready to execute (all haven't arrived yet or finished)
      time++;
      continue;
    }

    processes[shortest_process].remaining_time--;

    if (processes[shortest_process].remaining_time == 0) {
      completed++;
      turnaround_time[shortest_process] = time - processes[shortest_process].arrival_time;
      waiting_time[shortest_process] = turnaround_time[shortest_process] - processes[shortest_process].burst_time;
    }

    // Context switching overhead (optional)
    time++;
  }

  // Calculate average waiting and turnaround time
  float avg_waiting_time = 0, avg_turnaround_time = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting_time += waiting_time[i];
    avg_turnaround_time += turnaround_time[i];
  }
  avg_waiting_time /= n;
  avg_turnaround_time /= n;

  printf("Process ID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, turnaround_time[i], waiting_time[i]);
  }
  printf("Average Waiting Time: %.2f\n", avg_waiting_time);
  printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  struct Process processes[n];
  for (int i = 0; i < n; i++) {
    printf("Enter process ID, arrival time, and burst time for process %d: ", i + 1);
    scanf("%d %d %d", &processes[i].pid, &processes[i].arrival_time, &processes[i].burst_time);
  }

  SRTF(processes, n);
  return 0;
}
