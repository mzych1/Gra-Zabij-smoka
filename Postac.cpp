#include"Postac.h"
#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define RYCERZ_TRENING 8
#define LUCZNIK_TRENING 6
#define MAG_TRENING  10
#define ODPOCZYNEK 5

//objNaPlanszy
int objNaPlanszy::podajKolumne()
{
	return x;
}

int objNaPlanszy::podajWiersz()
{
	return y;
}

char objNaPlanszy::podajId()
{
	return id;
}

ostream& operator<<(ostream& out, objNaPlanszy& ob)//przeciazenie operatora wypisania
{
	out << ob.id << " " << ob.x << " " << ob.y << endl;
	return out;
}

//Jedzenie
Jedzenie::Jedzenie(Plansza& pl)
{
	srand(time(NULL));

	id = 'o';
	do
	{//losowanie niezajetego miejsca dla jedzenia
		x = rand() % pl.iloscKolumn();
		y = rand() % pl.iloscWierszy();
	} while (pl.podajZnak(x, y) != '.');

	pl.ustaw(*this);
}

Jedzenie::Jedzenie(Plansza& pl, int xx, int yy)
{
	id = 'o';
	x = xx;
	y = yy;
	pl.ustaw(*this);
}

//Bron
Bron::Bron(Plansza& pl)
{
	srand(time(NULL));

	id = '-';
	do
	{
		x = rand() % pl.iloscKolumn();
		y = rand() % pl.iloscWierszy();
	} while (pl.podajZnak(x, y) != '.');

	pl.ustaw(*this);
}

Bron::Bron(Plansza& pl, int xx, int yy)
{
	id = '-';
	x = xx;
	y = yy;
	pl.ustaw(*this);
}

//Postac
void Postac::ruchLewa(Plansza& pl, bool& czyWykonanoRuch)//komenda a
{
	if (x == 0)//postac jest na krawedzi planszy
	{
		czyWykonanoRuch = false;
	}
	else
	{
		pl.zdejmij(x, y);
		x--;

		if (pl.podajZnak(x, y) == 'o' || pl.podajZnak(x, y) == '-')//zbieranie jedzenia/broni
			this->zbierzObiekt(x, y, pl.podajZnak(x, y));
		else if (pl.podajZnak(x, y) == 'S' || pl.podajZnak(x, y) == 'R' || pl.podajZnak(x, y) == 'L' || pl.podajZnak(x, y) == 'M')
		{
			atakNaPostac();
			x++;//ustawienie na z powrotem na tym samym miejscu
		}

		pl.ustaw(*this);
		czyWykonanoRuch = true;
	}
}

void Postac::ruchGora(Plansza& pl, bool& czyWykonanoRuch)//komenda w 
{
	if (y == 0)
	{
		czyWykonanoRuch = false;
	}
	else
	{
		pl.zdejmij(x, y);
		y--;

		if (pl.podajZnak(x, y) == 'o' || pl.podajZnak(x, y) == '-')//zbieranie jedzenia/broni
			this->zbierzObiekt(x, y, pl.podajZnak(x, y));
		else if (pl.podajZnak(x, y) == 'S' || pl.podajZnak(x, y) == 'R' || pl.podajZnak(x, y) == 'L' || pl.podajZnak(x, y) == 'M')
		{
			atakNaPostac();
			y++;//ustawienie na z powrotem na tym samym miejscu
		}

		pl.ustaw(*this);
		czyWykonanoRuch = true;
	}
}

void Postac::ruchDol(Plansza& pl, bool& czyWykonanoRuch)//komenda s
{
	if (y == pl.iloscWierszy() - 1)
	{
		czyWykonanoRuch = false;
	}
	else
	{
		pl.zdejmij(x, y);
		y++;

		if (pl.podajZnak(x, y) == 'o' || pl.podajZnak(x, y) == '-')//zbieranie jedzenia/broni
			this->zbierzObiekt(x, y, pl.podajZnak(x, y));
		else if (pl.podajZnak(x, y) == 'S' || pl.podajZnak(x, y) == 'R' || pl.podajZnak(x, y) == 'L' || pl.podajZnak(x, y) == 'M')
		{
			atakNaPostac();
			y--;//ustawienie na z powrotem na tym samym miejscu
		}

		pl.ustaw(*this);
		czyWykonanoRuch = true;
	}
}

void Postac::ruchPrawa(Plansza& pl, bool& czyWykonanoRuch)//komenda d
{
	if (x == pl.iloscKolumn() - 1)
	{
		czyWykonanoRuch = false;
	}
	else
	{
		pl.zdejmij(x, y);
		x++;

		if (pl.podajZnak(x, y) == 'o' || pl.podajZnak(x, y) == '-')//zbieranie jedzenia/broni
			this->zbierzObiekt(x, y, pl.podajZnak(x, y));
		else if (pl.podajZnak(x, y) == 'S' || pl.podajZnak(x, y) == 'R' || pl.podajZnak(x, y) == 'L' || pl.podajZnak(x, y) == 'M')
		{
			atakNaPostac();
			x--;//ustawienie na z powrotem na tym samym miejscu
		}

		pl.ustaw(*this);
		czyWykonanoRuch = true;
	}
}

//PostacGracza
ostream& operator<< (ostream& out, PostacGracza& pos)//operator wypisania, przy zapisie do pliku
{
	out << pos.id << " " << pos.x << " " << pos.y << " " << pos.atakMax << " " << pos.atak << " " << pos.bron;
	out << " " << pos.zdrowieMax << " " << pos.zdrowie << " " << pos.pancerz << endl;
	return out;
}

istream& operator>>(istream& in, PostacGracza& pos)
{
	string wyj = "Blad wczytywania - bledne dane o parametrach postaci";
	in >> pos.atakMax >> pos.atak >> pos.bron >> pos.zdrowieMax >> pos.zdrowie >> pos.pancerz;
	if (in.good() == false || pos.atakMax < 0 || pos.atak < 0 || pos.bron < 0 || pos.zdrowieMax < 0 || pos.zdrowie < 0 || pos.pancerz < 0)
		throw wyj;
	if (pos.atakMax < pos.atak || pos.zdrowieMax < pos.zdrowie)
		throw wyj;

	return in;
}

void PostacGracza::wypisz()
{
	cout << "  POSTAC" << endl;
	cout << "zdrowie: " << zdrowie << "/" << zdrowieMax << endl;
	cout << "atak: " << atak << "/" << atakMax << endl;
	cout << "pancerz: " << pancerz << endl;
	cout << "bron: " << bron << endl;
}

void PostacGracza::trenujPos(bool& czyWykonanoRuch, const int t)//t to wartos o jaka wzrosnie atak
{
	if (atak == atakMax)
	{
		cout << "Nie mozna wykonac tego ruchu, masz juz maksymalny atak" << endl;
		czyWykonanoRuch = false;
	}
	else
	{
		czyWykonanoRuch = true;
		if (atak + t >= atakMax)
			atak = atakMax;
		else
			atak += t;
	}
}

void PostacGracza::odpocznij(bool& czyWykonanoRuch)
{
	if (zdrowie == zdrowieMax)
	{
		cout << "Nie mozna wykonac tego ruchu, masz juz maksymalne zdrowie" << endl;
		czyWykonanoRuch = false;
	}
	else
	{
		czyWykonanoRuch = true;
		if (zdrowie + ODPOCZYNEK >= zdrowieMax)
			zdrowie = zdrowieMax;
		else
			zdrowie += ODPOCZYNEK;
	}
}

void PostacGracza::ruch(Plansza& pl, char str, bool& czyWykonanoRuch)
{
	switch (str)
	{
	case('a'): this->ruchLewa(pl, czyWykonanoRuch); break;
	case('w'): this->ruchGora(pl, czyWykonanoRuch); break;
	case('s'): this->ruchDol(pl, czyWykonanoRuch); break;
	case('d'): this->ruchPrawa(pl, czyWykonanoRuch); break;
	}
	if (czyWykonanoRuch == false)
		cout << "Nie mozna wykonac tego ruchu" << endl;
}

void PostacGracza::zadajObrazenia()
{
	cout << "ZDROWIE -" << 100 - pancerz << endl;

	if (zdrowie - 100 + pancerz <= 0)
	{
		string wyj = "przegrana";
		zdrowie = 0;
		cout << "Zastales zabity przez smoka!" << endl;
		cout << "KONIEC GRY - przegrales" << endl;
		throw wyj;//powoduje usuniecie obiektow i powrot do menu
	}
	else
	{
		zdrowie = zdrowie - 100 + pancerz;
	}
}

void PostacGracza::zbierzObiekt(int a, int b, char c)
{
	if (c == 'o')
	{
		if (zdrowie + 5 >= zdrowieMax)
			zdrowie = zdrowieMax;
		else
			zdrowie += 5;
	}
	else if (c == '-')
		bron++;

	usunZebranyObiekt(a, b, c);
}

//Smok
void Smok::ruch(Plansza&pl, PostacGracza& pos)
{
	srand(time(NULL));
	bool czyWykonanoRuch = false;

	while (czyWykonanoRuch == false)
	{
		switch (rand() % 10)
		{
		case 0: this->ruchLewa(pl, czyWykonanoRuch); break;
		case 1: this->ruchGora(pl, czyWykonanoRuch); break;
		case 2: this->ruchDol(pl, czyWykonanoRuch); break;
		case 3: this->ruchPrawa(pl, czyWykonanoRuch); break;
		default: //w pozostalych przypadkach ma sie poruszac w strone gracza
			if (pos.podajKolumne()<x)
				this->ruchLewa(pl, czyWykonanoRuch);
			else if (pos.podajWiersz()<y)
				this->ruchGora(pl, czyWykonanoRuch);
			else if (pos.podajKolumne()>x)
				this->ruchPrawa(pl, czyWykonanoRuch);
			else
				this->ruchDol(pl, czyWykonanoRuch);
			break;
		}
	}
}

Smok::Smok(Plansza& pl)//najpierw musi byc tworzony smok, a pozniej jakies jedzenie/bron
{
	srand(time(NULL));

	czyZadalObrazenia = false;
	id = 'S';
	zdrowie = 200;

	x = rand() % (pl.iloscKolumn() / 3) + pl.iloscKolumn() / 3;//tak aby smok byl na poczatku mniej wiecej na srodku planszy
	y = rand() % (pl.iloscWierszy() / 3) + pl.iloscWierszy() / 3;

	pl.ustaw(*this);
}

Smok::Smok(Plansza& pl, int z, int xx, int yy)
{
	czyZadalObrazenia = false;
	id = 'S';
	zdrowie = z;
	x = xx;
	y = yy;
	pl.ustaw(*this);
}

void Smok::Atakowal(bool b)//ustawienie ze smok zaatakowal juz postac w danej kolejce
{
	czyZadalObrazenia = b;
}

bool Smok::czyAtakowal()
{
	return czyZadalObrazenia;
}

void Smok::zadajObrazenia(int obr)
{
	cout << "Zaatakowales smoka!" << endl;
	cout << "ZDROWIE SMOKA -" << obr << endl;;
	if (zdrowie - obr <= 0)
	{
		string wyj = "wygrana";
		zdrowie = 0;
		cout << "Zabiles smoka!" << endl;
		cout << "KONIEC GRY - wygrales" << endl;
		throw wyj;//powoduje usuniecie obiektow i powrot do menu
	}
	else
		zdrowie = zdrowie - obr;
}

ostream& operator<< (ostream& out, Smok& sm)//operator wypisania, zapis do pliku
{
	out << sm.zdrowie << " " << sm.x << " " << sm.y << endl;//zdrowie kolumna wiersz
	return out;
}

istream& operator>>(istream& in, Smok& sm) //wczytywanie informacji o smoku
{
	string wyj = "Blad wczytywania- bledne dane w pliku";
	in >> sm.zdrowie >> sm.x >> sm.y;
	if (in.good() == 0 || sm.zdrowie < 0 || sm.x < 0 || sm.y < 0) throw wyj;
	return in;
}

void Smok::wypisz()
{
	cout << "   SMOK" << endl << "zdrowie: " << zdrowie << endl;
}

void Smok::zbierzObiekt(int a, int b, char c)
{
	usunZebranyObiekt(a, b, c);
}

//Rycerz
Rycerz::Rycerz(Plansza& pl)//a to ilosc wierszy planszy, b-kolumn
{
	int a = pl.iloscWierszy();
	int b = pl.iloscKolumn();

	srand(time(NULL));
	int pozycja = rand() % 4;
	id = 'R';
	switch (pozycja)//ustawieniejpostaci w jednym z rogow planszy
	{//x to kolumna, y to wiersz
	case 0: x = 0; y = 0; break;
	case 1: x =b-1; y = 0; break;
	case 2: x = b-1; y = a-1; break;
	case 3: x = 0; y = a-1; break;
	}
	atak = 20;
	atakMax = 80;
	bron = 0;
	zdrowie = 85;
	zdrowieMax = 85;
	pancerz = 70;

	pl.ustaw(*this);
}

Rycerz::Rycerz(Plansza& pl, int xx, int yy)
{
	id = 'R';
	x = xx;
	y = yy;
	string wyj = "Blad wczytywania - bledne dane o parametrach postaci";
	if (pl.podajZnak(x, y) != '.')//proba ustawienia postaci w miejscu juz zajetym (np przez smoka)
		throw wyj;
	pl.ustaw(*this);
}

void Rycerz::trenuj(bool& czyWykonanoRuch)
{
	this->trenujPos(czyWykonanoRuch, RYCERZ_TRENING);
}

void Rycerz::atakqs(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x - 1 >= 0 && y + 1 < pl.iloscWierszy() && pl.podajZnak(x - 1, y + 1) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Rycerz::atakqa(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x - 1 >= 0 && y - 1 >= 0 && pl.podajZnak(x - 1, y - 1) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Rycerz::atakqw(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x + 1 < pl.iloscKolumn() && y - 1 >= 0 && pl.podajZnak(x + 1, y - 1) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Rycerz::atakqd(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x + 1 <pl.iloscKolumn() && y + 1 < pl.iloscWierszy() && pl.podajZnak(x + 1, y + 1) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

//Lucznik
Lucznik::Lucznik(Plansza& pl)
{
	int a = pl.iloscWierszy();
	int b = pl.iloscKolumn();

	srand(time(NULL));
	int pozycja = (int)(rand() % 4);
	id = 'L';
	switch (pozycja)//ustawieniejpostaci w jednym z rogow planszy
	{
	case 0: x = 0; y = 0; break;
	case 1: x = b - 1; y = 0; break;
	case 2: x = b - 1; y = a - 1; break;
	case 3: x = 0; y = a - 1; break;
	}
	atak = 10;
	atakMax = 40;
	bron = 0;
	zdrowie = 70;
	zdrowieMax = 70;
	pancerz = 40;

	pl.ustaw(*this);
}

Lucznik::Lucznik(Plansza& pl, int xx, int yy)
{
	id = 'L';
	x = xx;
	y = yy;
	string wyj = "Blad wczytywania - bledne dane o parametrach postaci";
	if (pl.podajZnak(x, y) != '.')//proba ustawienia postaci w miejscu juz zajetym (np przez smoka)
		throw wyj;
	pl.ustaw(*this);
}

void Lucznik::trenuj(bool& czyWykonanoRuch)
{
	this->trenujPos(czyWykonanoRuch, LUCZNIK_TRENING);
}

void Lucznik::atakqs(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)//atak do dolu
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;
		if (y + 1 < pl.iloscWierszy() && pl.podajZnak(x, y + 1) == 'S')
			sm.zadajObrazenia(atak);
		else if (y + 2 < pl.iloscWierszy() && pl.podajZnak(x, y + 2) == 'S')
			sm.zadajObrazenia(atak);
		else if (y + 3 < pl.iloscWierszy() && pl.podajZnak(x, y + 3) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Lucznik::atakqa(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)//atak w lewo
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;
		if (x - 1 >= 0 && pl.podajZnak(x - 1, y) == 'S')
			sm.zadajObrazenia(atak);
		else if (x - 2 >= 0 && pl.podajZnak(x - 2, y) == 'S')
			sm.zadajObrazenia(atak);
		else if (x - 3 >= 0 && pl.podajZnak(x - 3, y) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Lucznik::atakqw(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;
		if (y - 1 >= 0 && pl.podajZnak(x, y - 1) == 'S')
			sm.zadajObrazenia(atak);
		else if (y - 2 >= 0 && pl.podajZnak(x, y - 2) == 'S')
			sm.zadajObrazenia(atak);
		else if (y - 3 >= 0 && pl.podajZnak(x, y - 3) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Lucznik::atakqd(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;
		if (x + 1 < pl.iloscKolumn() && pl.podajZnak(x + 1, y) == 'S')
			sm.zadajObrazenia(atak);
		else if (x + 2 < pl.iloscKolumn() && pl.podajZnak(x + 2, y) == 'S')
			sm.zadajObrazenia(atak);
		else if (x + 3 < pl.iloscKolumn() && pl.podajZnak(x + 3, y) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

//Mag
Mag::Mag(Plansza& pl)
{
	int a = pl.iloscWierszy();
	int b = pl.iloscKolumn();

	srand(time(NULL));
	int pozycja = rand() % 4;
	id = 'M';
	switch (pozycja)//ustawieniejpostaci w jednym z rogow planszy
	{
	case 0: x = 0; y = 0; break;
	case 1: x = b - 1; y = 0; break;
	case 2: x = b - 1; y = a - 1; break;
	case 3: x = 0; y = a - 1; break;
	}
	atak = 5;
	atakMax = 50;
	bron = 0;
	zdrowie = 80;
	zdrowieMax = 80;
	pancerz = 60;

	pl.ustaw(*this);
}

Mag::Mag(Plansza& pl, int xx, int yy)
{
	id = 'M';
	x = xx;
	y = yy;
	string wyj = "Blad wczytywania - bledne dane o parametrach postaci";
	if (pl.podajZnak(x, y) != '.')//proba ustawienia postaci w miejscu juz zajetym (np przez smoka)
		throw wyj;
	pl.ustaw(*this);
}

void Mag::trenuj(bool& czyWykonanoRuch)
{
	this->trenujPos(czyWykonanoRuch, MAG_TRENING);
}

void Mag::atakqs(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x - 1 >= 0 && y + 1 < pl.iloscWierszy() && pl.podajZnak(x - 1, y + 1) == 'S')
			sm.zadajObrazenia(atak);
		else if (x - 2 >= 0 && y + 2 < pl.iloscWierszy() && pl.podajZnak(x - 2, y + 2) == 'S')
			sm.zadajObrazenia(atak);
		else if (x - 3 >= 0 && y + 3 < pl.iloscWierszy() && pl.podajZnak(x - 3, y + 3) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Mag::atakqa(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x - 1 >= 0 && y - 1 >= 0 && pl.podajZnak(x - 1, y - 1) == 'S')
			sm.zadajObrazenia(atak);
		else if (x - 2 >= 0 && y - 2 >= 0 && pl.podajZnak(x - 2, y - 2) == 'S')
			sm.zadajObrazenia(atak);
		else if (x - 3 >= 0 && y - 3 >= 0 && pl.podajZnak(x - 3, y - 3) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Mag::atakqw(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x + 1 < pl.iloscKolumn() && y - 1 >= 0 && pl.podajZnak(x + 1, y - 1) == 'S')
			sm.zadajObrazenia(atak);
		else if (x + 2 < pl.iloscKolumn() && y - 2 >= 0 && pl.podajZnak(x + 2, y - 2) == 'S')
			sm.zadajObrazenia(atak);
		else if (x + 3 < pl.iloscKolumn() && y - 3 >= 0 && pl.podajZnak(x + 3, y - 3) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}

void Mag::atakqd(Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (bron == 0)
	{
		czyWykonanoRuch = false;
		cout << "Nie posiadasz broni wiec nie mozesz atakowac" << endl;
	}
	else
	{
		czyWykonanoRuch = true;
		bron--;

		if (x + 1 <pl.iloscKolumn() && y + 1 < pl.iloscWierszy() && pl.podajZnak(x + 1, y + 1) == 'S')
			sm.zadajObrazenia(atak);
		else if (x + 2 <pl.iloscKolumn() && y + 2 < pl.iloscWierszy() && pl.podajZnak(x + 2, y + 2) == 'S')
			sm.zadajObrazenia(atak);
		else if (x + 3 <pl.iloscKolumn() && y + 3 < pl.iloscWierszy() && pl.podajZnak(x + 3, y + 3) == 'S')
			sm.zadajObrazenia(atak);
		else
			cout << "Nie trafiles w smoka" << endl;
	}
}