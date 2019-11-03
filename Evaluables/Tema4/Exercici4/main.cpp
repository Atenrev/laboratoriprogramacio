#include <iostream>
#include <vector>

using namespace std;


void quicksort(vector<int>& v, int indexInici, int indexFinal);


void mostraArray(vector<int>& v)
{
	cout << "Comment :=>> ";
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}	

bool comparaArray(vector<int>& v1, vector<int>& v2)
{
	bool iguals = true;
	int i = 0;
	while ((i < v1.size()) && iguals)
	{
		if (v1[i] != v2[i])
			iguals = false;
		else
			i++;
	}
	return iguals;
}

int main()
{
	const int MAX_PROVES = 5;
	float grade = 10.0;
	bool iguals;

	cout << "Comment :=>> Iniciant test..." << endl;
	cout << "Comment :=>> -------------------------" << endl;
	vector<int> v;
	v.resize(1);
	v[0] = 10;
	
	vector<int> vOrdenat;
	vOrdenat.resize(1);
	vOrdenat[0] = 10;
	
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, 0);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	

	const int MAX = 100;
	cout << "Comment :=>> -------------------------" << endl;
	v.resize(MAX);
	for (int i = 0; i < MAX; i++)
		v[i] = MAX - 1 - i;
	vOrdenat.resize(MAX);
	for (int i = 0; i < MAX; i++)
		vOrdenat[i] = i;
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, MAX - 1);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	
	cout << "Comment :=>> -------------------------" << endl;
	
	for (int i = 0; i < MAX; i++)
		v[i] = i;
	
	for (int i = 0; i < MAX; i++)
		vOrdenat[i] = i;
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, MAX - 1);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	
	cout << "Comment :=>> -------------------------" << endl;
	
	for (int i = 0; i < (MAX / 2); i++)
		v[i] = (i * 2) + 1;
	for (int i = 0; i < (MAX / 2); i++)
		v[i + (MAX / 2)] = (i * 2);
	
	for (int i = 0; i < MAX; i++)
		vOrdenat[i] = i;
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, MAX - 1);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	
	cout << "Comment :=>> -------------------------" << endl;
	
	for (int j = 0; j < 5; j++)
		for (int i = 0; i < (MAX / 5); i++)
			v[(j * (MAX / 5)) + i] = ((i * 5) + j);
	
	for (int i = 0; i < MAX; i++)
		vOrdenat[i] = i;
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, MAX - 1);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	
	cout << "Comment :=>> -------------------------" << endl;
	
	for (int j = 0; j < 10; j++)
		for (int i = 0; i < (MAX / 10); i++)
			v[(j * (MAX / 10)) + i] = ((i * 10) + j);
	
	for (int i = 0; i < MAX; i++)
		vOrdenat[i] = i;
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, MAX - 1);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	
	cout << "Comment :=>> -------------------------" << endl;
	
	for (int j = 0; j < 20; j++)
		for (int i = 0; i < (MAX / 20); i++)
			v[(j * (MAX / 20)) + i] = ((i * 20) + j);
	
	for (int i = 0; i < MAX; i++)
		vOrdenat[i] = i;
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, MAX - 1);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	
	cout << "Comment :=>> -------------------------" << endl;
	
	for (int j = 0; j < 50; j++)
		for (int i = 0; i < (MAX / 50); i++)
			v[(j * (MAX / 50)) + i] = ((i * 50) + j);
	
	for (int i = 0; i < MAX; i++)
		vOrdenat[i] = i;
	cout << "Comment :=>> Ordenant array amb valors: " << endl;
	mostraArray(v);
	quicksort(v, 0, MAX - 1);
	iguals = comparaArray(v, vOrdenat);
	if (!iguals)
	{
		grade -= 2.0;
		cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
		mostraArray(v);
	}
	else
		cout << "Comment :=>> ORDENACIO OK" << endl;
	
	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
}