#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include <fstream>
#include"funkcje.h"

using namespace std;

PostacGracza* postac;
Plansza* plansza;
Komenda* komenda;
Smok* smok;
vector <objNaPlanszy*> obiekty;
int a, b;
char c;
#define BOK_X 12
#define BOK_Y 12

void menu()
{
	char a;
	while (true)
	{
		cout << "----------GRA ZABIJ SMOKA----------" << endl;
		cout << "1. Zagraj" << endl;
		cout << "2. Pomoc" << endl;
		cout << "3. Wczytaj gre" << endl;
		cout << "4. Wyjscie" << endl;
		cout << "Wybierz 1, 2, 3 lub 4:  ";

		obslugaWczyt(a, false);//false bo nie jest to wczytywanie wyboru postaci
		switch (a)
		{
		case '1': gra(); break;
		case '2': zasady(); sterowanie(); break;
		case '3': wczytajGre(); break;
		case '4': exit(0); break;
		}
	}
}

char wczytaj(bool czyWczytPostaci)
{
	char a;
	cin >> a;
	if (czyWczytPostaci == true && a != '1' && a != '2' && a != '3')
	{
		string wyjatek = "Podano niewlasciwy znak";
		throw wyjatek;
	}
	else if (a!='1' && a!='2' && a!='3' && a!='4')
	{
		string wyjatek = "Podano niewlasciwy znak";
		throw wyjatek;
	}
	return a;
}

void obslugaWczyt(char& x, bool czyWczytPostaci)
{
	try
	{
		x = wczytaj(czyWczytPostaci);
	}
	catch (string w)
	{
		cout <<  w << endl;
		cin.clear();//czyszczenie flagi bledu
		cin.ignore(1000, '\n');
		obslugaWczyt(x, czyWczytPostaci);
	}
}

void gra()
{
	plansza = new Plansza(BOK_Y, BOK_X);//tworzenie planszy na ktorej odbywa sie gra
	komenda = new Komenda;
	wyswietlPostaci();
	cout << "Wybierz 1, 2 lub 3:  ";
	char a;
	obslugaWczyt(a, true);
	switch (a)
	{//tworzenie bohatera gry
	case '1': postac = new Rycerz(*plansza); break;//zrobic tak zeby po zakonczeniu gry ten obiekt sie usuwal
	case '2': postac = new Lucznik(*plansza); break;
	case '3': postac = new Mag(*plansza); break;
	}
	smok = new Smok(*plansza);
	ruch();
}

void sterowanie()
{
	cout << "Sterowanie (komendy dozwolone podczas gry): " << endl;
	cout << "  a-> ruch w lewo" << endl;
	cout << "  w-> ruch do gory" << endl;
	cout << "  s-> ruch do dolu" << endl;
	cout << "  d-> ruch w prawo" << endl;
	cout << "  qa-> atak w lewo/ukos gora lewo" << endl;
	cout << "  qw-> atak w gore/ukos gora prawo" << endl;
	cout << "  qs-> atak w dol/ukos dol lewo" << endl;
	cout << "  qd-> atak w prawo/ ukos dol prawo" << endl;
	cout << "  tr-> rezygnujesz z poruszenia sie, ale zwiekszasz atak" << endl;
	cout << "  od-> rezygnujesz z poruszenia sie, ale zwiekszasz zdrowie" << endl;
	cout << "  pomoc-> wyswietlona zostanie informacja o sterowaniu" << endl;
	cout << "  menu-> powrot do menu poczatkowego" << endl;//napisac
	cout << "  koniec-> wylaczenie gry" << endl;
	cout << "  zapisz-> zapisanie gry" << endl;
	}

void zasady()
{
	cout << "Celem gry jest zabicie smoka. W kazdej kolejce gry mozesz sie poruszyc," << endl;
	cout << " atakowac, trenowac lub odpoczac. Poruszajac sie mozesz zbierac " << endl;
	cout << "jedzenie (o) zwiekszajace zdrowie oraz bron (-) ktorej posiadanie" << endl;
	cout << "umozliwi atakowanie smoka. Sposob ataku zalezy od tego jaka postacia" << endl;
	cout << "jestes(rycerz / lucznik / mag) - jest to przedstawione w opisie postaci." << endl;
	cout << "Trenownie/odpoczynek oznacza ze nie wykonasz kroku, ale zwiekszysz " << endl;
	cout << "atak/zdrowie. Jesli smok wejdzie na postac, zdrowie maleje w zaleznosci" << endl;
	cout << "od posiadanego pancerza (zmniejsza sie o 100-pancerz). Przy ataku na " << endl;
	cout << "smoka zadane mu obrazenia sa zalezne od ataku postaci (zdrowie smoka " << endl;
	cout << "zmniejsza sie o atak postaci)." << endl;
	cout<< "Wygrana: zabicie smoka (spowodowanie ze jego zdrowie = 0)"<<endl;
	cout << "Przegrana: zdrowie postaci = 0" << endl;
	cout << endl;
}

void koniec()
{
	usunObiekty();//usuwanie wszystkich obiektow jakie zostaly stworzone
	exit(0);
}

void wyswietlPostaci()
{
	cout << "Wybierz jaka postacia chcesz byc: " << endl;
	cout << "1.Rycerz (R)" << endl;
	cout << "  zdrowie: 85/85 (odpoczynek: +5)" << endl;
	cout << "  atak: 20/80 (trening: +8)" << endl;
	cout << "  pancerz: 70" << endl;
	cout << "  bron: miecz (mozna zadac cios stojac przy smoku na ukos od niego)" << endl;
	cout << "   sytuacje w ktorych mozna atakowac przedstawione ponizej(R-rycerz, S-smok):" << endl;
	cout << "    R . .  " << "    . . R  " << "    . . .  " << "    . . .  " << endl;
	cout << "    . S .  " << "    . S .  " << "    . S .  " << "    . S .  " << endl;
	cout << "    . . .  " << "    . . .  " << "    R . .  " << "    . . R  " << endl;

	cout << "2.Lucznik (L)" << endl;
	cout << "  zdrowie: 70/70 (odpoczynek: +5)" << endl;
	cout << "  atak: 10/40 (trening: +6)" << endl;
	cout << "  pancerz: 40" << endl;
	cout << "  bron: luk (mozna zadac cios stojac w tym samym wierszu/kolumnie co smok)" << endl;
	cout << "   mozna atakowac jesli smoka i postac dziela nie wiecej niz 2 pola (kropki)" << endl;
	cout << "   przykladowe sytuacje w ktorych mozna atakowac(L-lucznik, S-smok):" << endl;
	cout << "    L . . S      L . S .      . L S .    S . . L      S . L .      . S L . " << endl;
	cout << "   oraz analogiczne sytuacje w pionie" << endl;

	cout << "3.Mag (M)" << endl;
	cout << "  zdrowie: 80/80 (odpoczynek: +5)" << endl;
	cout << "  atak: 5/50 (trening: +10)" << endl;
	cout << "  pancerz: 60" << endl;
	cout << "  bron: zaklecia (mozna zadac cios stojac na ukos od smoka)" << endl;
	cout << "   mozna atakowac jesli smoka i postac dziela nie wiecej niz 2 pola (kropki)" << endl;
	cout << "   przykladowe sytuacje w ktorych mozna atakowac(M-mag, S-smok):" << endl;
	cout << "    M . .  " << "    M . .  " << "    M . . .  " << endl;
	cout << "    . S .  " << "    . . .  " << "    . . . .  " << endl;
	cout << "    . . .  " << "    . . S  " << "    . . . .  " <<  endl;
	cout << "    . . .  " << "    . . .  " << "    . . . S  " <<  endl;
	cout << "   oraz inne analogiczne sytuacje" << endl;
}

void ruch(bool czyWczytywanie)
{
	srand(time(NULL));
	bool czyWykonanoRuch = true;
	int los;

	if (czyWczytywanie == false)//przy pierwszym ruchu po wczytaniu gry nie pojawia sie jedzenie/bron
	{
		obiekty.push_back(new Jedzenie(*plansza));//utworzenie 1 jedzenia i broni przed zaczeciem gry
		obiekty.push_back(new Bron(*plansza));
	}

	while (true)
	{
		try
		{
			if (czyWykonanoRuch)
			{
				if (czyWczytywanie == false)//przy pierwszym ruchu po wczytaniu gry smok sie nie porusza
				{
					smok->ruch(*plansza, *postac);

					los = rand() % 12;
					switch (los)//mniej wiecej co 6 ruch bedzie pojawiac sie jedzenie lub bron
					{
					case 1: obiekty.push_back(new Jedzenie(*plansza)); break;
					case 0: obiekty.push_back(new Bron(*plansza)); break;
					}
				}
				czyWczytywanie = false;//pozniej juz za kazdym razem smok ma sie poruszyc

				cout << *plansza;
				smok->wypisz();
				postac->wypisz();
			}
			cout << "Podaj wybor dzialania w tej kolejce: ";
			cin >> *komenda;
			smok->Atakowal(false);//ustawienie znacznika ze w tej kolejce smok nie zadal obrazen postaci
			komenda->wykonaj(*postac, *plansza, czyWykonanoRuch, *smok);
		}
		catch (string koniec)//powrot do menu i zakonczenie poprzedniej gry
		{
			if (koniec == "przegrana" || koniec == "wygrana")
			{
				cout << *plansza;
				smok->wypisz();
				postac->wypisz();
			}
			usunObiekty();
			menu();
		}
	}
}

void usunZebranyObiekt(int x, int y, char c)
{
	a = x;
	b = y;
	::c = c;
	vector <objNaPlanszy*> ::iterator it = find_if(obiekty.begin(), obiekty.end(), czyZebrany);//szukanie obiektu ktory ma zostac usuniety (bo zostal zebrany)
	delete *it;
	obiekty.erase(it);//usuwanie odpowiedniego elementu wektora
}

void usunObiekty()
{
	delete plansza;
	delete postac;
	delete smok;
	for (int i = 0; i < obiekty.size(); i++)//usuwanie jedzenia i broni
		delete obiekty[i];
	obiekty.clear();
	delete komenda;
}

bool czyZebrany(objNaPlanszy* ob)//funkcja potrzebna do algorytmu przeszukiwania wektora
{
	if (ob->podajId()==c && ob->podajKolumne()==a && ob->podajWiersz()==b)
		return true;
	else
		return false;
}

void wczytajGre()
{
	try
	{
		int x, y, z;
		char d;
		string wyj;
		fstream plik;
		plik.open("gra.txt", ios::in);
		if (plik.good() == false)
		{
			wyj = "Nie udalo sie otworzyc pliku";
			throw wyj;
		}

		wyj = "Blad wczytywania- bledny wymiar planszy";
		plik >> y >> x;
		if (plik.good() == 0 || y <= 0 || x <= 0) throw wyj;
		plansza = new Plansza(y, x);//utworzenie odpowiedniej planszy

		wyj = "Blad wczytywania- bledne dane o smoku";
		plik >> z >> x >> y;
		if (plik.good() == 0 || y < 0 || x < 0 || z < 0 || y >= plansza->iloscWierszy() || x >= plansza->iloscKolumn())
			throw wyj;
		smok = new Smok(*plansza, z, x, y);//tworenie odpowiedniego smoka

		wyj = "Blad wczytywania- bledne dane o postaci";
		plik >> d >> x >> y;
		if (plik.good() == 0 || y < 0 || x < 0 || y >= plansza->iloscWierszy() || x >= plansza->iloscKolumn())
			throw wyj;

		switch (d)
		{//tworzenie bohatera gry
		case 'R': postac = new Rycerz(*plansza, x, y); break;
		case 'L': postac = new Lucznik(*plansza, x, y); break;
		case 'M': postac = new Mag(*plansza, x, y); break;
		default: throw wyj; break;
		}
		plik >> *postac;//wczytywanie danych o postaci i sprawdzanie czy sa poprawne
		komenda = new Komenda();
		wyj= "Blad wczytywania- bledne dane o przedmiotach";
		plik >> z;
		if (plik.good() == 0 || z < 0)
			throw wyj;
		for (int i = 0; i < z; i++)//wczytywanie info o przedmiotach na planszy (jedzeniu i broni)
		{
			plik >> d >> x >> y;
			if (plik.good() == 0 || y < 0 || x < 0 || y >= plansza->iloscWierszy() || x >= plansza->iloscKolumn() || plansza->podajZnak(x, y) != '.')
				throw wyj;
			switch (d)
			{
			case 'o': obiekty.push_back(new Jedzenie(*plansza, x, y)); break;
			case '-': obiekty.push_back(new Bron(*plansza, x, y)); break;
			default: throw wyj; break;
			}
		}

		ruch(true);//true, bo to zaczecie gry poprzez wczytywanie (maja nie pojawic sie zadne nowe obiekty i smok ma sie nie poruszyc)
		plik.close();
	}
	catch (string s)
	{
		cout << s << endl;
		if (s == "Blad wczytywania- bledne dane o smoku")
			delete plansza;//bo do momentu wystapienia tego bledu stworzono tylko plansze
		else if (s == "Blad wczytywania- bledne dane o postaci")
		{
			delete plansza;
			delete smok;
		}
		else if (s == "Blad wczytywania - bledne dane o parametrach postaci")
		{
			delete plansza;
			delete smok;
			delete postac;
		}
		else if (s == "Blad wczytywania- bledne dane o przedmiotach")
			usunObiekty();
	}
}

void zapiszGre()
{
	try
	{
		fstream plik;
		plik.open("gra.txt", ios::out);
		if (plik.good() == false)
		{
			string wyj = "Nie udalo sie otworzyc pliku";
			throw wyj;
		}
		//zapisywanie potrzebnych informacji do pliku
		plik << plansza->iloscWierszy() << " " << plansza->iloscKolumn() << endl;//info o wymiarasz planszy
		plik << *smok;//info o smoku (zdrowie i polozenie)- zdrowie x y
		plik << *postac;//info o postaci (wszytskie parametry)- id x y atakMax atak bron zdrowieMax zdrowie pancerz
		plik << obiekty.size() << endl;//ilosc przedmiotow typu jedzenie/bron
		for (int i = 0; i < obiekty.size(); i++)//identyfikatory i polozenie jedzenia i broni: id x y
			plik << *obiekty[i];

		plik.close();
	}
	catch (string s)
	{
		cout << s << endl;
	}
}

void atakNaPostac()
{
	if ((smok->czyAtakowal()) == false)
	{
		cout << "Zostales zaatakowany przez smoka!" << endl;;
		smok->Atakowal(true);//ustawienie ze w tej kolejce smok juz zadal obrazenia
		postac->zadajObrazenia();
	}
}
