#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;

    int remain_time;
} Process;

typedef struct {
    int data[512];
    int length;
} Queue;


void move_queue(Queue *queue) {
    // Move first element to end of queue
    int temp = queue->data[0];
    for (int i = 1; i < queue->length; ++i) {
        queue->data[i - 1] = queue->data[i];
    }
    queue->data[queue->length - 1] = temp;
}

void add_queue(Queue *queue, int element) {
    // Add element to end of queue
    queue->data[queue->length] = element;
    queue->length += 1;
}

int pop_queue(Queue *queue) {
    // Remove first element from queue and return it
    if (queue->length <= 0) return -1;
    int result = queue->data[0];
    move_queue(queue);
    queue->length -= 1;
    return result;
}

bool in_queue(Queue *queue, int el) {
    for (int i = 0; i < queue->length; ++i) {
        if (queue->data[i] == el) return true;
    }
    return false;
}


void round_robin_algorithm(Process *processes, int n, int q) {
    Queue *queue = malloc(sizeof(Queue));

    int processes_finished = 0;
    int current_time = 0;
    int remain_executing = 0;
    int currently_executing = -1;

    while (processes_finished < n) {

        for (int i = 0; i < n; i++) {
            if (currently_executing == i) continue;
            if (in_queue(queue, i) && processes[i].remain_time > 0) {
                // Process waiting
                processes[i].waiting_time += 1;
            }
            if (!in_queue(queue, i) && processes[i].arrival_time <= current_time && processes[i].remain_time > 0) {
                // Process should be added to queue
                add_queue(queue, i);
            }
        }

        if (remain_executing > 0) { // If executing process
            remain_executing -= 1;
            processes[currently_executing].remain_time -= 1;
            if (remain_executing == 0) { // If process executed
                if (processes[currently_executing].remain_time == 0) {

                    processes[currently_executing].completion_time = current_time;
                    processes[currently_executing].turnaround_time =
                            processes[currently_executing].waiting_time + processes[currently_executing].burst_time;
                    Process current = processes[currently_executing];
                    processes_finished++;
                    printf("[Process #%d] Arrival time: %d, Burst time: %d, Waiting time: %d, Completion time: %d, Turnaround time: %d\n",
                           currently_executing, current.arrival_time, current.burst_time,
                           current.waiting_time,
                           current.completion_time, current.turnaround_time);

                } else {
                    add_queue(queue, currently_executing);
                }
                currently_executing = -1;
            }
        }

        current_time++;

        // If currently executing process
        if (remain_executing > 0) continue;

        int el_i = pop_queue(queue);
        if (el_i == -1) continue;

        if (processes[el_i].remain_time <= q) {
            remain_executing = processes[el_i].remain_time;
        } else {
            remain_executing = q;
        }
        currently_executing = el_i;
    }
}

int main() {
    int q;
    printf("Time quantum: ");
    scanf("%d", &q);

    int n;
    printf("Number of processes: ");
    scanf("%d", &n);
    Process processes[n];
    for (int i = 0; i < n; ++i) {
        printf("Arrival time and burst time for process %d: ", i);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remain_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
    }
    round_robin_algorithm(processes, n, q);

    int total_turnaround_time, total_waiting_time;
    for (int i = 0; i < n; ++i) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }
    printf("Average turnaround time: %f\n", (double) total_turnaround_time / n);
    printf("Average waiting time: %f\n", (double) total_waiting_time / n);

    return EXIT_SUCCESS;
}