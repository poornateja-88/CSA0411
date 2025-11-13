#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    struct message msg;
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello, message queue (simulated)!");

    // ---- Producer: write message to a file ----
    FILE *fp = fopen("message_queue.txt", "w");
    if (fp == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%ld|%s\n", msg.msg_type, msg.msg_text);
    fclose(fp);
    printf("Producer: Data sent to message queue file: %s\n", msg.msg_text);

    // ---- Consumer: read message back from file ----
    fp = fopen("message_queue.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%ld|%99[^\n]", &msg.msg_type, msg.msg_text);
    fclose(fp);
    printf("Consumer: Data received from message queue file: %s\n", msg.msg_text);

    // ---- Pause so output window stays open ----
    printf("\nPress Enter to exit...");
    getchar();

    return 0;
}
