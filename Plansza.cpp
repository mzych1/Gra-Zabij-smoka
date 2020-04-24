#include"Plansza.h"
#include<iostream>

using namespace std;

Plansza::Plansza(int a, int b)//[wiersz][kolumna]
{
	y = a;//ilosc wierszy
	x = b;//ilosc kolumn
	tablica = new char *[y];//pierwsza wspolrzedna to numer wiersza
	for (int i = 0; i<y; i++)
		tablica[i] = new char[x];//druga wspolrzedna to numer kolumny

	//ustawinie wszystkich pol jako puste pola (czyli '.')
	for (int i = 0; i<y; i++)
		for (int j = 0; j<x; j++)
			tablica[i][j] = '.';
}

Plansza::~Plansza()//niszczenie tablicy 2wymiarowej
{
	for (int i = 0; i<y; i++)
		delete[] tablica[i];
	delete[] tablica;
}

int Plansza::iloscWierszy()
{
	return y;
}

int Plansza::iloscKolumn()
{
	return x;
}

void Plansza::ustaw(objNaPlanszy& pos)
{

	tablica[pos.podajWiersz()][pos.podajKolumne()] = pos.podajId();
}

void Plansza::ustaw(int x, int y, char id)
{
	tablica[y][x] = id;
}

void Plansza::zdejmij(int x, int y)
{
	tablica[y][x] = '.';
}

char Plansza::podajZnak(int x, int y)
{
	return tablica[y][x];
}

ostream& operator<< (ostream& out, Plansza& pl)//operator wypisania
{
	out << "*******************************" << endl;
	for (int i = 0; i<pl.y; i++)
	{
		for (int j = 0; j < pl.x; j++)
			out << pl.tablica[i][j] << " ";
		out << endl;
	}
	out << endl;
	return out;
}
