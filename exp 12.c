#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_PHILOSOPHERS 5

HANDLE chopsticks[NUM_PHILOSOPHERS];
HANDLE philosophers[NUM_PHILOSOPHERS];
DWORD threadIDs[NUM_PHILOSOPHERS];
int ids[NUM_PHILOSOPHERS];

// Thread function for each philosopher
DWORD WINAPI philosopherLifeCycle(LPVOID arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    int i;

    for (i = 0; i < 3; i++)   // each philosopher eats 3 times
    {
        printf("Philosopher %d is thinking...\n", id);
        Sleep(500 + rand() % 1000);

        // Pick up chopsticks
        WaitForSingleObject(chopsticks[left], INFINITE);
        WaitForSingleObject(chopsticks[right], INFINITE);

        printf("Philosopher %d is eating...\n", id);
        Sleep(500 + rand() % 1000);

        // Put down chopsticks
        ReleaseSemaphore(chopsticks[left], 1, NULL);
        ReleaseSemaphore(chopsticks[right], 1, NULL);

        printf("Philosopher %d finished eating %d times.\n", id, i + 1);
    }

    printf("Philosopher %d is done dining.\n", id);
    return 0;
}

int main(void)
{
    int i;
    srand((unsigned int)GetTickCount());

    // Initialize semaphores
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        chopsticks[i] = CreateSemaphore(NULL, 1, 1, NULL);
        if (chopsticks[i] == NULL)
        {
            printf("Error creating semaphore %d\n", i);
            return 1;
        }
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        philosophers[i] = CreateThread(NULL, 0, philosopherLifeCycle, &ids[i], 0, &threadIDs[i]);
        if (philosophers[i] == NULL)
        {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for philosophers to finish
    WaitForMultipleObjects(NUM_PHILOSOPHERS, philosophers, TRUE, INFINITE);

    // Close handles
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        CloseHandle(chopsticks[i]);
        CloseHandle(philosophers[i]);
    }

    printf("\nAll philosophers have finished dining.\n");
    printf("Press Enter to exit...");
    getchar();

    return 0;
}
