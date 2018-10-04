#pragma once
class Kabel
{
public:


	int identyfikator;
	int poj;
	int koszt;
	bool operator<(const Kabel &hal) {
		if (float(poj) / float(koszt) > float(hal.poj) / float(hal.koszt)) {
			return true;

		}
		else {
			return false;
		}



	}
	Kabel(int id, int p, int k) {
		identyfikator = id;
		poj = p;
		koszt = k;



	}
	~Kabel();
};

