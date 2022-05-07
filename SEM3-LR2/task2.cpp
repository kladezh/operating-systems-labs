#include "task2.h"

void printMemoryState(DWORD state) {
	std::cout << "Memory state is: ";

	switch (state) {
	case MEM_COMMIT:
		std::cout << "Commited";
		break;
	case MEM_RESERVE:
		std::cout << "Reserved";
		break;
	case MEM_DECOMMIT:
		std::cout << "Decommited";
		break;
	case MEM_RELEASE:
		std::cout << "Released";
		break;
	default:
		std::cout << "...unknown...";
	}

	std::cout << '\n';
}

void printPageProtect(DWORD protect) {
	std::cout << "Page protect is: ";

	switch (protect) {
	case NULL:
		std::cout << "Null";
		break;
	case PAGE_NOACCESS:
		std::cout << "No access";
		break;
	case PAGE_READONLY:
		std::cout << "Readonly";
		break;
	case PAGE_READWRITE:
		std::cout << "Readwrite";
		break;
	}

	std::cout << '\n';
}

void task2() {
	void* cast_addr = nullptr;

	/* ЗАДАНИЕ 1 */
	// >
	// узнаём размер страницы памяти
	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);

	SIZE_T page_size = system_info.dwPageSize;

	std::cout << "Page size: " << page_size << '\n';

	// запрашиваем кол-во страниц
	SIZE_T page_count;

	std::cout << "Enter the count of virtual memory pages: ";
	std::cin >> page_count;

	// резервируем страницы
	LPVOID allocate_addr = VirtualAlloc(NULL, page_count * page_size, MEM_RESERVE, PAGE_READWRITE);

	if (allocate_addr == NULL) {
		std::cout << "Memory allocation error: " << GetLastError();
		exit(1);
	}

	std::cout << "Allocation address: " << allocate_addr << '\n';
	// <

	/* ЗАДАНИЕ 2 */
	// >
	SIZE_T commit_page_count, first_commit_page;

	// запрашиваем страницы
	std::cout << "Enter the count of virtual memory pages to commit: ";
	std::cin >> commit_page_count;

	std::cout << "Enter the index of first page: ";
	std::cin >> first_commit_page;

	// получаем страницы
	cast_addr = (SIZE_T*)allocate_addr + (first_commit_page * page_size);
	LPVOID commit_addr = VirtualAlloc(cast_addr, commit_page_count * page_size, MEM_COMMIT, PAGE_READWRITE);

	if (commit_addr == NULL) {
		std::cout << "Memory commit error: " << GetLastError();
		exit(1);
	}

	std::cout << "Commited pages: count = " << commit_page_count << ", begin index = " << first_commit_page << "\n";
	std::cout << "Commit address: " << commit_addr << "\n";
	// <

	/* ЗАДАНИЕ 3 */
	// >
	int arr[] = { 0, 5, 10, -2, 7 }; // size = 5

	cast_addr = commit_addr;
	errno_t memcpy_err = memcpy_s((int*)cast_addr, commit_page_count * page_size,
		arr, 5 * sizeof(int));

	if (memcpy_err != NULL) {
		std::cout << "Memcopy error: " << memcpy_err << "\n";
		exit(1);
	}

	std::cout << "Copied array in memory:\n";
	for (int i = 0; i < 5; i++) {
		std::cout << *((int*)commit_addr + i) << '\n';
	}
	// <

	/* ЗАДАНИЕ 4 */
	// >
	MEMORY_BASIC_INFORMATION mem_info;
	int query_err;

	query_err = VirtualQuery(commit_addr, &mem_info, sizeof(mem_info));
	if (query_err == NULL) {
		std::cout << "Memory info error: " << query_err;
		exit(1);
	}

	std::cout << "Info about commit memory:\n";
	printMemoryState(mem_info.State);
	printPageProtect(mem_info.Protect);

	cast_addr = (SIZE_T*)commit_addr + commit_page_count * page_size;
	query_err = VirtualQuery(cast_addr, &mem_info, sizeof(mem_info));
	if (query_err == NULL) {
		std::cout << "Memory info error: " << query_err;
		exit(1);
	}

	std::cout << "Info about commit after commit memory:\n";
	printMemoryState(mem_info.State);
	printPageProtect(mem_info.Protect);
	// <

	/* ЗАДАНИЕ 4 */
	// >
	LPVOID another_commit_addr = VirtualAlloc(cast_addr, page_size, MEM_COMMIT, PAGE_READONLY);

	if (another_commit_addr == NULL) {
		std::cout << "Memory commit error: " << GetLastError();
		exit(1);
	}

	std::cout << "Another commit address: " << another_commit_addr << "\n";

	query_err = VirtualQuery(another_commit_addr, &mem_info, sizeof(mem_info));
	if (query_err == NULL) {
		std::cout << "Memory info error: " << query_err;
		exit(1);
	}

	std::cout << "Info about another commit memory:\n";
	printMemoryState(mem_info.State);
	printPageProtect(mem_info.Protect);
	// <

	/* ЗАДАНИЕ 5 */
	// >
	SIZE_T decommit_page_count, first_decommit_page;

	std::cout << "Enter the count of decommit pages: ";
	std::cin >> decommit_page_count;

	std::cout << "Enter the index of first decommite page: ";
	std::cin >> first_decommit_page;

	cast_addr = (SIZE_T*)allocate_addr + (first_decommit_page * page_size);
	query_err = VirtualFree(cast_addr, decommit_page_count * page_size, MEM_DECOMMIT);
	if (query_err == NULL) {
		std::cout << "Memory deccomit error: " << query_err;
		exit(1);
	}

	std::cout << "Allocation address: " << cast_addr << '\n';

	query_err = VirtualQuery(cast_addr, &mem_info, sizeof(mem_info));
	if (query_err == NULL) {
		std::cout << "Memory info error: " << query_err;
		exit(1);
	}

	std::cout << "Info about decommit memory:\n";
	printMemoryState(mem_info.State);
	printPageProtect(mem_info.Protect);
	// <

	/* ЗАДАНИЕ 5 */
	// >
	query_err = VirtualFree(allocate_addr, 0, MEM_RELEASE);
	if (query_err == NULL) {
		std::cout << "Memory free error: " << query_err;
		exit(1);
	}
	// <
}