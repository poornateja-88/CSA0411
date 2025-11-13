#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2;
    char filename1[100], filename2[100];
    char c;

    printf("Enter the filename to open for reading: ");
    scanf("%s", filename1);

    fptr1 = fopen(filename1, "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file %s for reading.\n", filename1);
        printf("Press Enter to exit...");
        getchar(); getchar(); // ? keeps window open
        exit(0);
    }

    printf("Enter the filename to open for writing: ");
    scanf("%s", filename2);

    fptr2 = fopen(filename2, "w");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s for writing.\n", filename2);
        fclose(fptr1);
        printf("Press Enter to exit...");
        getchar(); getchar(); // ? keeps window open
        exit(0);
    }

    c = fgetc(fptr1);
    while (c != EOF)
    {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }

    printf("\nContents copied successfully from %s to %s\n", filename1, filename2);

    fclose(fptr1);
    fclose(fptr2);

    printf("\nPress Enter to exit...");
    getchar(); getchar();  // ? waits for you to press Enter before closing
    return 0;
}
