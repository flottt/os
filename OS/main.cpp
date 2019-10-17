#include <iostream>
//TODO system pause

int blatt1_1_main();
int blatt1_2_main();
int blatt1_3_main();
int blatt1_P_main(int);

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
	std::cout << "Eingabe: "; 
	std::cin >> eingabe;
	switch (eingabe) {
	case 11: returnresult = blatt1_1_main(); break;
	case 12: returnresult = blatt1_2_main(); break;
	case 13: returnresult = blatt1_3_main(); break;

	default:
		break;
	}


	return returnresult;
}