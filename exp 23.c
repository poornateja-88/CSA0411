#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY];

void initializeMemory()
{
    int i;
    for (i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1;
    }
}

void displayMemory()
{
    int i, j;
    int foundFree = 0;

    printf("\nMemory Status:\n");

    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            foundFree = 1;
            j = i;
            while (j < MAX_MEMORY && memory[j] == -1) {
                j++;
            }
            printf("Free memory block: %d - %d\n", i, j - 1);
            i = j - 1;
        }
    }

    if (!foundFree) {
        printf("No free memory available.\n");
    }
}

void allocateMemory(int processId, int size)
{
    int start = -1;
    int blockSize = 0;
    int i;

    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            if (blockSize == 0) {
                start = i;
            }
            blockSize++;
        } else {
            blockSize = 0;
        }

        if (blockSize >= size) {
            break;
        }
    }

    if (blockSize >= size) {
        for (i = start; i < start + size; i++) {
            memory[i] = processId;
        }
        printf("\nAllocated block %d - %d to Process %d\n",
               start, start + size - 1, processId);
    } else {
        printf("\nAllocation failed for Process %d (Not enough free space)\n", processId);
    }
}

void deallocateMemory(int processId)
{
    int i;
    int released = 0;

    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
            released = 1;
        }
    }

    if (released)
        printf("\nMemory released by Process %d\n", processId);
    else
        printf("\nProcess %d had no allocated memory\n", processId);
}

int main()
{
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

    system("pause");   // <-- This fixes your output window problem

    return 0;
}
