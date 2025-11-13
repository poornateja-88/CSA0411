#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;

    // Open file to simulate shared memory
    fp = fopen("shared_memory.txt", "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write message to the file
    char message[] = "Hello, shared memory (simulated)!";
    fprintf(fp, "%s", message);
    fclose(fp);

    // Print the message
    printf("Data written successfully: %s\n", message);

    // Pause so Dev-C++ output window stays open
    printf("\nPress Enter to exit...");
    getchar();  // waits for user input

    return 0;
}
