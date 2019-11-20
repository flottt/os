#ifdef _WIN32
#include <string>
#include "semaphore.h"
#include <iostream>

int semapharen_main(void);

int semapharen_main(void) {
	std::string text;
	text.reserve(64);
	semaphore s("meineOSSemaphore", 2, 2); 
	std::cout << "Semaphore initialisiert. " << std::endl; 
	s.wait();
	std::cout << "Semaphore bekommen. " << std::endl << "Eingabe: "; 
	std::cin >> text; 
	s.signal();
	return 0;
}
#else
int semapharen_main(void) {
	std::cout << "not implemented in non-Windows" << std::endl;
	return 0;
}
#endif