/* file_reader_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[256];
    ssize_t bytesRead;
    const char *err = "Error opening file\n";

    // 1. Open "output.txt" for reading using open()
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        write(2, err, strlen(err));
        return 1;
    }

    // 2. Read content into buffer using read() in a loop
    // 3. Write the content to the terminal (fd 1) using write()
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }

    // 4. Close the file using close()
    close(fd);

    return 0;
}
