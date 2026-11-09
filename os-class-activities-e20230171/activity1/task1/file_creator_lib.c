/* file_creator_lib.c */
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "Hello from Operating Systems class!\n");
    fclose(fp);

    printf("File created successfully!\n");
    return 0;
}
