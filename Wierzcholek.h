#pragma once

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace sf;
using namespace std;
class Wierzcholek
{
public:
	int identyfikator;
	int x;
	int y;
	int klienci;
	
	CircleShape c1;
	Font font;
	sf::Text txt;
	Wierzcholek();
	
	Wierzcholek(int, int, int, int);
	~Wierzcholek();
};

