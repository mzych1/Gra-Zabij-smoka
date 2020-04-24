#ifndef FUNKCJE_H
#define FUNKCJE_H

#include"Postac.h"
#include"Plansza.h"
#include"Komenda.h"

class objNaPlanszy;

void menu();
void obslugaWczyt(char&, bool), wczytajGre(), zapiszGre(), atakNaPostac();
void gra(), zasady(), sterowanie(), wyswietlPostaci(), koniec();
void ruch(bool=false), usunZebranyObiekt(int, int, char), usunObiekty();
char wczytaj(bool);
bool czyZebrany(objNaPlanszy*);


#endif
