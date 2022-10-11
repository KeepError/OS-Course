#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

int compare_processes_fcfs(const void *a, const void *b) {
    Process *a_process = ((Process *) a);
    Process *b_process = ((Process *) b);
    if (a_process->arrival_time > b_process->arrival_time) return 1;
    if (a_process->arrival_time < b_process->arrival_time) return -1;
    return 0;
}

void fcfs_algorithm(Process *processes, int n) {
    qsort(processes, n, sizeof(Process), compare_processes_fcfs);
    int last_exit_time = 0;
    for (int i = 0; i < n; ++i) {
        if (last_exit_time <= processes[i].arrival_time)
            processes[i].waiting_time = 0;
        else
            processes[i].waiting_time = last_exit_time - processes[i].arrival_time;
        processes[i].completion_time = processes[i].arrival_time + processes[i].waiting_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        last_exit_time = processes[i].completion_time;

        printf("[Process #%d] Arrival time: %d, Burst time: %d, Waiting time: %d, Completion time: %d, Turnaround time: %d\n",
               i, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time,
               processes[i].completion_time, processes[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);
    Process processes[n];
    for (int i = 0; i < n; ++i) {
        printf("Arrival time and burst time for process %d: ", i);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }
    fcfs_algorithm(processes, n);

    int total_turnaround_time, total_waiting_time;
    for (int i = 0; i < n; ++i) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }
    printf("Average turnaround time: %f\n", (double) total_turnaround_time / n);
    printf("Average waiting time: %f\n", (double) total_waiting_time / n);

    return EXIT_SUCCESS;
}