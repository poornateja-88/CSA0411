#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void copyFile()
{
    const char *source_file = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    const char *destination_file = "C:/Users/itssk/OneDrive/Desktop/sk.txt";

    int source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0)
    {
        printf("Error: Cannot open source file.\n");
        return;
    }

    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd < 0)
    {
        printf("Error: Cannot create destination file.\n");
        close(source_fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead)
        {
            printf("Error: Write failed.\n");
            close(source_fd);
            close(dest_fd);
            return;
        }
    }

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
}

void createFile()
{
    FILE *fp;
    fp = fopen("C:/Users/itssk/OneDrive/Desktop/sasi.txt", "w");

    if (fp == NULL)
    {
        printf("Error creating file.\n");
        return;
    }

    fprintf(fp, "This is a sample text written to the file.\n");
    fclose(fp);

    printf("File created successfully.\n");
}

void deleteFile()
{
    if (remove("C:/Users/itssk/OneDrive/Desktop/sasi.txt") == 0)
        printf("File deleted successfully.\n");
    else
        printf("Error deleting file.\n");
}

int main()
{
    int n;

    printf("1. Create\t2. Copy\t3. Delete\nEnter your choice: ");
    scanf("%d", &n);

    switch (n)
    {
    case 1:
        createFile();
        break;

    case 2:
        copyFile();
        break;

    case 3:
        deleteFile();
        break;

    default:
        printf("Invalid choice.\n");
        break;
    }

    // ?? Keeps the output window open in Dev-C++
    printf("\nPress any key to exit...");
    system("pause");

    return 0;
}
