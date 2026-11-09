#include <fcntl.h>
#include <unistd.h>
int main() {
    char buffer[1024];
    ssize_t bytesRead;
    int src = open("result.txt", O_RDONLY);
    int dst = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dst, buffer, bytesRead);
    }
    close(src);
    close(dst);
    write(1, "File copied successfully!\n", 25);
    return 0;
}
