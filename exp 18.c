#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

DWORD WINAPI producer(LPVOID arg)
{
    for (int i = 1; i <= MAX_ITEMS; i++)
    {
        while (count == BUFFER_SIZE)
            Sleep(50);   // buffer full ? wait

        buffer[in] = i;
        printf("Produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        Sleep(100);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID arg)
{
    for (int i = 1; i <= MAX_ITEMS; i++)
    {
        while (count == 0)
            Sleep(50);  // buffer empty ? wait

        int item = buffer[out];
        printf("Consumed: %d\n", item);

        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;
        count--;

        Sleep(150);
    }
    return 0;
}

int main()
{
    HANDLE prodThread, consThread;

    prodThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    CloseHandle(prodThread);
    CloseHandle(consThread);

    printf("\nAll work done. Press Enter to exit...");
    getchar();
    getchar();

    return 0;
}
