#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Function executed by threads
DWORD WINAPI threadFunction(LPVOID arg) {
    char* message = (char*)arg;
    printf("%s\n", message);
    return 0;
}

int main() {
    HANDLE thread1, thread2;
    DWORD threadID1, threadID2;

    char* message1 = "Hello from Thread 1!";
    char* message2 = "Hello from Thread 2!";

    // Create threads
    thread1 = CreateThread(NULL, 0, threadFunction, (void*)message1, 0, &threadID1);
    if (thread1 == NULL) {
        printf("Failed to create thread 1\n");
        return 1;
    }

    thread2 = CreateThread(NULL, 0, threadFunction, (void*)message2, 0, &threadID2);
    if (thread2 == NULL) {
        printf("Failed to create thread 2\n");
        return 1;
    }

    // Wait for both threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    printf("Both threads finished execution.\n");

    // Close thread handles
    CloseHandle(thread1);
    CloseHandle(thread2);

    // ? Keep window open until user presses Enter
    printf("\nPress Enter to exit...");
    getchar();

    return 0;
}
