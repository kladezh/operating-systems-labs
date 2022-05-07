#include "task2.h";

void printLastFileError(HANDLE h_file, const std::string& message_after_error = "") {
	int error;
	if ((error = GetLastError()) != 0) {
		std::cout << error << ": " << message_after_error << std::endl;
		CloseHandle(h_file);
		exit(1);
	}
}

void cutData(LPCWSTR source_filename, LONG position, LPCWSTR destination_filename) {
	
	// открывает файл для чтения, после закрытия дескриптора - удалит файл, если файл не существует, то завершится
	HANDLE h_file = CreateFile(source_filename,
		GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_FLAG_DELETE_ON_CLOSE, NULL
	);
	printLastFileError(h_file, "when setting handle to source_file");

	// сдвиг указателя
	SetFilePointer(h_file, position, NULL, FILE_BEGIN);
	printLastFileError(h_file, "when setting pointer in source_file");

	// чтение файла
	DWORD buff, num_of_read_bytes;

	ReadFile(h_file, &buff, sizeof(buff), &num_of_read_bytes, NULL);
	std::cout << "read_bytes: " << num_of_read_bytes << "\n";		// DEBUG
	printLastFileError(h_file, "when reading source_file");

	// закрывает дескриптор на source файле
	CloseHandle(h_file);


	// открывает файл для записи, если файл не существет - завершится
	h_file = CreateFile(destination_filename,
		GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	);
	printLastFileError(h_file, "when setting handle to destination_file");

	// запись в файл
	DWORD num_of_written_bytes;

	WriteFile(h_file, &buff, num_of_read_bytes, &num_of_written_bytes, NULL);
	std::cout << "written_bytes: " << num_of_written_bytes << "\n";  // DEBUG
	printLastFileError(h_file, "when writing destination_file");

	// закрывает дескриптор на destination файле
	CloseHandle(h_file);
}

void task2() {

	// нужно передать именна существующих файлов
	LPCWSTR source_file = L"";
	LPCWSTR destin_file = L"";

	cutData(source_file, 1, destin_file);
}