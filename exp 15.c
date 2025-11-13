#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  // For _mkdir on Windows

int main()
{
    char mainDirectory[] = "C:/Users/itssk/OneDrive/Desktop";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char folderPath[300];
    char filePath[400];

    // Build folder path: Desktop/os
    snprintf(folderPath, sizeof(folderPath), "%s/%s", mainDirectory, subDirectory);

    // Try to create the folder if it doesn't exist
    _mkdir(folderPath);  // _mkdir works fine even if folder already exists

    // Build full file path
    snprintf(filePath, sizeof(filePath), "%s/%s", folderPath, fileName);

    // Try to open (create) the file
    FILE *file = fopen(filePath, "w");
    if (file == NULL)
    {
        printf("? Error creating file.\n");
        printf("Check if the folder path exists: %s\n", folderPath);
        system("pause");
        return 1;
    }

    fprintf(file, "This is an example file content.\n");
    fclose(file);

    printf("? File created successfully!\n");
    printf("?? Path: %s\n", filePath);

    // Keep window open
    printf("\nPress any key to exit...");
    system("pause");

    return 0;
}
