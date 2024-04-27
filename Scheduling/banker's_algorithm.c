#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Function prototypes
bool isSafe(int available[], int maxm[][3], int allocation[][3], int need[][3], int numProcesses, int numResources);
int findAvailableProcess(int available[], int need[][3], int numProcesses, int numResources);

int main() {
    int numProcesses, numResources;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resource types: ");
    scanf("%d", &numResources);

    int available[numResources];
    printf("Enter the available resources (separated by spaces): ");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    int (*maxm)[numResources] = malloc(numProcesses * numResources * sizeof(int));
    printf("Enter the maximum requirements for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &maxm[i][j]);
        }
    }

    int (*allocation)[numResources] = malloc(numProcesses * numResources * sizeof(int));
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    int (*need)[numResources] = malloc(numProcesses * numResources * sizeof(int));
    // Calculate the need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maxm[i][j] - allocation[i][j];
        }
    }

    if (isSafe(available, maxm, allocation, need, numProcesses, numResources)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is in an unsafe state and may lead to a deadlock.\n");
    }

    free(maxm);
    free(allocation);
    free(need);

    return 0;
}

bool isSafe(int available[], int maxm[][3], int allocation[][3], int need[][3], int numProcesses, int numResources) {
    int work[numResources]; // Work vector
    bool *finish = calloc(numProcesses, sizeof(bool)); // Finish vector
    int safeSequence[numProcesses]; // Safe sequence
    int count = 0; // Counter for safe sequence

    // Copy available resources to work vector
    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    // Find safe sequence
    while (count < numProcesses) {
        bool found = false;
        int processIndex = findAvailableProcess(work, need, numProcesses, numResources);

        if (processIndex != -1) {
            for (int i = 0; i < numResources; i++) {
                work[i] += allocation[processIndex][i];
            }
            safeSequence[count++] = processIndex;
            finish[processIndex] = true;
            found = true;
        }

        if (!found) {
            break;
        }
    }

    // Check if all processes can be finished
    bool isSafe = (count == numProcesses);

    // Print safe sequence
    if (isSafe) {
        printf("Safe sequence: ");
        for (int i = 0; i < numProcesses; i++) {
            printf("%d ", safeSequence[i]); // Print the actual process IDs
        }
        printf("\n");
    }

    free(finish);
    return isSafe;
}

int findAvailableProcess(int available[], int need[][3], int numProcesses, int numResources) {
    for (int i = 0; i < numProcesses; i++) {
        bool canAllocate = true;
        for (int j = 0; j < numResources; j++) {
            if (need[i][j] > available[j]) {
                canAllocate = false;
                break;
            }
        }
        if (canAllocate) {
            return i;
        }
    }
    return -1;
}
