#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Process ID simulation (Windows doesn’t support getpid directly)\n");
    printf("Program executed successfully.\n");

    system("pause");  // pauses until a key is pressed
    return 0;
}
