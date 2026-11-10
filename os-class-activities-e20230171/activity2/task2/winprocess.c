/* winprocess.c — Process creation on Windows using CreateProcess() */
#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    /* Zero out the structures */
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent process (PID: %lu) — creating child...\n", GetCurrentProcessId());

    /*
     * Attempt to launch mspaint.
     * On Windows 10, mspaint is typically at C:\Windows\System32\mspaint.exe.
     * On Windows 11, mspaint is a Store app, so we fallback to "mspaint.exe" via PATH.
     */
    char cmd[] = "mspaint.exe";
    BOOL created = CreateProcess(
        "C:\\Windows\\System32\\mspaint.exe",  /* Application path */
        NULL,           /* Command line */
        NULL,           /* Process security attributes */
        NULL,           /* Thread security attributes */
        FALSE,          /* Inherit handles */
        0,              /* Creation flags */
        NULL,           /* Environment */
        NULL,           /* Current directory */
        &si,            /* Startup info */
        &pi             /* Process information */
    );

    if (!created) {
        /* Fallback for Windows 11 / Store app version */
        created = CreateProcess(
            NULL,
            cmd,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi
        );
    }

    if (!created) {
        fprintf(stderr, "CreateProcess failed (error %lu).\n", GetLastError());
        return 1;
    }

    printf("Child process created!\n");
    printf("  Child PID:       %lu\n", pi.dwProcessId);
    printf("  Child Thread ID: %lu\n", pi.dwThreadId);

    printf("Parent: waiting for child (mspaint) to exit...\n");
    printf(">>> Open Task Manager now and take a screenshot! <<<\n");
    printf(">>> Then close mspaint to let this program finish. <<<\n");

    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Parent: child has exited. Cleaning up.\n");

    /* Close process and thread handles */
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
