#pragma once

#include <limits>
#include "Zadanie.h"
#include <vector>
#include <algorithm>
#include <iostream>

class Carlier
{
	int UB;
	int LB;
	int a;
	int b;
	int c;
	int r_k;
	int p_k;
	int q_k;

	int schrage();
	int schrage_ptmn();
	int oblicz_czas_zakonczenia(int nr_zadania);
	void znajdz_b(int Cmax);
	void znajdz_a(int Cmax);
	void znajdz_c();

public:

	Carlier();
	Zadanie optymalnePI[50];
	Zadanie PI[50];
	int liczba_zadan;

	int carlier();


};
