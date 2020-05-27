#pragma once

struct PorownajR {
	bool operator()(Zadanie const& zadanie1, Zadanie const& zadanie2)
	{
		if (zadanie1.R < zadanie2.R)
			return false;
		if (zadanie1.R > zadanie2.R)
			return true;
		if (zadanie1.R == zadanie2.R)
			return zadanie1.nr > zadanie2.nr;
	}
};

struct PorownajQ {
	bool operator()(Zadanie const& zadanie1, Zadanie const& zadanie2)
	{
		if (zadanie1.Q < zadanie2.Q)
			return true;
		if (zadanie1.Q > zadanie2.Q)
			return false;
		if (zadanie1.Q == zadanie2.Q)
			return zadanie1.nr > zadanie2.nr;
	}
};