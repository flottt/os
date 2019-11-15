#ifdef _WIN32
#include <Windows.h>
#include <iostream>
#include <string>

int semapharen_main(void);

int semapharen_main(void) {
	DWORD dwWaitResult;
	std::string text(30, '\0');
	SECURITY_ATTRIBUTES secus;
	secus.nLength = 1;
	secus.lpSecurityDescriptor = 0;
	secus.bInheritHandle = true;

	HANDLE semaphore = CreateSemaphore(
		&secus,
		2,
		2,
		"meineOSSemaphore"
	);
	if (semaphore == 0) {
		std::cout << "CreateSemaphore error: " << GetLastError();
		return -1;
	}
	std::cout << "Semaphore initialisiert. " << std::endl; 

	dwWaitResult = WaitForSingleObject(semaphore, 120000);
	switch (dwWaitResult) {
	case WAIT_OBJECT_0:
		std::cout << "Semaphore bekommen. " << std::endl << "Eingabe: "; 
		std::cin >> text; 
		if (!ReleaseSemaphore(
			semaphore,
			1,
			NULL
		)) {
			std::cout << "Fehler beim Freigeben der Semaphore. " << std::endl; 
		}
		break;
	case WAIT_TIMEOUT:
		std::cout << "Waiting timeout. " << std::endl;
		break;
	default:
		std::cout << "Anderes Wait-Result: " << dwWaitResult << std::endl;
	}
	



	CloseHandle(semaphore);
	return 0;
}
#else
int semapharen_main(void) {
	std::cout << "not implemented in non-Windows" << std::endl;
	return 0;
}
#endif