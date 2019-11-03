#include <iostream>
#include <vector>
using namespace std;


void ordenaArray(vector<int>& v, int indexInici, int indexFinal);

void mostraArray(vector<int>& v, int longitud)
{
	cout << "Comment :=>> ";
	for (int i = 0; i < longitud; i++)
		cout << v[i] << " ";
	cout << endl;
}	

bool comparaArray(vector<int>& v1, vector<int>& v2, int longitud)
{
	bool iguals = true;
	int i = 0;
	while ((i < longitud) && iguals)
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
	const int TEST = 5;
	vector<int> numValors;
	vector<int> numInit;
	numValors.resize(TEST);
	numInit.resize(TEST);

	numValors = { 1,20,0,4,10 };
	numInit = { 0,0,0,0,2 };

	vector<vector<int>> v;
	vector<vector<int>> v_ordenat;

	v.resize(TEST);
	v_ordenat.resize(TEST);

	v_ordenat = { {10},{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},{},{5,8,9,13},{ 5,9,2,4,6,9,10,12,14,20 } };
	v = { { 10 },{ 5,11,13,10,19,6,18,3,2,1,15,14,9,8,20,4,7,16,17,12 },{},{ 13,8,5,9 },{5,9,2,6,9,12,14,10,20,4} };
	
	for (int i = 0; i < TEST; i++)
	{
		cout << "Comment :=>> Ordenant array amb valors: " << endl;
		mostraArray(v[i], numValors[i]);
		ordenaArray(v[i], numInit[i], numValors[i]-1);
		iguals = comparaArray(v[i], v_ordenat[i], numValors[i]);
		if (!iguals)
		{
			grade -= 2.0;
			cout << "Comment :=>> ERROR. L'array ordenat que s'ha obtingut es:" << endl;
			mostraArray(v[i], numValors[i]);
		}
		else
		{
			cout << "Comment :=>> ORDENACIO OK. L'array ordenat que s'ha obtingut es:" << endl;
			mostraArray(v[i], numValors[i]);
		}
	}
		
	if (grade < 0)
		grade = 0.0;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
}