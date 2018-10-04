#pragma once
#include <vector>
#include "Krawedz.h"
#include "Kabel.h"
#include "Sciezka.h"
#include<iostream>

using namespace std;
class Siec
{
public:
	vector <Kabel> kabel;
	vector <Krawedz> edge;
	vector <Wierzcholek> vert;
	vector <int>granice;
	void dodajKrawedz(int, Wierzcholek, Wierzcholek,int);
	void dodajKabel(int, int,int);
	void dodajWierzcholek(int, int, int, int);
	
	void sortuj(){
		sort(kabel.begin(),kabel.end());

	};
	void zakop() {
		for (int j = 0; j < edge.size(); j++) {

			int wlokna = edge[j].wlokna;
			int koszt = 0;
			int i = 0;
			vector<int>ile = granice;
			for (int j = 0; j < ile.size(); j++) {
				ile[j] = 0;
			}


			while (wlokna>0) {
				if (wlokna >= granice[i]) {
					wlokna = wlokna - kabel[i].poj;
					koszt = koszt + kabel[i].koszt;
					ile[i]++;
					edge[j].kable.push_back(kabel[i]);


				}
				else {
					if (i <= kabel.size() - 1)
						i++;


				}



			}
			int a = 1;

			edge[j].koszt = koszt*edge[j].waga / 10;
			if (edge[j].koszt > 0) {
				edge[j].koszt = edge[j].koszt + edge[j].cena;
			}

			if (edge[j].wlokna > 0) {
				cout << "Krawedz " << edge[j].identyfikator << " ma zakopane:" << endl;
				for (int t = 0; t < ile.size(); t++) {
					if (ile[t] > 0) {
						cout << "        ";
						cout << ile[t] << " sztuk kabla o identfikatorze " << kabel[t].identyfikator << endl;






					}
					

				}
				cout << "        ";
				cout << "Kosztuje to " << edge[j].koszt << endl;

			}


		}
		int lacznykoszt = 0;
		for (int y = 0; y < edge.size(); y++) {

			lacznykoszt = lacznykoszt + edge[y].koszt;



		}

		cout << "Calkowity koszt budowy sieci to " << lacznykoszt;


	}
	void kabluj() {
		int koszt = 0;
		int zost = 0;
		int poj = 0;
		int n = 0;
		for (int i = 0; i < kabel.size()-1; i++) {
			poj = 0;
			zost = 0;
			koszt = 0;
			n = 0;
			Kabel c = kabel[i + 1];
			zost = kabel[i].koszt;
			while (1) {

				if (c.koszt <= zost) {
					zost = zost - c.koszt;
					koszt = koszt + c.koszt;
					poj = poj + c.poj;

				}
				else {

					if (i + n == kabel.size()-1) {
						break;
					}else{
						n = n + 1;
						c = kabel[i + n];
					}

				}




			}

			if (koszt < kabel[i].koszt) {
				granice.push_back(poj+1);
			}else {
				granice.push_back(poj);
			}




		}


		granice.push_back(1);

	}
	void Buduj();
	int porownaj(vector<int> koszt, int li)
	{
		int indeks = 0;
		/*int indextmp = 0;
		for (int i = 0; i < koszt.size()-1; i++)
		{
		for (int j = 1; j < koszt.size(); j++)
		if (koszt[i] < koszt[j] && koszt[i] >= aktualnyNajmniejszyKoszt)
		{
		indeks = i;
		indextmp = indeks;

		}
		else
		indeks = j;

		return indeks;*/
		vector<int> tmp;
		tmp = koszt;
		sort(tmp.begin(), tmp.end());
		for (int i = 0; i < koszt.size(); i++)
		{
			if (koszt[i] == tmp[0 + li])
				return i;
		}
	}
	int porownaj2(vector<int> koszt, int li)
	{
		int indeks = 0;
		/*int indextmp = 0;
		for (int i = 0; i < koszt.size()-1; i++)
		{
		for (int j = 1; j < koszt.size(); j++)
		if (koszt[i] < koszt[j] && koszt[i] >= aktualnyNajmniejszyKoszt)
		{
		indeks = i;
		indextmp = indeks;

		}
		else
		indeks = j;

		return indeks;*/
		vector<int> tmp;
		tmp = koszt;
		sort(tmp.rbegin(), tmp.rend());
		for (int i = 0; i < koszt.size(); i++)
		{
			if (koszt[i] == tmp[0 + li])
				return i;
		}
	}
	Sciezka algorytmsciezka(Siec &s, int poczatek, int koniec) {

		Siec *s1 = &s;

		//fscanf_s(p, "%d %d\n", &a, &b);
		vector<Wierzcholek> S;
		vector<Wierzcholek> Q;
		vector<int> koszt;
		vector<int> poprzednik;


		bool skierowany = false; //ogarnac jak ustawic w pliku !!!!!!!!!!!!!!!!!!




								 //int aktualnyNajmniejszyKoszt = 0;
		for (int i = 0; i < s.vert.size(); i++)
		{
			if (s.vert[i].identyfikator == poczatek)
			{
				S.push_back(s.vert[i]);
				koszt.push_back(0);
				poprzednik.push_back(-1);
			}
			else
			{
				koszt.push_back(1000000);
				Q.push_back(s.vert[i]);
				poprzednik.push_back(-1);
			}
		}
		int j = 0;
		if (skierowany)
		{
			for (int h = 0; h < Q.size(); h++)
			{

				for (int i = 0; i < s.edge.size(); i++)
				{

					if (s.edge[i].pocz.identyfikator == porownaj(koszt, j) + 1)
					{
						if (koszt[s.edge[i].pocz.identyfikator - 1 /*+ s.edge[i].konc.identyfikator - 1*/] + s.edge[i].waga < koszt[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].konc.identyfikator - 1])
						{

							koszt[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].konc.identyfikator - 1] = koszt[s.edge[i].pocz.identyfikator - 1 /*+ s.edge[i].konc.identyfikator - 1*/] + s.edge[i].waga;
							poprzednik[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].konc.identyfikator - 1] = s.edge[i].pocz.identyfikator - 1;
						}
						else
						{
							continue;
						}
					}

				}


				//S.push_back(/*Q[ porownaj(koszt,j)*/Wierzcholek(1,1,1) );

				j++;
			}
		}
		if (!skierowany)
		{
			for (int h = 0; h < Q.size(); h++)
			{

				for (int i = 0; i < s.edge.size(); i++)
				{

					if (s.edge[i].pocz.identyfikator == porownaj(koszt, j) + 1 || s.edge[i].konc.identyfikator == porownaj(koszt, j) + 1)
					{
						if (s.edge[i].pocz.identyfikator == porownaj(koszt, j) + 1)
						{
							if (koszt[s.edge[i].pocz.identyfikator - 1 /*+ s.edge[i].konc.identyfikator - 1*/] + s.edge[i].waga < koszt[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].konc.identyfikator - 1])
							{

								koszt[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].konc.identyfikator - 1] = koszt[s.edge[i].pocz.identyfikator - 1 /*+ s.edge[i].konc.identyfikator - 1*/] + s.edge[i].waga;
								poprzednik[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].konc.identyfikator - 1] = s.edge[i].pocz.identyfikator - 1;
							}
						}
						if (s.edge[i].konc.identyfikator == porownaj(koszt, j) + 1)
						{
							if (koszt[s.edge[i].konc.identyfikator - 1 /*+ s.edge[i].konc.identyfikator - 1*/] + s.edge[i].waga < koszt[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].pocz.identyfikator - 1])
							{

								koszt[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].pocz.identyfikator - 1] = koszt[s.edge[i].konc.identyfikator - 1 /*+ s.edge[i].konc.identyfikator - 1*/] + s.edge[i].waga;
								poprzednik[/*s.edge[i].pocz.identyfikator - 1 +*/ s.edge[i].pocz.identyfikator - 1] = s.edge[i].konc.identyfikator - 1;
							}
						}


					}
				}


				//S.push_back(/*Q[ porownaj(koszt,j)*/Wierzcholek(1,1,1) );

				j++;
			}

		}

		Sciezka k;
		int indeks = koniec - 1;
		for (int i = 0; i < Q.size() + 1; i++)
		{
			if (i == indeks)
			{

				if (skierowany)
				{
					while (poprzednik[indeks] != -1)
					{
						for (int j = 0; j < s.edge.size(); j++)
						{
							if (s.edge[j].konc.identyfikator - 1 == indeks && s.edge[j].pocz.identyfikator - 1 == poprzednik[indeks])
								k.sverts.push_back(j);
						}
						indeks = poprzednik[indeks];
					}
					break;
				}
				if (!skierowany)
				{
					while (poprzednik[indeks] != -1)
					{
						for (int j = 0; j < s.edge.size(); j++)
						{
							if (s.edge[j].konc.identyfikator - 1 == indeks && s.edge[j].pocz.identyfikator - 1 == poprzednik[indeks]) {
								k.sverts.push_back(j + 1);
								s.edge[j].wlokna += s.vert[poczatek-1].klienci;
							}
							else if (s.edge[j].pocz.identyfikator - 1 == indeks && s.edge[j].konc.identyfikator - 1 == poprzednik[indeks]) {
								k.sverts.push_back(j + 1);
								s.edge[j].wlokna += s.vert[poczatek-1].klienci;
							}
						}
						indeks = poprzednik[indeks];
					}
					
					break;
				}
			}

		}

	/*	vector<Krawedz>qa;
		for (int j = 0; j < k.sverts.size(); j++) {
			Wierzcholek pocz = s.edge[k.sverts[j]].pocz;
			Wierzcholek konc = s.edge[k.sverts[j]].konc;
			Krawedz kr = Krawedz(pocz, konc, 0, 0);
			qa.push_back(kr);
			qa[j].line[0] = sf::Vertex(sf::Vector2f(qa[j].pocz.x, qa[j].pocz.y), Color::Red);
			qa[j].line[1] = sf::Vertex(sf::Vector2f(qa[j].konc.x, qa[j].konc.y), Color::Red);


		}

		string nazwa = "Dijkstra";
		sf::RenderWindow w(sf::VideoMode(1366, 768, 32), nazwa);
		Font f;

		f.loadFromFile("sansation.ttf");
		while (w.isOpen())
		{

			sf::Event event;
			while (w.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
					w.close();
			}
			w.clear(Color::White);


			for (int i = 0; i < s1->edge.size(); i++)
			{
				w.draw(s1->edge[i].pocz.c1);
				w.draw(s1->edge[i].konc.c1);
				w.draw(s1->edge[i].line, 2, sf::Lines);
			}
			for (int j = 0; j < qa.size(); j++)
			{

				w.draw(qa[j].line, 2, sf::Lines);
			}
			for (int j = 0; j < s1->vert.size(); j++)
			{

				//s1.vert[j].txt.setFont(s1.vert[j].font.getDefault());
				s1->vert[j].txt.setFont(f);
				w.draw(s1->vert[j].txt);

			}





			w.display();

		}*/
		return k;
	}

	void polozKable();
	
	/*vector <int> ustalKrawedzie(Siec &s, Sciezka d)
	{
		vector<int> krawedzieSciezki;

		for (int i = 0; i < d.sverts.size() - 1; i++) {
			for (int j = 0; j < s.edge.size(); j++)
			{
				if ((s.edge[j].konc.identyfikator - 1 == d.sverts[i] && s.edge[j].pocz.identyfikator - 1 == d.sverts[i + 1]) || (s.edge[j].pocz.identyfikator - 1 == d.sverts[i + 1] && s.edge[j].konc.identyfikator - 1 == d.sverts[i]))
				{
					krawedzieSciezki.push_back(j);
				}
			}

		}
		return krawedzieSciezki;
	}*/


	Siec();
	~Siec();
};

