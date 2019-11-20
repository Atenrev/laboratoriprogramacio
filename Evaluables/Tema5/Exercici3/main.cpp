#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include "graf.h"

using namespace std;

void mostraBool(bool logic)
{
	if (logic)
		cout << "TRUE";
	else
		cout << "FALSE";
}

void mostraNodes(std::vector<string> &nodes)
{
	cout << "[";
	if (nodes.size() > 0)
	{
		for (int i = 0; i < nodes.size() - 1; i++)
		{
			cout << nodes[i] << ",";
		}
		cout << nodes[nodes.size() - 1];
	}
	cout << "]";
}

float testCicles()
{
	float reduccio = 0.0;

	int numNodes;

	vector<string> nodes;
	vector<vector<int>> arestes;
	vector<int> pesos;
	const int N_PROVES = 3;
	bool resultat[N_PROVES] = { false, true, true };

	numNodes = 11;
	nodes.resize(numNodes);
	nodes = { "Tasca 1","Tasca 2","Tasca 3","Tasca 4","Tasca 5","Tasca 6","Tasca 7","Tasca 8","Tasca 9","Tasca 10","Tasca 11" };

	arestes = { { 0,1 },{ 0,2 },{ 0,3 },{ 2,1 },{ 2,3 },{ 1,4 },{ 1,5 },{ 3,5 },{ 3,6 },{ 5,4 },{ 5,6 },{ 4,7 },{ 4,8 },{ 6,8 },{ 6,9 },{ 7,8 },
	{ 8,9 },{ 7,10 },{ 8,10 },{ 9,10 } };

	pesos = { 5,5,5,7,7,10,10,4,4,6,6,3,3,9,9,2,8,2,8,4 };

	int nProva = 0; 
	cout << endl;
	cout << "Comment :=>> Iniciant test de cerca de cicles en un graf dirigit" << endl;
	cout << "Comment :=>> (TEST NO AVALUABLE)" << endl;
	cout << "Comment :=>> ===================================================" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> TEST " << nProva + 1 << endl;
	cout << "Comment :=>> ------------" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> Inicialitzant el graf ......." << endl;
	cout << "Comment :=>> Nodes: [";
	for (int i = 0; i < (numNodes - 1); i++)
		cout << nodes[i] << ", ";
	cout << nodes[numNodes - 1] << "]" << endl;
	cout << "Comment :=>> Arestes: [";
	for (int i = 0; i < arestes.size() - 1; i++)
		cout << "(" << arestes[i][0] << ", " << arestes[i][1] << "),";
	cout << "(" << arestes[arestes.size() - 1][0] << ", " << arestes[arestes.size() - 1][1] << ")]" << endl;

	Graf gTasques1(nodes, arestes, pesos, true);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gTasques1.mostra();

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Buscant cicles al graf....." << endl;

	bool hihaCicle = gTasques1.existeixCicle();

	cout << "Comment :=>> -----" << endl;
	cout << "Comment :=>> Resultat esperat: ";
	mostraBool(resultat[nProva]);
	cout << endl;
	cout << "Comment :=>> Resultat obtingut: ";
	mostraBool(hihaCicle);
	cout << endl;

	if (resultat[nProva] == hihaCicle)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 4.0;
	}

	arestes = { { 0,1 },{ 0,2 },{ 0,3 },{ 2,1 },{ 2,3 },{ 1,4 },{ 1,5 },{ 3,5 },{ 6,3 },{ 5,4 },{ 5,6 },{ 4,7 },{ 4,8 },{ 6,8 },{ 6,9 },{ 7,8 },
	{ 8,9 },{ 7,10 },{ 8,10 },{ 9,10 } };

	pesos = { 5,5,5,7,7,10,10,4,4,6,6,3,3,9,9,2,8,2,8,4 };

	nProva++;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> TEST " << nProva + 1 << endl;
	cout << "Comment :=>> ------------" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> Inicialitzant el graf ......." << endl;
	cout << "Comment :=>> Nodes: [";
	for (int i = 0; i < (numNodes - 1); i++)
		cout << nodes[i] << ", ";
	cout << nodes[numNodes - 1] << "]" << endl;
	cout << "Comment :=>> Arestes: [";
	for (int i = 0; i < arestes.size() - 1; i++)
		cout << "(" << arestes[i][0] << ", " << arestes[i][1] << "),";
	cout << "(" << arestes[arestes.size() - 1][0] << ", " << arestes[arestes.size() - 1][1] << ")]" << endl;

	Graf gTasques2(nodes, arestes, pesos, true);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gTasques2.mostra();

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Buscant cicles al graf.....:" << endl;

	hihaCicle = gTasques2.existeixCicle();

	cout << "Comment :=>> -----" << endl;
	cout << "Comment :=>> Resultat esperat: ";
	mostraBool(resultat[nProva]);
	cout << endl;
	cout << "Comment :=>> Resultat obtingut: ";
	mostraBool(hihaCicle);
	cout << endl;

	if (resultat[nProva] == hihaCicle)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 4.0;
	}


	arestes = { { 0,1 },{ 0,2 },{ 2,1 },{ 1,4 },{ 3,5 },{ 6,3 },{ 5,4 },{ 5,6 },{ 4,7 },{ 4,8 },{ 6,8 },{ 6,9 },{ 7,8 },
	{ 8,9 },{ 7,10 },{ 8,10 },{ 9,10 } };

	pesos = { 5,5,5,7,7,10,10,4,4,6,6,3,3,9,9,2,8 };

	nProva++;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> TEST " << nProva + 1 << endl;
	cout << "Comment :=>> ------------" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> Inicialitzant el graf ......." << endl;
	cout << "Comment :=>> Nodes: [";
	for (int i = 0; i < (numNodes - 1); i++)
		cout << nodes[i] << ", ";
	cout << nodes[numNodes - 1] << "]" << endl;
	cout << "Comment :=>> Arestes: [";
	for (int i = 0; i < arestes.size() - 1; i++)
		cout << "(" << arestes[i][0] << ", " << arestes[i][1] << "),";
	cout << "(" << arestes[arestes.size() - 1][0] << ", " << arestes[arestes.size() - 1][1] << ")]" << endl;

	Graf gTasques3(nodes, arestes, pesos, true);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gTasques3.mostra();

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Buscant cicles al graf.....:" << endl;

	hihaCicle = gTasques3.existeixCicle();

	cout << "Comment :=>> -----" << endl;
	cout << "Comment :=>> Resultat esperat: ";
	mostraBool(resultat[nProva]);
	cout << endl;
	cout << "Comment :=>> Resultat obtingut: ";
	mostraBool(hihaCicle);
	cout << endl;

	if (resultat[nProva] == hihaCicle)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 4.0;
	}

	return reduccio;
}

float testOrdreTasques()
{
	float reduccio = 0.0;

	int numNodes;

	vector<string> nodes;
	vector<vector<int>> arestes;
	vector<int> pesos;
	queue<string> recorregut;
	stack<string> ordre;
	vector<string> ordreEsperat1, ordreEsperat2;
	vector<string> ordreObtingut;

	numNodes = 11;
	nodes.resize(numNodes);
	nodes = { "Tasca 1","Tasca 2","Tasca 3","Tasca 4","Tasca 5","Tasca 6","Tasca 7","Tasca 8","Tasca 9","Tasca 10","Tasca 11" };

	arestes = { {0,1},{0,2},{0,3},{2,1},{2,3},{1,4},{1,5},{3,5},{3,6},{5,4},{5,6},{4,7},{4,8},{6,8},{6,9},{7,8},
		{8,9},{7,10},{8,10},{9,10} };

	pesos = { 5,5,5,7,7,10,10,4,4,6,6,3,3,9,9,2,8,2,8,4 };

	ordreEsperat1 = {"Tasca 1", "Tasca 3", "Tasca 2", "Tasca 4", "Tasca 6", "Tasca 5", "Tasca 7", "Tasca 8", "Tasca 9", "Tasca 10", "Tasca 11" };
	ordreEsperat2 = { "Tasca 1", "Tasca 3", "Tasca 4", "Tasca 2", "Tasca 6", "Tasca 7", "Tasca 5", "Tasca 8", "Tasca 9", "Tasca 10", "Tasca 11" };

	cout << endl;
	cout << "Comment :=>> Iniciant test de DFS per trobar ordre de les tasques" << endl;
	cout << "Comment :=>> ====================================================" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> TEST 1" << endl;
	cout << "Comment :=>> ------------" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> Inicialitzant el graf ......." << endl;
	cout << "Comment :=>> Nodes: [";
	for (int i = 0; i < (numNodes - 1); i++)
		cout << nodes[i] << ", ";
	cout << nodes[numNodes - 1] << "]" << endl;
	cout << "Comment :=>> Arestes: [";
	for (int i = 0; i < arestes.size() - 1; i++)
		cout << "(" << arestes[i][0] << ", " << arestes[i][1] << "),";
	cout << "(" << arestes[arestes.size() - 1][0] << ", " << arestes[arestes.size() - 1][1] << ")]" << endl;

	Graf gTasques1(nodes, arestes, pesos, true);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gTasques1.mostra();

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Realitzant DFS per trobar ordre de les tasques a partir de Tasca 1:" << endl;

	gTasques1.DFS("Tasca 1", recorregut, ordre);
	while (!ordre.empty())
	{
		ordreObtingut.push_back(ordre.top());
		ordre.pop();
	}

	cout << "Comment :=>> -----" << endl;
	cout << "Comment :=>> Ordre de tasques esperat: ";
	mostraNodes(ordreEsperat1);
	cout << endl;
	cout << "Comment :=>> Ordre de tasques esperat (alternatiu): ";
	mostraNodes(ordreEsperat2);
	cout << endl;
	cout << "Comment :=>> -----" << endl;
	cout << "Comment :=>> Ordre de tasques obtingut: ";
	mostraNodes(ordreObtingut);
	cout << endl;

	if ((ordreObtingut == ordreEsperat1) || (ordreObtingut == ordreEsperat2))
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 5.0;
	}

	arestes = { { 0,1 },{ 0,2 },{ 2,1 },{ 1,4 },{ 3,5 },{ 3,6 },{ 5,6 },{ 4,7 },{ 4,8 },{ 7,8 },
	{ 8,9 },{ 7,10 },{ 8,10 },{ 9,10 } };

	pesos = { 5,5,5,7,7,10,10,4,4,6,6,3,3,9 };

	ordreEsperat1 = { "Tasca 1", "Tasca 3", "Tasca 2", "Tasca 5", "Tasca 8", "Tasca 9", "Tasca 10", "Tasca 11" };

	cout << "Comment :=>>" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> TEST 2" << endl;
	cout << "Comment :=>> ------------" << endl;
	cout << "Comment :=>>" << endl;
	cout << "Comment :=>> Inicialitzant el graf ......." << endl;
	cout << "Comment :=>> Nodes: [";
	for (int i = 0; i < (numNodes - 1); i++)
		cout << nodes[i] << ", ";
	cout << nodes[numNodes - 1] << "]" << endl;
	cout << "Comment :=>> Arestes: [";
	for (int i = 0; i < arestes.size() - 1; i++)
		cout << "(" << arestes[i][0] << ", " << arestes[i][1] << "),";
	cout << "(" << arestes[arestes.size() - 1][0] << ", " << arestes[arestes.size() - 1][1] << ")]" << endl;

	Graf gTasques2(nodes, arestes, pesos, true);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gTasques2.mostra();

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Realitzant DFS per trobar ordre de les tasques a partir de Tasca 1:" << endl;

	ordreObtingut.clear();
	gTasques2.DFS("Tasca 1", recorregut, ordre);
	while (!ordre.empty())
	{
		ordreObtingut.push_back(ordre.top());
		ordre.pop();
	}

	cout << "Comment :=>> -----" << endl;
	cout << "Comment :=>> Ordre de tasques esperat: ";
	mostraNodes(ordreEsperat1);
	cout << endl;
	cout << "Comment :=>> -----" << endl;
	cout << "Comment :=>> Ordre de tasques obtingut: ";
	mostraNodes(ordreObtingut);
	cout << endl;

	if (ordreObtingut == ordreEsperat1)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 5.0;
	}

	return reduccio;
}

int main()
{
	float grade = 0.0;
	float reduccio;

	cout << endl;
	cout << "Comment :=>> Iniciant test " << endl;
	cout << "Comment :=>> ==============" << endl;

	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testOrdreTasques();
	if (reduccio > 10.0)
		reduccio = 10.0;
	grade += (10.0 - reduccio);

	cout << "Grade :=>> " << grade << endl;


	testCicles();


	if (grade < 0)
		grade = 0.0;
	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
	return 0;


}