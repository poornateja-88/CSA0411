#include <windows.h>
#include <stdio.h>

#define NUM_ITERATIONS 10

// Shared data
int data = 0;
int readersCount = 0;

// Synchronization objects
HANDLE mutex;       // protects readersCount
HANDLE writeBlock;  // ensures writers exclusive access

DWORD WINAPI Reader(LPVOID param)
{
    int i;
    for (i = 0; i < NUM_ITERATIONS; i++)
    {
        // Entry section
        WaitForSingleObject(mutex, INFINITE);
        readersCount++;
        if (readersCount == 1) {
            WaitForSingleObject(writeBlock, INFINITE); // first reader blocks writers
        }
        ReleaseMutex(mutex);

        // Reading section
        printf("Reader reads data: %d\n", data);
        Sleep(100); // simulate reading time

        // Exit section
        WaitForSingleObject(mutex, INFINITE);
        readersCount--;
        if (readersCount == 0) {
            ReleaseSemaphore(writeBlock, 1, NULL); // last reader allows writers
        }
        ReleaseMutex(mutex);

        Sleep(50); // optional pause between reads
    }
    return 0;
}

DWORD WINAPI Writer(LPVOID param)
{
    int i;
    for (i = 0; i < NUM_ITERATIONS; i++)
    {
        WaitForSingleObject(writeBlock, INFINITE); // exclusive access

        // Writing section
        data++;
        printf("Writer writes data: %d\n", data);
        Sleep(150); // simulate writing time

        ReleaseSemaphore(writeBlock, 1, NULL);

        Sleep(50); // optional pause between writes
    }
    return 0;
}

int main()
{
    HANDLE readerThread, writerThread;

    // Create synchronization objects
    mutex = CreateMutex(NULL, FALSE, NULL);          // mutex unlocked
    writeBlock = CreateSemaphore(NULL, 1, 1, NULL);  // initially available

    if (!mutex || !writeBlock) {
        printf("Failed to create synchronization objects.\n");
        return 1;
    }

    // Create threads
    readerThread = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
    writerThread = CreateThread(NULL, 0, Writer, NULL, 0, NULL);

    if (!readerThread || !writerThread) {
        printf("Failed to create threads.\n");
        return 1;
    }

    // Wait for threads to finish
    WaitForSingleObject(readerThread, INFINITE);
    WaitForSingleObject(writerThread, INFINITE);

    // Cleanup
    CloseHandle(readerThread);
    CloseHandle(writerThread);
    CloseHandle(mutex);
    CloseHandle(writeBlock);

    printf("All reading and writing finished.\n");

    system("pause");
    return 0;
}
