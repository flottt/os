#include "BlumenstraussAutomat.h"
#include <thread>
#include <iostream>
#include <sstream>

#define Blumenstraussautomat_Liefermenge 7
#define Blumenstraussautomat_Initialblumenmenge 10

/** Klassenkonstanten */
const int BlumenstraussAutomat::kosten = 5;

/** Kostruktor */
BlumenstraussAutomat::BlumenstraussAutomat() :
	automatFrei(semaphore("BLUMENSTRAUSS_AUTOMAT_SEMAPHORE_FREI", 1, 1)),  
	automatKunde(semaphore("BLUMENSTRAUSS_AUTOMAT_SEMAPHORE_KUNDE", 0, 60)),  
	automatIdle(semaphore("BLUMENSTRAUSS_AUTOMAT_SEMAPHORE_IDLE", 1, 1)),  
	automatLieferant(semaphore("BLUMENSTRAUSS_AUTOMAT_SEMAPHORE_LIEFERANT", 0, 1)),
	automatBlume(semaphore("BLUMENSTRAUSS_AUTOMAT_SEMAPHORE_Blume", 0, 1)),
	automatBlumenlager(semaphore("BLUMENSTRAUSS_AUTOMAT_SEMAPHORE_Blumenlager", Blumenstraussautomat_Initialblumenmenge, 255)),
	blumen(60) {
}

void BlumenstraussAutomat::starten(void) {
	std::thread tKunde(&(BlumenstraussAutomat::muenzenThreadExecute), this);
	std::thread tLieferant(&(BlumenstraussAutomat::lieferantenThreadExecute), this);
	tKunde.join();
	tLieferant.join();
}

/** Destruktor */
BlumenstraussAutomat::~BlumenstraussAutomat() {
}

void BlumenstraussAutomat::muenzenThreadExecute(BlumenstraussAutomat * that) {
	while (1) {
		that->automatKunde.wait();
		that->geldEingeworfen();
		that->automatIdle.signal();
	}
}

void BlumenstraussAutomat::lieferantenThreadExecute(BlumenstraussAutomat * that) {
	while (1) {
		that->automatLieferant.wait();
		that->lieferantLiefert();
	}
}

void BlumenstraussAutomat::geldEingeworfen(void) {
	this->geld++;
	if (this->geld >= BlumenstraussAutomat::kosten) {
		this->geld -= BlumenstraussAutomat::kosten;
		this->automatBlumenlager.wait();
		this->automatBlume.signal();
		std::cout << "Blumenstrauss kommt sofort. ";
		if (this->geld > 0) {
			std::cout << "Ihr Wechselgeld: " << this->geld;
		}
		std::cout << std::endl;
		this->geld = 0;
	} else {
		std::cout << "Eingeworfener Betrag: " << this->geld << " Euro" << std::endl;
	}
}

void BlumenstraussAutomat::lieferantLiefert(void) {
	long blumenlager = this->automatBlumenlager.signal(Blumenstraussautomat_Liefermenge);
	std::ostringstream text;
	text << "Blumenstrausslager aufgefuellt auf " << blumenlager << " Blumen" << std::endl;
	std::cout << text.str();

}

