#include <stdio.h>
#include <stdlib.h>

/* Priority Scheduling (non-preemptive)
   Portable version for older compilers (Dev-C++ / MinGW)
*/

struct priority_scheduling {
    char process_name;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int priority;
};

int main(void)
{
    int number_of_process;
    int total = 0;
    struct priority_scheduling temp_process;
    int ASCII_number = 65; /* A, B, C ... */
    int position;
    float average_waiting_time = 0.0f;
    float average_turnaround_time = 0.0f;
    int i, j, ch;

    printf("Enter the total number of processes: ");
    if (scanf("%d", &number_of_process) != 1 || number_of_process <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    /* consume leftover newline */
    while ((ch = getchar()) != '\n' && ch != EOF) { }

    /* allocate dynamically (portable) */
    struct priority_scheduling *process = (struct priority_scheduling *)
        malloc(sizeof(struct priority_scheduling) * number_of_process);
    if (process == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter the Burst Time and Priority of each process:\n");

    for (i = 0; i < number_of_process; i++)
    {
        process[i].process_name = (char)(ASCII_number + i);
        process[i].waiting_time = 0;
        process[i].turn_around_time = 0;

        printf("\nProcess %c\n", process[i].process_name);

        /* Burst time input */
        printf("Enter the Burst Time: ");
        while (scanf("%d", &process[i].burst_time) != 1) {
            printf("Invalid input. Enter an integer for Burst Time: ");
            while ((ch = getchar()) != '\n' && ch != EOF) { }
        }
        while ((ch = getchar()) != '\n' && ch != EOF) { } /* clear rest of line */

        /* Priority input */
        printf("Enter the Priority (higher number = higher priority): ");
        while (scanf("%d", &process[i].priority) != 1) {
            printf("Invalid input. Enter an integer for Priority: ");
            while ((ch = getchar()) != '\n' && ch != EOF) { }
        }
        while ((ch = getchar()) != '\n' && ch != EOF) { } /* clear rest of line */
    }

    /* Sort processes by Priority (descending: higher number first) */
    for (i = 0; i < number_of_process - 1; i++)
    {
        position = i;
        for (j = i + 1; j < number_of_process; j++)
        {
            if (process[j].priority > process[position].priority)
                position = j;
        }
        /* swap */
        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }

    /* Calculate waiting time */
    process[0].waiting_time = 0;
    total = 0;
    for (i = 1; i < number_of_process; i++)
    {
        process[i].waiting_time = 0;
        for (j = 0; j < i; j++)
            process[i].waiting_time += process[j].burst_time;
        total += process[i].waiting_time;
    }

    average_waiting_time = (float)total / (float)number_of_process;

    /* Calculate turnaround time and print */
    total = 0;
    printf("\n\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < number_of_process; i++)
    {
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time;
        total += process[i].turn_around_time;
        printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i].process_name,
               process[i].burst_time,
               process[i].priority,
               process[i].waiting_time,
               process[i].turn_around_time);
    }

    average_turnaround_time = (float)total / (float)number_of_process;

    printf("\nAverage Waiting Time : %.2f", average_waiting_time);
    printf("\nAverage Turnaround Time : %.2f\n", average_turnaround_time);

    /* Keep Dev-C++ console open */
    printf("\nPress Enter to exit...");
    while ((ch = getchar()) != '\n' && ch != EOF) { } /* consume leftover */
    getchar();

    free(process);
    return 0;
}
