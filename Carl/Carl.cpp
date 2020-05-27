#pragma comment(linker, "/STACK:512000000")
#pragma comment(linker, "/HEAP:128000000")
#include <iostream>
#include <fstream>
#include <iostream>
#include <stdlib.h> 
#include <string>
#include "Carlier.h"


using namespace std;


int main()
{
	int cmax;

	for (int z = 0; z < 9; z++)
	{
		ifstream dane("carl.data.txt");
		string nazwa = "data." + to_string(z) + ":";
		string buff = "";
		Carlier carl;

		while (buff != nazwa)
			dane >> buff;

		dane >> carl.liczba_zadan;

		for (int i = 0; i < carl.liczba_zadan; i++)
		{
			carl.PI[i].nr = i;
			dane >> carl.PI[i].R >> carl.PI[i].P >> carl.PI[i].Q;
		}

		cmax = carl.carlier();

		cout << "Permutacja data" << z << ": " << endl;
		for (int j = 0; j < carl.liczba_zadan; j++)
			cout << carl.optymalnePI[j].nr << " ";
		cout << endl;
		cout << "Cmax data" << z << ": "<< cmax << endl;
	}
}
