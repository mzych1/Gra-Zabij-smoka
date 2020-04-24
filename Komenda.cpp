#include"Komenda.h"
#include<string>
#include<iostream>

using namespace std;

Komenda::Komenda()
{
	tresc = " ";
}

void Komenda::wykonaj(PostacGracza& pos, Plansza& pl, bool& czyWykonanoRuch, Smok& sm)
{
	if (tresc == "koniec")
		koniec();
	else if (tresc == "a")
		pos.ruch(pl, 'a', czyWykonanoRuch);
	else if (tresc == "w")
		pos.ruch(pl, 'w', czyWykonanoRuch);
	else if (tresc == "s")
		pos.ruch(pl, 's', czyWykonanoRuch);
	else if (tresc == "d")
		pos.ruch(pl, 'd', czyWykonanoRuch);
	else if (tresc == "tr")
		pos.trenuj(czyWykonanoRuch);
	else if (tresc == "od")
		pos.odpocznij(czyWykonanoRuch);
	else if (tresc == "pomoc")
	{
		sterowanie();
		czyWykonanoRuch = false;
	}
	else if (tresc == "menu")
	{
		string wyjatek = "koniecGry";
		throw wyjatek;
	}
	else if (tresc == "zapisz")
	{
		zapiszGre();
		czyWykonanoRuch = false;
	}
	else if (tresc == "qw")
	{
		pos.atakqw(pl, czyWykonanoRuch, sm);
	}
	else if (tresc == "qa")
	{
		pos.atakqa(pl, czyWykonanoRuch, sm);
	}
	else if (tresc == "qs")
	{
		pos.atakqs(pl, czyWykonanoRuch, sm);
	}
	else if (tresc == "qd")
	{
		pos.atakqd(pl, czyWykonanoRuch, sm);
	}
}

istream& operator>>(istream& in, Komenda& kom)//przeciazenie strumienia wejscia
{
	do
	{
		in >> kom.tresc;
	} while (kom.tresc!="a" && kom.tresc != "w" && kom.tresc != "s" && kom.tresc != "d" && kom.tresc!="koniec" && kom.tresc != "tr" && kom.tresc != "od" &&
		kom.tresc != "pomoc" && kom.tresc != "menu" && kom.tresc!="zapisz" && kom.tresc != "qw" && kom.tresc != "qa" && kom.tresc != "qs" && kom.tresc != "qd");
	//wczytywanie tylko komend ktore sa dopuszczalne w grze
	return in;
}
