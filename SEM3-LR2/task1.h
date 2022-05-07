#pragma once

#include <windows.h>
#include <stdio.h>
#include <tchar.h>  

#define DIV (1<<20)
#define WIDTH 7

extern HANDLE H_STDIN;
extern DWORD  FDW_SAVE_OLD_MODE;

VOID ErrorExit(LPCSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);

void task1();
