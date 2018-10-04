#pragma once
#pragma once
#include <fstream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Siec.h"
//#include <stdio.h>
#include "siec.h"
void addvert(Wierzcholek w, vector <Wierzcholek>&tverts) {
	tverts.push_back(w);

}

void updateava(vector <Wierzcholek>&tverts, vector <Krawedz>&avaedge, vector <Krawedz>&edge) {
	
	avaedge.clear();

	for (int i = 0; i<tverts.size(); i++) {
		Wierzcholek w = tverts[i ];

		for (int j = 0; j<edge.size();j++) {
			Krawedz k =edge[j];
			if (w.identyfikator ==k.pocz.identyfikator || w.identyfikator ==k.konc.identyfikator) {

				int bylo=0;

				for (int c=0; c<avaedge.size(); c++) {
					if (k.identyfikator == avaedge[c ].identyfikator) {
						bylo = 1;
					}

				}

				if (bylo == 0) {
					avaedge.push_back(k);

				}




			}




		}







	}
	

}
bool porownaj1(Krawedz a, Krawedz b) {
	if (a.waga < b.waga) {
		return true;

	}
	else {
		return false;
	}


}
void sortava(vector <Krawedz>&avaedge) {

	sort(avaedge.begin(), avaedge.end(), porownaj1);


}
void addtedge(vector <Krawedz>&avaedge, vector <Krawedz>&edge) {
	for (int c = 0; c<avaedge.size(); c++) {
		
		Krawedz e=avaedge[c];
     




	}



}

void updatedone(vector <Wierzcholek>&doneverts, vector <Krawedz>&tedge, vector <Wierzcholek> tverts) {
	doneverts.clear();


	for (int c = 0; c<tverts.size(); c++) {
		Wierzcholek w= tverts[c];
		int bylo = 0;

		for (int d = 0; d<tedge.size(); d++) {
			Krawedz k = tedge[d];

			if (k.pocz.identyfikator==w.identyfikator || k.konc.identyfikator == w.identyfikator) {
				bylo = 1;

			}

		}


		if (bylo == 1) {
			doneverts.push_back(w);


		}






	}


}
bool isinside(Wierzcholek w, vector <Wierzcholek>&doneverts) {
	bool bylo = false;
	for (int d = 0; d < doneverts.size(); d++) {
		Wierzcholek z = doneverts[d];


		if (w.identyfikator == z.identyfikator) {


			bylo = true;

			break;
		}
	}


		return bylo;


}

void drukmst(Siec &s, vector <Krawedz> wynik) {
	using namespace sf;
	Font f;
	f.loadFromFile("sansation.ttf");



	sf::RenderWindow w(sf::VideoMode(1366, 768, 32), "Minimalne drzewo rozpinajace Steinera");

	Siec *s1 = &s;


	
	

	for (int j = 0; j < s1->vert.size(); j++)
	{
		//s1->vert[j].font.loadFromFile("sansation.ttf");
		//s1.vert[j].txt.setFont(s1.vert[j].font.getDefault());
		s1->vert[j].txt.setFont(f);
		//w.draw(s1->vert[j].txt);

	}

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
		for (int j = 0; j < s1->vert.size(); j++)
		{
			s1->vert[j].font.loadFromFile("sansation.ttf");
			//s1.vert[j].txt.setFont(s1.vert[j].font.getDefault());
			//s1->vert[j].txt.setFont(f);
			w.draw(s1->vert[j].txt);

		}
		for (int j = 0; j < wynik.size(); j++)
		{

			w.draw(wynik[j].line, 2, sf::Lines);
		}




		w.display();

	}


}
void algorytmmst(FILE* p, Siec &s) {

	//vector <Wierzcholek> tverts;
	vector <Krawedz> tedge;



	vector <Wierzcholek> doneverts;
	vector <Krawedz> avaedge;
	addvert(s.vert[0], doneverts);

	while (s.vert.size() != doneverts.size()){
		updateava(doneverts, avaedge, s.edge);
		sortava(avaedge);

		for (int d = 0; d < avaedge.size(); d++) {
			Krawedz k = avaedge[d];

			if (!isinside(k.pocz,doneverts) || !isinside(k.konc,doneverts)) {

				tedge.push_back(k);


				break;
			}

		}

		updatedone(doneverts, tedge, s.vert);

	}


	for (int z = 0; z < tedge.size(); z++) {
		tedge[z].line[0] = sf::Vertex(sf::Vector2f(tedge[z].pocz.x, tedge[z].pocz.y), Color::Red);
		tedge[z].line[1] = sf::Vertex(sf::Vector2f(tedge[z].konc.x, tedge[z].konc.y), Color::Red);

	}



	drukmst(s, tedge);
	
	




}