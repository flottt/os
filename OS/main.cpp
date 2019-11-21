#ifdef __linux__

#elif _WIN32
#include <Windows.h>
#else
#error "Unknown OS"
#endif

#include <iostream>

extern int blatt1_1_main();
extern int blatt1_2_main();
extern int blatt1_3_main();
extern int blatt1_P_main(int);
extern int semapharen_main(void);
extern int badDiningPhil_main(void);
extern int blatt3_1_main(void);
extern int blatt3_1_kunde_main(bool automatisch);
extern int blatt3_1_lieferant_main(void);

int main(int argc, char ** argv) {
	int eingabe = 0, returnresult = 0;
	
	if (argc > 0) {
		if (argv[0][0] == 'P') {
			return blatt1_P_main(1);
		}
	}

	std::cout << "Betriebssysteme Uebungen" << std::endl;
	std::cout << "11: Blatt 1. Zugriff auf globale Variable ueber mehrere .exe Dateien durch Benutzereingabe" << std::endl; 
	std::cout << "12: Blatt 1. Zugriff auf globale Variable ueber mehrere Prozesse durch Inkrementieren" << std::endl; 
	std::cout << "13: Blatt 1. Zugriff auf globale Variable ueber mehrere Threads durch Inkrementieren" << std::endl; 
	std::cout << "20: eigene Semaphoren-Uebung in Windows" << std::endl;
	std::cout << "21: Dining Philosopher Problem mit Deadlock-Chance" << std::endl;
	std::cout << "31: Blatt 3. Blumenstraussautomat" << std::endl;
	std::cout << "32: Blatt 3. Blumenstraussautomat-Kunde automatisch 2 Blumen" << std::endl;
	std::cout << "33: Blatt 3. Blumenstraussautomat-Kunde manuell" << std::endl;
	std::cout << "34: Blatt 3. Blumenstraussautomat-Lieferant" << std::endl;
	std::cout << "Eingabe: "; 
	std::cin >> eingabe;
	switch (eingabe) {
	case 11: returnresult = blatt1_1_main(); break;
	case 12: returnresult = blatt1_2_main(); break;
	case 13: returnresult = blatt1_3_main(); break;
	case 20: returnresult = semapharen_main(); break;
	case 21: returnresult = badDiningPhil_main(); break;
	case 31: returnresult = blatt3_1_main(); break;
	case 32: returnresult = blatt3_1_kunde_main(true); break;
	case 33: returnresult = blatt3_1_kunde_main(false); break;
	case 34: returnresult = blatt3_1_lieferant_main(); break;
	default:
		break;
	}

#ifdef __linux__
	char cc;
	std::cout << "Ende. Beliebige Eingabe zum beenden: "; 
	std::cin >> cc;
#elif _WIN32
	system("pause");
#endif
	return returnresult;
}