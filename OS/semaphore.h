#ifndef _WIN32
#error ONLY Windows OS implemented yet
#endif
#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__
#include <Windows.h>

class semaphore {
private:
	HANDLE s;
public:
	semaphore(const char * name, const unsigned int initialValue, const unsigned int maxValue);
	semaphore(const semaphore &) = delete;
	semaphore(semaphore &&);
	~semaphore();
	void wait(unsigned int maxMilliseconds = INFINITE);
	long signal(long count = 1);
};

#endif //__SEMAPHORE_H__