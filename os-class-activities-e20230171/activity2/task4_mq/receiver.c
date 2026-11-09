/* receiver.c — Receives a message from a POSIX message queue */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include "common.h"

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];

    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        fprintf(stderr, "Hint: Did you run sender first?\n");
        exit(EXIT_FAILURE);
    }

    mq_getattr(mq, &attr);

    if (mq_receive(mq, buffer, attr.mq_msgsize, NULL) == -1) {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    }

    printf("Receiver: message received from queue '%s'\n", QUEUE_NAME);
    printf("Receiver: message = \"%s\"\n", buffer);

    mq_close(mq);

    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }
    printf("Receiver: queue unlinked.\n");

    return 0;
}
