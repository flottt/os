#include <iostream>
#include <thread>
#include <process.h>

int blatt1_1_main();
int blatt1_2_main();
int blatt1_3_main();
int blatt1_P_main(int);
void parallelFunktion(const int);

volatile int vari;
volatile int * v_ptr;

int blatt1_1_main() {
	int eingabe;
	vari = 7; 
	v_ptr = &vari;

	while (1) {
		std::cout << std::endl << std::endl;
		std::cout << "Aktuelle Variablen-Adresse: " << (int)(v_ptr) << std::endl;
		std::cout << "Aktueller Variableninhalt: " << (*v_ptr) << std::endl;
		std::cout << "Eingabe 1 wiederholt Ausgabe" << std::endl; 
		std::cout << "Eingabe 2 aendert Adresse" << std::endl;
		std::cout << "Eingabe 3 aendert Wert" << std::endl;
		std::cout << "Jede andere Eingabe beendet das Programm" << std::endl;
		std::cout << "Eingabe: ";
		std::cin >> eingabe;
		switch (eingabe) {
		case 1: 
			std::cout << "Erneutes Ausgeben. " << std::endl;
			break;
		case 2: 
			std::cout << "Neue Adresse: "; 
			std::cin >> eingabe; 
			v_ptr = (int*)eingabe; 
			std::cout << "Neue Adresse gespeichert. " << std::endl;
			break;
		case 3:
			std::cout << "Neuer Wert: ";
			std::cin >> eingabe;
			*v_ptr = eingabe;
			std::cout << "Neuer Wert gespeichert. " << std::endl;
			break;

		default: 
			std::cout << "Programmende. " << std::endl; 
			return 0;
		}
	}
}

void parallelFunktion(const int i) {
	int inkrement = i; 
	for (int i = 0; i < 9; ++i) {
		vari += inkrement;
		std::cout << "Inkrement " << i << ", Wert " << vari << std::endl;
	}
}

int blatt1_2_main() {
	std::cout << "Prozesse... " << std::endl;
	vari = 0; 
	//TODO Datei suchen
	_execl("Uebung.exe", "P");
	
	return blatt1_P_main(55);
}

int blatt1_P_main(int inkrement) {
	int eingabe;
	std::cout << "Parallel..." << std::endl;
	parallelFunktion(inkrement);
	std::cin >> eingabe; 
	return 0;
}

int blatt1_3_main() {
	std::cout << "Threads... " << std::endl;
	vari = 0;
	std::thread th1(&parallelFunktion, 1001);
	std::thread th2(&parallelFunktion, 1010);
	std::thread th3(&parallelFunktion, 1100);
	std::cout << "Zwischenergebnis: " << vari;
	th1.join();
	th2.join();
	th3.join();
	return 0;
}