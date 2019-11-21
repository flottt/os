#include "semaphore.h"
#include <iostream>


semaphore::semaphore(const char * name, const unsigned int initialValue, const unsigned int maxValue) {
	SECURITY_ATTRIBUTES secus;
	secus.nLength = 1;
	secus.lpSecurityDescriptor = 0;
	secus.bInheritHandle = true;

	this->s = CreateSemaphore(
		&secus,
		initialValue,
		maxValue,
		name
	);
	if (this->s == 0) {
		std::cout << "CreateSemaphore error: " << GetLastError();
		throw "CreateSemaphore error";
	}
}


semaphore::semaphore(semaphore && that) {
	this->s = that.s;
	that.s = 0;
}

semaphore::~semaphore() {
	if (this->s != 0) {
		CloseHandle(this->s);
	}
	this->s = 0;
}

void semaphore::wait(unsigned int maxMilliseconds) {
	DWORD dwWaitResult = WaitForSingleObject(this->s, maxMilliseconds);
	if (dwWaitResult == WAIT_TIMEOUT) {
		throw "Semaphoren-Deadlock: Timeout";
	}
	if (dwWaitResult != WAIT_OBJECT_0) {
		throw "Semaphoren-Deadlock: Unknown";
	}
}

void semaphore::signal() {
	if (!ReleaseSemaphore(this->s, 1, NULL)) {
		throw "Semaphoren-Release-Lock";
	}
}
