/* file_creator_win.c */
#include <windows.h>
#include <string.h>

int main() {
    const char *text = "Hello from Operating Systems class!\n";
    const char *confirm = "File created successfully!\n";
    DWORD bytesWritten;

    HANDLE hFile = CreateFile(
        "output.txt",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        const char *err = "Error creating file\n";
        WriteFile(GetStdHandle(STD_ERROR_HANDLE), err, strlen(err), &bytesWritten, NULL);
        return 1;
    }

    WriteFile(hFile, text, strlen(text), &bytesWritten, NULL);
    CloseHandle(hFile);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), confirm, strlen(confirm), &bytesWritten, NULL);

    return 0;
}
