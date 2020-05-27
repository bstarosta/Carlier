#include "Carlier.h"
#include "PorownaniaRQ.h"

using namespace std;

Carlier::Carlier() : UB(INT_MAX) {}


int Carlier::oblicz_czas_zakonczenia(int nr_zadania)
{
	int m = 0;
	int c = 0;

	for (int i = 0; i < nr_zadania; i++)
	{
		m = max(m, PI[i].R) + PI[i].P;
		c = max(m + PI[i].Q, c);
	}
	return m;
}

int Carlier::schrage()
{
	vector<Zadanie> niegotowe;
	vector<Zadanie> gotowe;

	int t = 0;
	int k = 0;
	int Cmax = 0;
	Zadanie tmp;

	for (int i = 0; i < liczba_zadan; ++i)
		niegotowe.push_back(this->PI[i]);

	make_heap(niegotowe.begin(), niegotowe.end(), PorownajR());
	while (!gotowe.empty() || !niegotowe.empty())
	{
		while (!niegotowe.empty() && niegotowe[0].R <= t)
		{
			gotowe.push_back(niegotowe[0]);
			push_heap(gotowe.begin(), gotowe.end(), PorownajQ());
			pop_heap(niegotowe.begin(), niegotowe.end(), PorownajR());
			niegotowe.pop_back();
		}

		if (gotowe.empty())
			t = niegotowe[0].R;
		else
		{
			tmp = gotowe[0];
			pop_heap(gotowe.begin(), gotowe.end(), PorownajQ());
			gotowe.pop_back();
			t += tmp.P;
			Cmax = max(Cmax, t + tmp.Q);
			this->PI[k] = tmp;
			++k;
		}
	}

	return Cmax;
}


int Carlier::schrage_ptmn()
{
	vector<Zadanie> niegotowe;
	vector<Zadanie> gotowe;

	Zadanie tmp;
	int m = 0;
	int Cmax = 0;
	int t = 0;
	int p_tmp = 0;
	int t_next = 0;

	for (int i = 0; i < liczba_zadan; ++i)
		niegotowe.push_back(this->PI[i]);
	

	std::make_heap(niegotowe.begin(), niegotowe.end(), PorownajR());
	while (!gotowe.empty() || !niegotowe.empty())
	{
		while (!niegotowe.empty() && niegotowe[0].R <= t)
		{
			gotowe.push_back(niegotowe[0]);
			push_heap(gotowe.begin(), gotowe.end(), PorownajQ());
			pop_heap(niegotowe.begin(), niegotowe.end(), PorownajR());
			niegotowe.pop_back();
		}

		t_next = niegotowe.empty() ? INT_MAX : niegotowe[0].R;

		if (gotowe.empty())
			t = t_next;
		else
		{
			tmp = gotowe[0];
			p_tmp = gotowe[0].P;

			if (t_next < t + p_tmp)
			{
				tmp.P = p_tmp - (t_next - t);
				pop_heap(gotowe.begin(), gotowe.end(), PorownajQ());
				gotowe.pop_back();
				gotowe.push_back(tmp);
				push_heap(gotowe.begin(), gotowe.end(), PorownajQ());
				t = t_next;
			}
			else
			{
				pop_heap(gotowe.begin(), gotowe.end(), PorownajQ());
				gotowe.pop_back();
				m = max(m, t) + tmp.P;
				Cmax = max(m + tmp.Q, Cmax);
				t += p_tmp;
			}
		}
	}

	return Cmax;
}

void Carlier::znajdz_b(int Cmax)
{
	for (int i = liczba_zadan; i > 0; --i)
	{
		if (oblicz_czas_zakonczenia(i) + PI[i - 1].Q == Cmax)
		{
			b = i - 1;
			break;
		}
	}
}

void Carlier::znajdz_a(int Cmax)
{
	for (int i = 0; i < liczba_zadan; ++i)
	{
		int suma_czasow = 0;

		for (int j = i; j <= b; ++j)
			suma_czasow += PI[j].P;

		if (PI[i].R + suma_czasow + PI[b].Q == Cmax)
		{
			a = i;
			break;
		}
	}
}

void Carlier::znajdz_c()
{
	for (int i = b; i >= a; --i)
	{
		if (PI[i].Q < PI[b].Q)
		{
			c = i;
			break;
		}
	}
}

int Carlier::carlier()
{
	int U = this->schrage();
	int wynik_carliera;

	r_k = INT_MAX;
	q_k = INT_MAX;
	p_k = 0;
	c = -1;

	if (U < UB)
	{
		UB = U;
		for (int i = 0; i < liczba_zadan; i++)
			optymalnePI[i] = PI[i];
	}

	znajdz_b(U);
	znajdz_a(U);
	znajdz_c();

	if (c == -1)
		return UB;

	for (int j = c + 1; j <= b; ++j)
	{
		if (PI[j].R < r_k)
			r_k = PI[j].R;

		if (PI[j].Q < q_k)
			q_k = PI[j].Q;

		p_k += PI[j].P;
	}


	int nr_c = PI[c].nr;
	int r_c = PI[c].R;
	int q_c;

	PI[c].R = max(PI[c].R, r_k + p_k);

	LB = schrage_ptmn();
	if (LB < UB)
	{
		wynik_carliera = carlier();

		if (wynik_carliera < UB)
			UB = wynik_carliera;

	}

	for (int i = 0; i < liczba_zadan; i++)
	{
		if (nr_c == PI[i].nr)
		{
			PI[i].R = r_c;
			q_c = PI[i].Q;
			PI[i].Q = max(PI[i].Q, q_k + p_k);
		}
	}

	LB = schrage_ptmn();
	if (LB < UB)
	{
		wynik_carliera = carlier();

		if (wynik_carliera < UB)
			UB = wynik_carliera;
	}

	for (int i = 0; i < liczba_zadan; i++)
		if (nr_c == PI[i].nr)
			PI[i].Q = q_c;

	return UB;
}