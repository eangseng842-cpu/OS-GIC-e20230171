/* shm-producer.c — Writes to POSIX shared memory */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS-iengseng";

    const char *message_0 = "Hello, ";
    const char *message_1 = "this is shared memory IPC!";

    int shm_fd;
    void *ptr;

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sprintf(ptr, "%s", message_0);
    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);
    ptr += strlen(message_1);

    printf("Producer: wrote to shared memory '%s'\n", name);
    printf("Producer: message = \"%s%s\"\n", message_0, message_1);

    return 0;
}
