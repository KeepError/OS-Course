#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    bool finished;
} Process;


void sjf_algorithm(Process *processes, int n) {
    int processes_finished = 0;
    int current_time = 0;
    int to_finish;
    while (processes_finished < n) {
        to_finish = -1;
        for (int i = 0; i < n; i++) {
            if (!processes[i].finished && processes[i].arrival_time <= current_time &&
                (to_finish == -1 || processes[i].burst_time < processes[to_finish].burst_time))
                to_finish = i;
        }
        if (to_finish == -1)
            continue;
        processes[to_finish].waiting_time = current_time - processes[to_finish].arrival_time;
        processes[to_finish].completion_time = current_time + processes[to_finish].burst_time;
        processes[to_finish].turnaround_time = processes[to_finish].waiting_time + processes[to_finish].burst_time;
        current_time += processes[to_finish].burst_time - 1;

        printf("[Process #%d] Arrival time: %d, Burst time: %d, Waiting time: %d, Completion time: %d, Turnaround time: %d\n",
               to_finish, processes[to_finish].arrival_time, processes[to_finish].burst_time,
               processes[to_finish].waiting_time,
               processes[to_finish].completion_time, processes[to_finish].turnaround_time);

        processes[to_finish].finished = true;
        processes_finished++;
        current_time++;
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
    sjf_algorithm(processes, n);

    int total_turnaround_time, total_waiting_time;
    for (int i = 0; i < n; ++i) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }
    printf("Average turnaround time: %f\n", (double) total_turnaround_time / n);
    printf("Average waiting time: %f\n", (double) total_waiting_time / n);

    return EXIT_SUCCESS;
}