#include "BlumenstraussAutomat.h"
#include <iostream>
#include <thread>
#include <chrono>

int blatt3_1_main(void);
int blatt3_1_kunde_main(bool automatisch);
void kaufeBlume(BlumenstraussAutomat &, bool automatisch);
int blatt3_1_lieferant_main(void);

int blatt3_1_main(void) {
	std::cout << "Blumenstraussautomat" << std::endl;
	BlumenstraussAutomat ba;
	ba.starten();
	return 0;
}

int blatt3_1_kunde_main(bool automatisch) {
	int anzahl = -1; 
	BlumenstraussAutomat ba;
	if (automatisch) {
		anzahl = 2;
	} else {
		std::cout << "Blumenstrauss-Kunde, wievele Straeusse wollen Sie kaufen: " << std::endl;
		std::cin >> anzahl;
	}

	for (int i = 0; i < anzahl; ++i) {
		kaufeBlume(ba, automatisch);
	}
	std::cout << "Kunde verlaesst den Automat. " << std::endl;

	return 0;
}

void kaufeBlume(BlumenstraussAutomat & ba, bool automatisch) {
	std::cout << "Stehe vor dem Automaten" << std::endl;
	ba.getSemaphoreFrei().wait();
	if (automatisch) {
		for (int i = 0; i < ba.kosten; ++i) {
			ba.getSemaphoreIdle().wait();
			std::cout << "Werfe 1 Euro ein" << std::endl;
			ba.getSemaphoreKunde().signal();
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

	} else {
		int einwurf = 0;
		for (int i = 0; i < ba.kosten; einwurf = 0) {
			ba.getSemaphoreIdle().wait();
			std::cout << "Werfe ein: "; 
			std::cin >> einwurf;
			if (einwurf > 0) {
				//TODO shared memory betrag
				ba.getSemaphoreKunde().signal();
				i += einwurf;
			}
		}
	}
	ba.getSemaphoreFrei().signal();
	ba.getSemaphoreBlume().wait();
	std::cout << "Blume erhalten" << std::endl;
}

int blatt3_1_lieferant_main(void) {
	BlumenstraussAutomat ba;
	std::cout << "Blumenstrauss-Lieferant kommt " << std::endl;
	ba.getSemaphoreLieferant().signal();
	return 0;
}