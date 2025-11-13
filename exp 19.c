#include <windows.h>
#include <process.h> // for _beginthreadex
#include <stdio.h>

#define NUM_ITERATIONS 1000000

// Shared variable
volatile long counter = 0;

// Mutex for synchronization
HANDLE mutex;

// Thread function
unsigned __stdcall ThreadFunction(void* param)
{
    for (long i = 0; i < NUM_ITERATIONS; i++)
    {
        WaitForSingleObject(mutex, INFINITE); // lock mutex
        counter++;                             // increment shared variable
        ReleaseMutex(mutex);                   // unlock mutex
    }
    return 0;
}

int main(void)
{
    HANDLE thread1, thread2;
    unsigned threadID1, threadID2;

    // Create mutex
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL)
    {
        printf("Failed to create mutex. Error: %lu\n", GetLastError());
        return 1;
    }

    // Create threads using _beginthreadex
    thread1 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, 0, &threadID1);
    thread2 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, 0, &threadID2);

    if (!thread1 || !thread2)
    {
        printf("Failed to create threads.\n");
        CloseHandle(mutex);
        return 1;
    }

    // Wait for threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Clean up
    CloseHandle(thread1);
    CloseHandle(thread2);
    CloseHandle(mutex);

    // Print final counter value
    printf("Final counter value: %ld\n", counter);

    system("pause");
    return 0;
}
