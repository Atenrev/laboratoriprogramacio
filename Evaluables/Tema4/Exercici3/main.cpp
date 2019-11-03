#include <list>
#include <vector>
#include <iostream>
using namespace std;

int MaxElementsLlista(list<int> &l);


void mostraLlista(list<int>& l)
{
	cout << "Comment :=>> ";
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		cout << (*it) << " ";
	cout << endl;
}

int main()
{
	const int MAX_PROVES = 8;
	float grade = 10.0;

	vector<list<int>> lValors = { {},
	{ 4 },
	{ 1, 2, 3, 4, 5 },
	{ 5, 4, 3, 2, 1 },
	{ 1, 3, 5, 2, 4 },
	{ 3, 1, 4, 2, 5 },
	{ 5, 1, 3, 4, 2 },
	{ 3, 5, 4, 2, 1 } };
	
	int nValorsLlista[MAX_PROVES] = { 0, 1, 5, 5, 5, 5, 5, 5 };
	int maxim[MAX_PROVES] = { 0, 4, 5, 5, 5, 5, 5, 5 };

	cout << "Comment :=>> Iniciant test..." << endl;
	for (int i = 0; i < MAX_PROVES; i++)
	{
		list<int> l;
		l = lValors[i];
		cout << "Comment :=>> -------------------------" << endl;
		cout << "Comment :=>> Buscant maxim en llista amb valors: " << endl;
		mostraLlista(l);
		int max = MaxElementsLlista(l);
		if (max != maxim[i])
		{
			grade -= 2.0;
			cout << "Comment :=>> ERROR. S'esperava " << maxim[i] << " i s'ha obtingut " << max << endl;
		}
		else
			cout << "Comment :=>> OK" << endl;		
	}

	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
}