/* shm-consumer.c — Reads from POSIX shared memory */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS-seng";

    int shm_fd;
    void *ptr;

    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        fprintf(stderr, "Hint: Did you run shm-producer first?\n");
        exit(EXIT_FAILURE);
    }

    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("Consumer: reading from shared memory '%s'\n", name);
    printf("Consumer: message = \"%s\"\n", (char *)ptr);

    if (shm_unlink(name) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }
    printf("Consumer: shared memory unlinked.\n");

    return 0;
}
