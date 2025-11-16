#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char buffer[100];

    // Creating a new file
    fp = fopen("sample.txt", "w");
    if (fp == NULL) {
        perror("create");
        exit(1);
    } else {
        printf("File 'sample.txt' created successfully.\n");
        fclose(fp);
    }

    // Opening the existing file for writing (append mode)
    fp = fopen("sample.txt", "a");
    if (fp == NULL) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for writing.\n");
    }

    // Writing data to the file
    fprintf(fp, "Hello, World!\n");
    printf("Data written to 'sample.txt'.\n");
    fclose(fp);

    // Opening the file for reading
    fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for reading.\n");
    }

    // Reading data from the file
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), fp);
    if (bytesRead == 0 && !feof(fp)) {
        perror("read");
        exit(1);
    } else {
        printf("Data read from 'sample.txt':\n");
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(fp);

    // Deleting the file
    if (remove("sample.txt") == -1) {
        perror("remove");
        exit(1);
    } else {
        printf("\nFile 'sample.txt' deleted.\n");
    }

    // *** VERY IMPORTANT FOR Dev-C++ ***
    printf("\n\nPress Enter to exit...");
    getchar();  // keeps the output window open

    return 0;
}
