/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>    // only for snprintf to format numbers into strings

int main() {
    char buffer[512];
    int len;

    // 1. Open current directory with opendir(".")
    DIR *dir = opendir(".");
    if (dir == NULL) {
        const char *err = "Error opening directory\n";
        write(2, err, strlen(err));
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    // 2. Print header line using write()
    len = snprintf(buffer, sizeof(buffer), "%-30s %10s\n", "Filename", "Size (bytes)");
    write(1, buffer, len);
    len = snprintf(buffer, sizeof(buffer), "%-30s %10s\n", "------------------------------", "----------");
    write(1, buffer, len);

    // 3. Loop through entries with readdir()
    while ((entry = readdir(dir)) != NULL) {
        // 4. For each entry, use stat() to get file size
        if (stat(entry->d_name, &fileStat) == 0) {
            // 5. Format output into buffer with snprintf(), then write() to fd 1
            len = snprintf(buffer, sizeof(buffer), "%-30s %10ld\n", entry->d_name, fileStat.st_size);
            write(1, buffer, len);
        }
    }

    // 6. Close directory with closedir()
    closedir(dir);
    return 0;
}
