#ifndef __BLUMENSTRAUSSAUTOMAT__H__
#define __BLUMENSTRAUSSAUTOMAT__H__
#include "semaphore.h"

class BlumenstraussAutomat {
public:
	static const int kosten;
private:
	mutable semaphore automatFrei;
	mutable semaphore automatKunde;
	mutable semaphore automatLieferant;
	mutable semaphore automatIdle;
	mutable semaphore automatBlume;
	mutable semaphore automatBlumenlager;
	int geld;
	int blumen;
	static void muenzenThreadExecute(BlumenstraussAutomat *);
	static void lieferantenThreadExecute(BlumenstraussAutomat *);
	void geldEingeworfen(void);
	void lieferantLiefert(void);

public:
	BlumenstraussAutomat();
	void starten(void);
	~BlumenstraussAutomat();
	semaphore & getSemaphoreFrei() const { return this->automatFrei; }
	semaphore & getSemaphoreIdle() const { return this->automatIdle; }
	semaphore & getSemaphoreKunde() const { return this->automatKunde; }
	semaphore & getSemaphoreLieferant() const { return this->automatLieferant; }
	semaphore & getSemaphoreBlume() const { return this->automatBlume; }
};

#endif //__BLUMENSTRAUSSAUTOMAT__H__