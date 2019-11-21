#include <stdlib.h>
#include <thread>
#include <iostream>
#include <ctime>
#include "semaphore.h"
#include <vector>
#include <sstream>

int diningPhil_global_i;
std::vector<semaphore> diningPhil_global_semaphoren;
char diningPhil_global_Does[6];

int badDiningPhil_main(void);
void running(int p);
void stick_up(int p); 
void eat(int p);
void stick_down(int p);
void warten(int milliseconds, int millisecondsAdd);

void warten(int milliseconds, int millisecondsAdd) {
	if (millisecondsAdd > 0) {
		milliseconds += std::rand() % millisecondsAdd;
	}
	//std::cout << "t= " << milliseconds << " ";
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

}

void running(int p) {
	try {
		std::srand(static_cast<unsigned int>(std::time(nullptr)) + p * 500);
		std::ostringstream status;
		status << diningPhil_global_Does << " Phil " << p << " is here " << std::endl;
		std::cout << status.str();

		warten(1000, 2500);
		while (diningPhil_global_i > 0) {
			stick_up(p);
			warten(100, 200);
			eat(p);
			warten(100, 200);
			stick_down(p);
			warten(100, 200);
			diningPhil_global_i--;
		}
	} catch (const char * err) {
		std::ostringstream status;
		diningPhil_global_Does[p - 1] = '=';
		status << diningPhil_global_Does << " Fehler beim Phil " << p << ": " << err << std::endl;
		diningPhil_global_Does[p - 1] = '-';
		std::cout << status.str();
	} catch (std::string err) {
		std::ostringstream status;
		diningPhil_global_Does[p - 1] = '=';
		status << diningPhil_global_Does << " Fehler beim Phil " << p << ": " << err << std::endl;
		diningPhil_global_Does[p - 1] = '-';
		std::cout << status.str();
	} catch (std::exception err) {
		std::ostringstream status;
		diningPhil_global_Does[p - 1] = '=';
		status << diningPhil_global_Does << " Fehler beim Phil " << p << ": " << err.what() << std::endl;
		diningPhil_global_Does[p - 1] = '-';
		std::cout << status.str();
	} catch (...) {
		std::ostringstream status;
		diningPhil_global_Does[p - 1] = '=';
		status << diningPhil_global_Does << " unbekannter Fehler beim Phil " << p << std::endl;
		diningPhil_global_Does[p - 1] = '-';
		std::cout << status.str();
	}
}

void stick_up(int p) {
	std::ostringstream status;
	diningPhil_global_Does[p - 1] = 'h';
	status << diningPhil_global_Does << " Phil " << p << " gets hungry... " << std::endl;
	diningPhil_global_Does[p - 1] = 'H';
	std::cout << status.str();
	if (p == 5) {
		diningPhil_global_semaphoren[0].wait();
		diningPhil_global_semaphoren[1].wait();
	} else if (p == 4) {
		diningPhil_global_semaphoren[0].wait();
		diningPhil_global_semaphoren[4].wait();
	} else {
		diningPhil_global_semaphoren[p].wait();
		diningPhil_global_semaphoren[p + 1].wait();
	}
	warten(100, 900);
}
void eat(int p) {
	std::ostringstream status;
	diningPhil_global_Does[p - 1] = 'e';
	status << diningPhil_global_Does << " Phil " << p << " is eating... " << std::endl;
	diningPhil_global_Does[p - 1] = 'E';
	std::cout << status.str();

	warten(1000, 2000);
}
void stick_down(int p) {
	std::ostringstream status;
	diningPhil_global_Does[p - 1] = 's';
	status << diningPhil_global_Does << " Phil " << p << " has eaten a lot..." << std::endl;
	diningPhil_global_Does[p - 1] = 'S';
	std::cout << status.str();

	diningPhil_global_semaphoren[(p + 1) % 5].signal();
	diningPhil_global_semaphoren[p % 5].signal();
}



int badDiningPhil_main(void) {
	try {
		const int philCount = 5;
		diningPhil_global_i = 2000;

		diningPhil_global_semaphoren.reserve(philCount);
		for (int i = 0; i < philCount; i++) {
			diningPhil_global_Does[i] = '-';
		}
		diningPhil_global_Does[philCount] = '\0';

		diningPhil_global_semaphoren.push_back(semaphore("DiningPhil1", 1, 1));
		diningPhil_global_semaphoren.push_back(semaphore("DiningPhil2", 1, 1));
		diningPhil_global_semaphoren.push_back(semaphore("DiningPhil3", 1, 1));
		diningPhil_global_semaphoren.push_back(semaphore("DiningPhil4", 1, 1));
		diningPhil_global_semaphoren.push_back(semaphore("DiningPhil5", 1, 1));

		std::thread t1(&running, 1);
		std::thread t2(&running, 2);
		std::thread t3(&running, 3);
		std::thread t4(&running, 4);
		std::thread t5(&running, 5);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
	} catch (...) {
		std::cout << "unbekannter Fehler in diningPhil.main() " << std::endl;
	}
	return 0;
}