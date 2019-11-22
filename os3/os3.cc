#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

sem_t zoneA, zoneB, zoneC;

class flieger {
  private:
  void generateRandomName(void);

  public:
  char name[11];
  flieger * next;
  pthread_t tid;

  flieger(flieger * prev) {
    this->next = prev;
    this->generateRandomName();
  }
  ~flieger() {
    delete this->next;
    this->next = nullptr;
  }
  void ankommen(void);
  void threadStart(void);
};

void * fliegerKommtAn(void * f);

void flieger::generateRandomName(void) {
  char * nameTo = this->name;
  for (int len = 9; len > 0; len--) {
    *nameTo = (rand() % 26) + 'A';
    ++nameTo;
  }
  *nameTo = '\0';
}

void flieger::ankommen(void) {
  printf("Flugzeug %s kommt \n", name);
  sem_wait(&zoneC);
  printf("Flugzeug %s fliegt in Zone C ein. \n", this->name);
  sleep(1);
  sem_wait(&zoneB);
  printf("Flugzeug %s fliegt in Zone B ein. \n", this->name);
  sleep(1);
  sem_post(&zoneC);
  sem_wait(&zoneA);
  printf("Flugzeug %s fliegt in Zone A ein. \n", this->name);
  sleep(1);
  printf("Flugzeug %s landet. \n", this->name);
  sem_post(&zoneB);
  sleep(2);
  printf("Flugzeug %s ist gelandet. \n", this->name);
  sem_post(&zoneA);
}

void flieger::threadStart(void) {
  pthread_create(&(this->tid), nullptr, &fliegerKommtAn, this);
}

void * fliegerKommtAn(void * f) {
  ((flieger *)f)->ankommen();
  return nullptr;
}

int main(void) {
  printf("OS Blatt 3 Aufgabe 2\n");
  srand(time(0));
  int anzahl = -1;
  printf("Anzahl ankommender Flieger: ");
  scanf("%i", &anzahl);
  sem_init(&zoneA, 0, 1);
  sem_init(&zoneB, 0, 3);
  sem_init(&zoneC, 0, 7);
  flieger * liste = nullptr;
  for (int i = 0; i < anzahl; i++) {
    liste = new flieger(liste);
    liste->threadStart();
  }
  void * returning;
  for (flieger * liste2 = liste; liste2 != nullptr; liste2 = liste2->next) {
    pthread_join(liste2->tid, &returning);
  }

  //flugzeugKommt("MM");
  delete liste;
  return 0;
}
