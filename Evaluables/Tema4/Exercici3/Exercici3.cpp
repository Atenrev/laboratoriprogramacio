#include <list>
using namespace std;

int MaxElsRec(list<int>& l, list<int>::iterator it)
{
	int v = 0;
	list<int>::iterator next = it;
	next++;

	if (next != l.end())
		v = MaxElsRec(l, next);

	if (v > * it)
		return v;
	else
		return *it;
}

int MaxElementsLlista(list<int> &l)
{
	if (l.size() > 0)
		return MaxElsRec(l, l.begin());
	else
		return 0;
}