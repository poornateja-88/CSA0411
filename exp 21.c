#include <stdio.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY]; // Memory array

// Function prototypes
void initializeMemory();
void displayMemory();
void allocateMemory(int processId, int size);
void deallocateMemory(int processId);

// Function to initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 indicates unallocated memory
    }
}

// Function to display memory status
void displayMemory() {
    int count = 0;
    printf("\nMemory Status:\n");
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            count++;
            int j = i;
            while (j < MAX_MEMORY && memory[j] == -1) {
                j++;
            }
            printf("Free memory block %d - %d\n", i, j - 1);
            i = j - 1; // Skip to end of free block
        }
    }
    if (count == 0) {
        printf("No free memory available.\n");
    }
}

// Function to allocate memory using worst-fit algorithm
void allocateMemory(int processId, int size) {
    int start = -1;
    int maxBlockSize = -1;
    int currentStart = -1;
    int currentBlockSize = 0;

    // Find the largest free block
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            if (currentBlockSize == 0) currentStart = i;
            currentBlockSize++;
        } else {
            if (currentBlockSize > maxBlockSize) {
                maxBlockSize = currentBlockSize;
                start = currentStart;
            }
            currentBlockSize = 0;
        }
    }

    // Check the last block
    if (currentBlockSize > maxBlockSize) {
        maxBlockSize = currentBlockSize;
        start = currentStart;
    }

    if (maxBlockSize >= size) {
        for (int i = start; i < start + size; i++) {
            memory[i] = processId;
        }
        printf("Allocated memory block %d - %d to Process %d\n", start, start + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
        }
    }
    printf("Memory released by Process %d\n", processId);
}

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
