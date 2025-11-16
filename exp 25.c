#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int fd;

    fd = open("foo.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    printf("fd = %d\n", fd);

    if (fd == -1)
    {
        printf("Error Number: %d\n", errno);
        perror("Program");
    }
    else
    {
        printf("File opened/created successfully.\n");
        close(fd);
    }

    // *** VERY IMPORTANT FOR Dev-C++ ***
    printf("\nPress Enter to exit...");
    getchar();     // keeps the output window open
    getchar();     // absorbs extra newline

    return 0;
}
