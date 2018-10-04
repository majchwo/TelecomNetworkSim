#pragma once
#include "stdafx.h"
#include "Wierzcholek.h"
#include "Kabel.h"
class Krawedz
{
public:
	int waga;
	Wierzcholek pocz;
	Wierzcholek konc;
	int koszt;
	int identyfikator;
	int cena;
	Vertex line[2];
	int wlokna;
	Font fontk;
	sf::Text txt;
	vector<Kabel>kable;
	Krawedz( Wierzcholek, Wierzcholek,int,int);
	~Krawedz();
};

