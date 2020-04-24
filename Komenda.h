#ifndef KOMENDA_H
#define KOMENDA_H

#include<string>
#include<iostream>
#include"Postac.h"
#include"Plansza.h"
#include"funkcje.h"

class PostacGracza;
class Plansza;
class Smok;

using namespace std;

class Komenda
{
private:
	string tresc;
public:
	Komenda();
	~Komenda() {};
	void wykonaj(PostacGracza&, Plansza&, bool&, Smok&);
	friend istream& operator>>(istream&, Komenda&);//przeciazenie strumienia wejscia
};

#endif
