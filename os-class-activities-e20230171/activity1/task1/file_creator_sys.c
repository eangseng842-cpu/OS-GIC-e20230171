/* file_creator_sys.c */
#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()

int main() {
    const char *text = "Hello from Operating Systems class!\n";
    const char *msg = "File created successfully!\n";
    const char *err = "Error opening file\n";

    // 1. Open/create "output.txt" using open()
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        write(2, err, strlen(err));
        return 1;
    }

    // 2. Write "Hello from Operating Systems class!\n" using write()
    write(fd, text, strlen(text));

    // 3. Close the file using close()
    close(fd);

    // 4. Print "File created successfully!\n" to the terminal using write()
    write(1, msg, strlen(msg));

    return 0;
}
