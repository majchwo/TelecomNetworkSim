#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include "Siec.h"
#include "algfloyd.h"
#include "algmst.h"
#include "algsciezka.h"
#include "steiner.h"
void ignoruj(FILE* p) {
	unsigned char c;



	c = fgetc(p);
	if (c == 35) {
		do {
			while (c != 10) {
				c = fgetc(p);
			}


			c = fgetc(p);
		} while (c == 35);
	}


	fseek(p, -1, 1);


}

void wczytuj2(Siec *s) {

	FILE* p; //uchwyt do pliku

	fopen_s(&p, "networkB.txt", "r"); //otwieramy plik w trybie tylko do odczytu - parametr "r"
									  //if (p == NULL)
									  //	exit(0);

	unsigned char c;


	int w;
	ignoruj(p);
	fscanf_s(p, "WEZLY = %d\n", &w);

	ignoruj(p);
	int id1 = 0;
	int x1, a1 = 0;
	int y1, b1,c1 = 0;
	int kli;
	float pojemnosck = 0;
	float kosztk = 0;
	for (int i = 1; i<w + 1; i++) {
		fscanf_s(p, "%d %d %d %d\n", &id1, &x1, &y1, &kli);
		s->dodajWierzcholek(id1, x1 * 10, y1 * 10, kli);
		ignoruj(p);


	}
	int l;
	fscanf_s(p, "KRAWEDZIE = %d\n", &l);

	ignoruj(p);
	for (int j = 1; j<l + 1; j++) {
		fscanf_s(p, "%d %d %d %d\n", &id1, &a1, &b1, &c1);
		s->dodajKrawedz(id1, s->vert[a1 - 1], s->vert[b1 - 1],c1);
		ignoruj(p);


	}

	fscanf_s(p, "KABLE = %d\n", &l);

	ignoruj(p);
	for (int j = 1; j<l + 1; j++) {
		fscanf_s(p, "%d %f %f\n", &id1, &pojemnosck, &kosztk);
		s->dodajKabel(id1, pojemnosck, kosztk);
		ignoruj(p);


	}
	



	fclose(p);

}

