#include <stdio.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY]; // Memory array

// Function prototypes
void initializeMemory();
void displayMemory();
void allocateMemory(int processId, int size);
void deallocateMemory(int processId);

// Initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 indicates free memory
    }
}

// Display memory status
void displayMemory() {
    printf("\nMemory Status:\n");
    int freeBlockFound = 0;
    for (int i = 0; i < MAX_MEMORY;) {
        if (memory[i] == -1) {
            int start = i;
            while (i < MAX_MEMORY && memory[i] == -1) {
                i++;
            }
            int end = i - 1;
            printf("Free memory block: %d - %d\n", start, end);
            freeBlockFound = 1;
        } else {
            i++;
        }
    }
    if (!freeBlockFound) {
        printf("No free memory available.\n");
    }
}

// Allocate memory using worst-fit algorithm
void allocateMemory(int processId, int size) {
    int maxBlockSize = -1;
    int maxStart = -1;
    int currentSize = 0;
    int currentStart = -1;

    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) { // free memory
            if (currentSize == 0) currentStart = i;
            currentSize++;
        } else {
            if (currentSize > maxBlockSize) {
                maxBlockSize = currentSize;
                maxStart = currentStart;
            }
            currentSize = 0;
        }
    }

    // Check last block
    if (currentSize > maxBlockSize) {
        maxBlockSize = currentSize;
        maxStart = currentStart;
    }

    if (maxBlockSize >= size) {
        for (int i = maxStart; i < maxStart + size; i++) {
            memory[i] = processId;
        }
        printf("Allocated memory block %d - %d to Process %d\n", maxStart, maxStart + size - 1, processId);
    } else {
        printf("Memory allocation failed for Process %d\n", processId);
    }
}

// Deallocate memory
void deallocateMemory(int processId) {
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
        }
    }
    printf("Memory released by Process %d\n", processId);
}

// Main function
int main() {
    initializeMemory();

    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    return 0;
}
