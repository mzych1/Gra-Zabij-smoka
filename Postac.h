#ifndef POSTAC_H
#define POSTAC_H

#include<iostream>
#include"Plansza.h"
#include"funkcje.h"
class Plansza;
class Smok;

using namespace std;

class objNaPlanszy //jedzenie/bron pojawiajaca sie na planszy, klasa abstrakcyjna
{
protected:
	char id;
	int x, y;//x to kolumna, y to wiersz
public:
	int podajKolumne();
	int podajWiersz();
	char podajId();
	virtual ~objNaPlanszy() {};
	friend ostream& operator<<(ostream&, objNaPlanszy&);//przeciazenie operatora wypisania
};

class Jedzenie : public objNaPlanszy
{
public:
	Jedzenie(Plansza&);
	Jedzenie(Plansza&, int, int);
	~Jedzenie() {};
};

class Bron : public objNaPlanszy
{
public:
	Bron(Plansza&);
	Bron(Plansza&, int, int);
	~Bron() {};
};

class Postac: public objNaPlanszy //smok i postacie graczy po tym dziedzicza, klasa abstrakcyjna
{
protected:
	int zdrowie;
public:
	void ruchLewa(Plansza&, bool&);//komenda a
	void ruchGora(Plansza&, bool&);//komenda w
	void ruchDol(Plansza&, bool&);//komenda s
	void ruchPrawa(Plansza&, bool&);//komenda d
	virtual void zbierzObiekt(int, int, char)=0;
	virtual void wypisz() = 0;
	virtual ~Postac() {};
};

class PostacGracza : public Postac //klasa abstrakcyjna
{
protected:
	int atak, bron;
	int pancerz, zdrowieMax, atakMax;
public:
	void ruch(Plansza&, char, bool&);//char to w ktora str, bool czy mozna bylo wykonac ten ruch
	virtual void trenuj(bool&) = 0;
	void trenujPos(bool&, const int);
	void odpocznij(bool&);
	void zbierzObiekt(int, int, char);
	void wypisz();
	void zadajObrazenia();
	virtual void atakqs(Plansza&, bool&, Smok&)=0;
	virtual void atakqa(Plansza&, bool&, Smok&)=0;
	virtual void atakqw(Plansza&, bool&, Smok&)=0;
	virtual void atakqd(Plansza&, bool&, Smok&)=0;
	friend ostream& operator<<(ostream&, PostacGracza&);//przeciazenie operatora wypisania
	friend istream& operator>>(istream&, PostacGracza&);
	virtual ~PostacGracza() {};

};

class Smok : public Postac
{
private:
	bool czyZadalObrazenia;
public:
	Smok(Plansza&);
	Smok(Plansza&, int, int, int);
	~Smok() {};
	void ruch(Plansza&, PostacGracza&);//losowanie jak sie poruszy
	void zbierzObiekt(int, int, char);
	void wypisz();
	void Atakowal(bool);
	bool czyAtakowal();
	void zadajObrazenia(int);
	friend ostream& operator<<(ostream&, Smok&);//przeciazenie operatora wypisania
	friend istream& operator>>(istream&, Smok&);//sprawdzic czy moge usunac
};

class Rycerz : public PostacGracza
{
public:
	Rycerz(Plansza&);
	Rycerz(Plansza&, int, int);
	~Rycerz() {};
	void trenuj(bool&);
	void atakqs(Plansza&, bool&, Smok&);
	void atakqa(Plansza&, bool&, Smok&);
	void atakqw(Plansza&, bool&, Smok&);
	void atakqd(Plansza&, bool&, Smok&);
};

class Lucznik: public PostacGracza
{
public:
	Lucznik(Plansza&);
	Lucznik(Plansza&, int, int);
	~Lucznik() {};
	void trenuj(bool&);
	void atakqs(Plansza&, bool&, Smok&);
	void atakqa(Plansza&, bool&, Smok&);
	void atakqw(Plansza&, bool&, Smok&);
	void atakqd(Plansza&, bool&, Smok&);
};

class Mag : public PostacGracza
{
public:
	Mag(Plansza&);
	Mag(Plansza&, int, int);
	~Mag() {};
	void trenuj(bool&);
	void atakqs(Plansza&, bool&, Smok&);
	void atakqa(Plansza&, bool&, Smok&);
	void atakqw(Plansza&, bool&, Smok&);
	void atakqd(Plansza&, bool&, Smok&);
};

#endif
