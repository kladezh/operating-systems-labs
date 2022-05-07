#pragma once

#include <windows.h>
#include <iostream>
#include <iomanip>  // дл€ табул€ции (setiosflags())

bool hasLogicalDrive(const std::string& drive);
void printDriveType(const std::string& drive);
void printVolumeInfo(const std::string& drive);
void printDiskFreeSpace(const std::string& drive);
void printDriveInfo(const std::string& drive_name);

void task1();