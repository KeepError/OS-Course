#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RESOURCES 3
#define PROCESSES 5
#define FILENAME "input.txt"

bool is_process_suitable(const int *resource_availability, int **request_matrix, int process) {
    for (int resource = 0; resource < RESOURCES; ++resource) {
        if (resource_availability[resource] < request_matrix[process][resource]) return false;
    }
    return true;
}

int proceed_next_process(int *resource_total, int *resource_availability, int **allocation_matrix, int **request_matrix,
                         const int *terminated_resources) {
    // returns process if found next process else -1
    for (int process = 0; process < PROCESSES; ++process) {
        if (terminated_resources[process] == 1) continue;
        if (!is_process_suitable(resource_availability, request_matrix, process)) continue;

        for (int j = 0; j < RESOURCES; ++j) {
            resource_availability[j] += allocation_matrix[process][j];
        }
        return process;
    }
    return -1;
}

bool check_for_deadlock(int *resource_total, int *resource_availability, int **allocation_matrix, int **request_matrix) {
    int *terminated_processes = malloc(sizeof(int) * PROCESSES);
    for (int i = 0; i < PROCESSES; ++i) {
        terminated_processes[i] = 0;
    }
    for (int i = 0; i < PROCESSES; ++i) {
        int process = proceed_next_process(resource_total, resource_availability, allocation_matrix, request_matrix,
                                           terminated_processes);
        if (process != -1) {
            printf("P%d terminated\n", process);
        } else {
            printf("Deadlocked processes: ");
            for (int process = 0; process < PROCESSES; ++process) {
                if (terminated_processes[process] == 0) printf("%d ", process);
            }
            printf("\n");
            return true;
        }
        terminated_processes[process] = 1;
    }
    printf("Deadlock not detected\n");
    return false;
}

int main() {
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        return EXIT_FAILURE;
    }

    int *resource_total = malloc(sizeof(int) * RESOURCES);
    for (int i = 0; i < RESOURCES; ++i) {
        fscanf(file, "%d", &resource_total[i]);
    }

    int *resource_availability = malloc(sizeof(int) * RESOURCES);
    for (int i = 0; i < RESOURCES; ++i) {
        fscanf(file, "%d", &resource_availability[i]);
    }

    int **allocation_matrix = malloc(sizeof(int *) * PROCESSES);
    for (int i = 0; i < PROCESSES; ++i) {
        allocation_matrix[i] = malloc(sizeof(int) * RESOURCES);
        for (int j = 0; j < RESOURCES; ++j) {
            fscanf(file, "%d", &allocation_matrix[i][j]);
        }
    }

    int **request_matrix = malloc(sizeof(int *) * PROCESSES);
    for (int i = 0; i < PROCESSES; ++i) {
        request_matrix[i] = malloc(sizeof(int) * RESOURCES);
        for (int j = 0; j < RESOURCES; ++j) {
            fscanf(file, "%d", &request_matrix[i][j]);
        }
    }

    check_for_deadlock(resource_total, resource_availability, allocation_matrix, request_matrix);

    return EXIT_SUCCESS;
}