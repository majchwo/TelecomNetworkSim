#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Siec.h"
#include "Sciezka.h"
#include "Odczyt.h"
void ignoruj(FILE* p);
class para {
public:
	int a = 0;
	int b = 0;
	vector <int>way;
	int cena;
	para(int c, int d) {
		a = c;
		b = d;

	};
	~para() {
	};




};


void rekurway(int pocz, int konc, vector<int>&way, int **nast) {
	int c = nast[pocz - 1][konc - 1];
	if (c == konc) {
		int t = 9;
		//way.push_back(pocz);
	}
	else {
		int i = c;
		rekurway(pocz, i, way, nast);
		way.push_back(i);
		rekurway(i, konc, way, nast);

	}
	//way.push_back(konc);

}

void drukuj(vector <para>&pary, Siec &s) {
	using namespace std;
	using namespace sf;

	

	Siec *s1 = &s;
	Font f;
	f.loadFromFile("sansation.ttf");
	for (int j = 0; j < s1->vert.size(); j++)
	{
		//s1->vert[j].font.loadFromFile("sansation.ttf");
		//s1.vert[j].txt.setFont(s1.vert[j].font.getDefault());
		s1->vert[j].txt.setFont(f);
		//w.draw(s1->vert[j].txt);

	}
	for (int i = 0; i < pary.size();i++) {
		para p = pary[i];
		Sciezka sc;
		sc.sverts = p.way;
		vector<Krawedz>k;
		for (int j = 0; j < sc.sverts.size()-1;j++) {
			Wierzcholek pocz=s.vert[sc.sverts[j]-1];
			Wierzcholek konc=s.vert[sc.sverts[j+1]-1];
			Krawedz kr = Krawedz( pocz, konc,0,0);
			k.push_back(kr);
			k[j].line[0] = sf::Vertex(sf::Vector2f(k[j].pocz.x, k[j].pocz.y), Color::Red);
			k[j].line[1] = sf::Vertex(sf::Vector2f(k[j].konc.x, k[j].konc.y), Color::Red);
			

		}


		//string az = "do ";
		string nazwa="Sciezka od " + std::to_string(p.a) + " do " + std::to_string(p.b);
		sf::RenderWindow w(sf::VideoMode(1366, 768, 32), nazwa);
		

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
			for (int j = 0; j < k.size(); j++)
			{

				w.draw(k[j].line, 2, sf::Lines);
			}
			for (int j = 0; j < s1->vert.size(); j++)
			{
				s1->vert[j].font.loadFromFile("sansation.ttf");
				//s1.vert[j].txt.setFont(s1.vert[j].font.getDefault());
				//s1->vert[j].txt.setFont(f);
				w.draw(s1->vert[j].txt);

			}
			




			w.display();

		}









	}


}

/*for (int j = 0; j < k.size(); j++)
{

w.draw(k[j].line, 2, sf::Lines);
}*/
void algorytmfloyd(FILE* p,Siec &s) {
	int maxint = 2147483647;
	int lpar = 0;
	bool CZYSKIEROWANE = 1;
	vector <para> pary;
	vector <Krawedz> fedge = s.edge;
	int e, f = 0;
	while (!feof(p)) {
		fscanf_s(p, "%d %d\n", &e, &f);
		pary.push_back(para(e, f));
		lpar++;
		if (!feof(p)) {
			ignoruj(p);
		}
	}
	
	int n = s.vert.size();

	//macierz wag
	int **wagi=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		wagi[i] = new int[n]; //alokacja pamieci
		for (int j = 0; j < n; ++j) { //wpisanie wartosci do tablicy
			wagi[i][j] = maxint;
			if (j == i) {
				wagi[i][j] = 0;
			}
		}
	}

	//macierz nastepnikow
	int **nast = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		nast[i] = new int[n]; //alokacja pamieci
		for (int j = 0; j < n; ++j) //wpisanie wartosci do tablicy
			nast[i][j] = j+1;
	}
	

	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << nast[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	*/

	int y = 2;


	for (int a = 0; a < fedge.size(); a++) {
		Krawedz z = fedge[a];
		wagi[z.pocz.identyfikator - 1][z.konc.identyfikator - 1] = z.waga;
		if (!CZYSKIEROWANE) {
			wagi[z.konc.identyfikator - 1][z.pocz.identyfikator - 1] = z.waga;
		}


	}




	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (wagi[i - 1][k - 1]!=maxint && wagi[k - 1][j - 1]!=maxint) {

					if (wagi[i - 1][j - 1] > (wagi[i - 1][k - 1] + wagi[k - 1][j - 1])) {
						wagi[i - 1][j - 1] = wagi[i - 1][k - 1] + wagi[k - 1][j - 1];
						nast[i - 1][j - 1] = k;
					}
				}

			}

		}

	}



	//vector <int>way;
	
	//rekurway(3, 1, way, nast);
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout<<wagi[i][j]<<' ';
		}
		cout << endl;
	}*/
	int x = 9;

	for (int t = 0; t < pary.size(); t++) {
		pary[t].way.push_back(pary[t].a);
		rekurway(pary[t].a, pary[t].b, pary[t].way, nast);
		pary[t].way.push_back(pary[t].b);
	}







	// czysc wagi
	for (int i = 0; i < n; ++i)
	{
		delete wagi[i];
		
	}
	delete[] wagi; //alokacja pamieci


				   // czysc nastepniki
	for (int i = 0; i < n; ++i)
	{
		delete nast[i];

	}
	delete[] nast;


	drukuj(pary, s);
	int a = 2;



}
