#pragma once

#include <iostream>
#include <windows.h>

void printLastFileError(HANDLE h_file, const std::string& message_after_error);
void cutData(LPCWSTR source_filename, LONG position, LPCWSTR destination_filename);

void task2();