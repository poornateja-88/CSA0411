#include <stdio.h>
#include <stdlib.h>

/* Print result: shows process number, process size and whether allocated */
void print_allocation(int alloc[], int processes[], int n)
{
    printf("\nProcess No.\tProcess Size\tStatus\n");
    for (int i = 0; i < n; ++i) {
        if (alloc[i] != -1)
            printf("   %2d\t\t    %2d\t\tAllocated (size %d)\n", i + 1, processes[i], alloc[i]);
        else
            printf("   %2d\t\t    %2d\t\tNot Allocated (must wait)\n", i + 1, processes[i]);
    }
}

/* First Fit: for each process, choose the first partition that fits */
void firstFit(int partitions[], int pCount, int processes[], int rCount)
{
    int *available = (int *)malloc(pCount * sizeof(int));
    int *allocation = (int *)malloc(rCount * sizeof(int));
    if (!available || !allocation) {
        printf("Memory allocation failed.\n");
        free(available);
        free(allocation);
        return;
    }

    for (int i = 0; i < pCount; ++i) available[i] = partitions[i];
    for (int i = 0; i < rCount; ++i) allocation[i] = -1;

    for (int i = 0; i < rCount; ++i) {
        for (int j = 0; j < pCount; ++j) {
            if (available[j] >= processes[i]) {
                allocation[i] = processes[i];    /* store process size allocated */
                available[j] -= processes[i];   /* reduce available */
                break;
            }
        }
    }

    printf("\n--- First Fit Allocation ---\n");
    print_allocation(allocation, processes, rCount);

    free(available);
    free(allocation);
}

/* Best Fit: choose smallest partition that is >= process size */
void bestFit(int partitions[], int pCount, int processes[], int rCount)
{
    int *available = (int *)malloc(pCount * sizeof(int));
    int *allocation = (int *)malloc(rCount * sizeof(int));
    if (!available || !allocation) {
        printf("Memory allocation failed.\n");
        free(available);
        free(allocation);
        return;
    }

    for (int i = 0; i < pCount; ++i) available[i] = partitions[i];
    for (int i = 0; i < rCount; ++i) allocation[i] = -1;

    for (int i = 0; i < rCount; ++i) {
        int bestIdx = -1;
        for (int j = 0; j < pCount; ++j) {
            if (available[j] >= processes[i]) {
                if (bestIdx == -1 || available[j] < available[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = processes[i];
            available[bestIdx] -= processes[i];
        }
    }

    printf("\n--- Best Fit Allocation ---\n");
    print_allocation(allocation, processes, rCount);

    free(available);
    free(allocation);
}

/* Worst Fit: choose largest partition that is >= process size */
void worstFit(int partitions[], int pCount, int processes[], int rCount)
{
    int *available = (int *)malloc(pCount * sizeof(int));
    int *allocation = (int *)malloc(rCount * sizeof(int));
    if (!available || !allocation) {
        printf("Memory allocation failed.\n");
        free(available);
        free(allocation);
        return;
    }

    for (int i = 0; i < pCount; ++i) available[i] = partitions[i];
    for (int i = 0; i < rCount; ++i) allocation[i] = -1;

    for (int i = 0; i < rCount; ++i) {
        int worstIdx = -1;
        for (int j = 0; j < pCount; ++j) {
            if (available[j] >= processes[i]) {
                if (worstIdx == -1 || available[j] > available[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = processes[i];
            available[worstIdx] -= processes[i];
        }
    }

    printf("\n--- Worst Fit Allocation ---\n");
    print_allocation(allocation, processes, rCount);

    free(available);
    free(allocation);
}

int main()
{
    int pCount, rCount;

    printf("Number of memory partitions: ");
    if (scanf("%d", &pCount) != 1 || pCount <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Number of processes: ");
    if (scanf("%d", &rCount) != 1 || rCount <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    if (pCount > 100 || rCount > 100) {
        printf("Too many partitions/processes (max 100).\n");
        return 1;
    }

    int *partitions = (int *)malloc(pCount * sizeof(int));
    int *processes = (int *)malloc(rCount * sizeof(int));
    if (!partitions || !processes) {
        printf("Memory allocation failed.\n");
        free(partitions);
        free(processes);
        return 1;
    }

    printf("Enter the memory partitions (sizes):\n");
    for (int i = 0; i < pCount; ++i) {
        printf(" Partition %d: ", i + 1);
        if (scanf("%d", &partitions[i]) != 1) partitions[i] = 0;
        if (partitions[i] < 0) partitions[i] = 0;
    }

    printf("Enter the process sizes:\n");
    for (int i = 0; i < rCount; ++i) {
        printf(" Process %d: ", i + 1);
        if (scanf("%d", &processes[i]) != 1) processes[i] = 0;
        if (processes[i] < 0) processes[i] = 0;
    }

    int choice;
    printf("\nChoose Allocation Strategy:\n");
    printf(" 1. First Fit\n 2. Best Fit\n 3. Worst Fit\nEnter your choice: ");
    if (scanf("%d", &choice) != 1) choice = 0;

    switch (choice) {
        case 1:
            firstFit(partitions, pCount, processes, rCount);
            break;
        case 2:
            bestFit(partitions, pCount, processes, rCount);
            break;
        case 3:
            worstFit(partitions, pCount, processes, rCount);
            break;
        default:
            printf("Invalid choice. Running all three for demonstration.\n");
            firstFit(partitions, pCount, processes, rCount);
            bestFit(partitions, pCount, processes, rCount);
            worstFit(partitions, pCount, processes, rCount);
            break;
    }

    free(partitions);
    free(processes);

    /* keep console open in Dev-C++ until Enter pressed */
    printf("\nPress Enter to exit...");
    getchar(); /* consume newline left by scanf */
    getchar();

    return 0;
}
