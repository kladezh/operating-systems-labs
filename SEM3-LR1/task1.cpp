#include "task1.h";

bool hasLogicalDrive(const std::string& drive) {
	char drive_letter = drive.at(0);
	DWORD mask = GetLogicalDrives();

	return (mask >> (drive_letter - 'A')) & 1;
}

void printDriveType(const std::string& drive) {
	switch (GetDriveType(std::wstring(drive.begin(), drive.end()).c_str())) {
	case DRIVE_UNKNOWN:		std::cout << "unknown type..."; break;
	case DRIVE_NO_ROOT_DIR: std::cout << "wrong dir..."; break;
	case DRIVE_REMOVABLE:	std::cout << "this drive is REMOVABLE"; break;
	case DRIVE_FIXED:		std::cout << "this drive is FIXED"; break;
	case DRIVE_REMOTE:		std::cout << "this drive is REMOTE/NETWORK drive"; break;
	case DRIVE_CDROM:		std::cout << "this drive is CD-ROOM drive"; break;
	case DRIVE_RAMDISK:		std::cout << "this drive is RAM drive"; break;
	default: std::cout << "\nUNKNOWN ERROR...\n";
	}
	std::cout << "\n";
}

void printVolumeInfo(const std::string& drive) {
	const int VOLNAME_SIZE = 100;
	const int FSYSNAME_SIZE = 100;

	char volume_name_buffer[VOLNAME_SIZE];
	char file_system_name_buffer[FSYSNAME_SIZE];
	DWORD volume_serial_sumber;
	DWORD maximum_component_length;
	DWORD file_system_flags;

	bool success = GetVolumeInformationA(drive.c_str(), volume_name_buffer, VOLNAME_SIZE, &volume_serial_sumber,
		&maximum_component_length, &file_system_flags, file_system_name_buffer, FSYSNAME_SIZE);

	if (success) {
		std::cout << setiosflags(std::ios::left);
		std::cout << std::setw(26) << "Volume name :" << volume_name_buffer << "\n";
		std::cout << std::setw(26) << "Volume serial number :" << volume_serial_sumber << "\n";
		std::cout << std::setw(26) << "File system :" << file_system_name_buffer << "\n";
		std::cout << std::setw(26) << "Maxi component length :" << maximum_component_length << "\n";
		std::cout << std::setw(26) << "File system flags :" << file_system_flags << "\n";
	}
	else {
		std::cout << "no information was recieved...\n";
	}

}

void printDiskFreeSpace(const std::string& drive) {
	ULARGE_INTEGER free_bytes_availabe;
	ULARGE_INTEGER total_number_of_bytes;
	ULARGE_INTEGER total_number_of_free_bytes;

	bool success = GetDiskFreeSpaceEx(std::wstring(drive.begin(), drive.end()).c_str(),
		&free_bytes_availabe, &total_number_of_bytes, &total_number_of_free_bytes);

	if (success) {
		std::cout << setiosflags(std::ios::left);
		std::cout << std::setw(30) << "Free bytes availabe :" <<
			free_bytes_availabe.QuadPart / 1024 / 1024 / 1024 << "gb\n";
		std::cout << std::setw(30) << "Total number of bytes :" <<
			total_number_of_bytes.QuadPart / 1024 / 1024 / 1024 << "gb\n";
		std::cout << std::setw(30) << "Total number of free bytes :" <<
			total_number_of_free_bytes.QuadPart / 1024 / 1024 / 1024 << "gb\n";
	}
	else {
		std::cout << "no information was recieved...\n";
	}
}

void printDriveInfo(const std::string& drive_name) {
	std::cout << "DISK \"" << drive_name << "\"\n\n";

	// проверка на существование диска
	std::cout << "----LOGICAL DRIVE----\n";
	std::cout << std::boolalpha << hasLogicalDrive(drive_name);

	// вывод тип диска
	std::cout << "\n\n----DRIVE TYPE----\n";
	printDriveType(drive_name);

	// вывод информации о диске
	std::cout << "\n\n----VOLUME INFORMATION----\n";
	printVolumeInfo(drive_name);

	// ввывод доступного места на диске
	std::cout << "\n\n----FREE SPACE ON DRIVE----\n";
	printDiskFreeSpace(drive_name);
}


void task1() {

	std::string drive_path = "C:\\";

	printDriveInfo(drive_path);

}