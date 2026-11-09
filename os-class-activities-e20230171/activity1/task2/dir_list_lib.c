/* dir_list_lib.c */
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    printf("%-30s %10s\n", "Filename", "Size (bytes)");
    printf("%-30s %10s\n", "------------------------------", "----------");

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            printf("%-30s %10ld\n", entry->d_name, fileStat.st_size);
        }
    }

    closedir(dir);
    return 0;
}
