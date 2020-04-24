#ifndef PLANSZA_H
#define PLANSZA_H

#include<iostream>
#include"Postac.h"

class objNaPlanszy;

using namespace std;

class Plansza
{
private:
	int x, y;//ilosc kolumn i wierszy planszy
	char **tablica;//tablica 2wymiarowa
public:
	Plansza(int, int);
	~Plansza();
	int iloscWierszy();//zwraca ilosc wierszy
	int iloscKolumn();//zwraca ilosc kolumn
	void ustaw(objNaPlanszy &);
	void ustaw(int, int, char);
	void zdejmij(int, int);//oznaczenie ze postac nie bedzie juz stala na polu na kktorym aktualnie stoi
	char podajZnak(int, int);
	friend ostream& operator<<(ostream&, Plansza&);//przeciazenie operatora wypisania
};

#endif
