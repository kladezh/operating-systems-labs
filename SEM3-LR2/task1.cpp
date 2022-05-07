#include "task1.h"

HANDLE H_STDIN;
DWORD  FDW_SAVE_OLD_MODE;

VOID ErrorExit(LPCSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(H_STDIN, FDW_SAVE_OLD_MODE);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD key_event) {
    if (key_event.bKeyDown && key_event.uChar.AsciiChar == 'q') exit(0);
}

void task1() {
    DWORD fdwMode, cNumRead;
    INPUT_RECORD irInBuff[128];

    H_STDIN = GetStdHandle(STD_INPUT_HANDLE);

    if (!GetConsoleMode(H_STDIN, &FDW_SAVE_OLD_MODE))
        ErrorExit("GetConsoleMode");

    fdwMode = ENABLE_WINDOW_INPUT;
    if (!SetConsoleMode(H_STDIN, fdwMode))
        ErrorExit("SetConsoleMode");

    while (true) {
        Sleep(1000);
        system("cls");

        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);

        GlobalMemoryStatusEx(&statex);

        _tprintf(TEXT("There is  %*ld percent of memory in use.\n"),
            WIDTH, statex.dwMemoryLoad);

        _tprintf(TEXT("There are %*I64d total KB of physical memory.\n"),
            WIDTH, statex.ullTotalPhys / DIV);

        _tprintf(TEXT("There are %*I64d free  KB of physical memory.\n"),
            WIDTH, statex.ullAvailPhys / DIV);

        // handle key event
        if (!ReadConsoleInput(H_STDIN, irInBuff, 128, &cNumRead))
            ErrorExit("SetConsoleMode");

        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuff[i].EventType == KEY_EVENT)
                KeyEventProc(irInBuff[i].Event.KeyEvent);
        }
    }
}