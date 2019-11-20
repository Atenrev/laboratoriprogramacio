#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include "graf.h"

using namespace std;

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

bool igualsLlistaNodes(std::vector<string> &resultat, std::vector<string> &esperat)
{
	bool iguals = (esperat.size() == resultat.size());

	int i = 0;
	while ((i < esperat.size()) && iguals)
	{
		iguals = false;
		int j = 0;
		while ((j < resultat.size()) && !iguals)
		{
			if (resultat[j] == esperat[i])
				iguals = true;
			else j++;
		}
		i++;
	}
	return iguals;
}



float testProfunditat()
{
	float reduccio = 0.0;

	int numNodes;

	vector<string> nodes;
	vector<vector<int>> arestes;
	vector<int> pesos;

	const int N_PROVES = 4;
	vector<string> resultat[N_PROVES] =
	{
		{ "Tu", "Marc", "Maria", "Jordi" },
		{ "Tu", "Marc", "Maria", "Jordi", "Marta", "Aritz", "Berta", "Mar", "Umair"},
		{ "Tu", "Marta", "Maria", "Jordi", "Berta", "Aritz", "Nikita", "Joshua", "Marc", "Mar", "Umair", "Neus", "LA persona" },
		{ "Tu", "Marta", "Maria", "Jordi", "Berta", "Aritz", "Nikita", "Joshua", "Marc", "Mar", "Umair", "Neus", "LA persona" }
	};

	string nodeInicial = "Tu";

	numNodes = 13;
	nodes.resize(numNodes);
	nodes = { "Tu", "Marta", "Maria", "Jordi", "Berta", "Aritz", "Nikita", "Joshua", "Marc", "Mar", "Umair", "Neus", "LA persona" };
	arestes = { { 0,2 },{ 0,3 },{ 0,8 },{ 1,2 },{ 2,3 },{ 2,5 },{ 3,4 },{ 4,6 },{ 4,7 },{ 5,6 },{ 7,12 },{ 8,9 },{ 8,10 },{ 10,11 },{ 10,12 },{ 11,12 } };

	cout << endl;
	cout << "Comment :=>> Iniciant test de trobar tots els nodes fins a certa distancia" << endl;
	cout << "Comment :=>> (TEST NO AVALUABLE)" << endl;
	cout << "Comment :=>> =============================================================" << endl;
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

	Graf gConnexions(nodes, arestes, false);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gConnexions.mostra();

	for (int nProva = 0; nProva < N_PROVES; nProva++)
	{
		queue<string> recorregut;
		vector<string> recorregutObtingut;

		cout << "Comment :=>>" << endl;
		cout << "Comment :=>> TEST " << nProva + 1 << endl;
		cout << "Comment :=>> -----------------------------" << endl;
		cout << "Comment :=>> Buscant nodes a distancia " << nProva + 1 << endl;
		cout << "Comment :=>> Node Inicial: " << nodeInicial << endl;

		gConnexions.BFS(nodeInicial, nProva + 1, recorregut);
		while (!recorregut.empty())
		{
			recorregutObtingut.push_back(recorregut.front());
			recorregut.pop();
		}

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Resultat esperat: ";
		mostraNodes(resultat[nProva]);
		cout << endl;
		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Resultat obtingut: ";
		mostraNodes(recorregutObtingut);
		cout << endl;

		if (igualsLlistaNodes(resultat[nProva], recorregutObtingut))
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2.0;
		}
	}
	return reduccio;
}


float testCami()
{
	float reduccio = 0.0;

	int numNodes;

	vector<string> nodes;
	vector<vector<int>> arestes;
	vector<int> pesos;

	const int N_PROVES = 6;
	vector<string> resultat[N_PROVES] = 
		{ 
			{ "Tu", "Marc", "Umair", "LA persona" },
			{ "Tu", "Maria" },
			{ "Tu", "Jordi", "Berta" },
			{ "Tu", "Maria", "Aritz" },
			{ "Tu", "Jordi", "Berta", "Joshua" },
			{}
	};

	string nodeInicial = "Tu";
	string nodeFinal[N_PROVES] = { "LA persona", "Maria", "Berta", "Aritz", "Joshua", "Josep" };

	numNodes = 13;
	nodes.resize(numNodes);
	nodes = { "Tu", "Marta", "Maria", "Jordi", "Berta", "Aritz", "Nikita", "Joshua", "Marc", "Mar", "Umair", "Neus", "LA persona" };
	arestes = { { 0,2 },{ 0,3 },{ 0,8 },{ 1,2 },{ 2,3 },{ 2,5 },{ 3,4 },{ 4,6 },{ 4,7 },{ 5,6 },{ 7,12 },{ 8,9 },{ 8,10 },{ 10,11 },{ 10,12 },{ 11,12 } };

	cout << endl;
	cout << "Comment :=>> Iniciant test de trobar cami optim entre dos nodes" << endl;
	cout << "Comment :=>> ==================================================" << endl;
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

	Graf gConnexions(nodes, arestes, false);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gConnexions.mostra();

	for (int nProva = 0; nProva < N_PROVES; nProva++)
	{
		queue<string> recorregut;
		stack<string> cami;
		vector<string> camiObtingut;

		cout << "Comment :=>>" << endl;
		cout << "Comment :=>> TEST " << nProva + 1 << endl;
		cout << "Comment :=>> -----------------------------" << endl;
		cout << "Comment :=>> Buscant cami....." << endl;
		cout << "Comment :=>> Node Inicial: " << nodeInicial << endl;
		cout << "Comment :=>> Node Final: " << nodeFinal[nProva] << endl;

		gConnexions.BFS(nodeInicial, nodeFinal[nProva], recorregut, cami);
		while (!cami.empty())
		{
			camiObtingut.push_back(cami.top());
			cami.pop();
		}

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Resultat esperat: ";
		mostraNodes(resultat[nProva]);
		cout << endl;
		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Resultat obtingut: ";
		mostraNodes(camiObtingut);
		cout << endl;

		if (resultat[nProva] == camiObtingut)
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2.0;
		}
	}
	return reduccio;
}


float testNPassos()
{
	float reduccio = 0.0;

	int numNodes;

	vector<string> nodes;
	vector<vector<int>> arestes;
	vector<int> pesos;

	queue<string> recorregut;
	
	const int N_PROVES = 6;
	int resultat[N_PROVES] = { 3, 1, 2, 2, 3, -1};

	string nodeInicial = "Tu";
	string nodeFinal[N_PROVES] = { "LA persona", "Maria", "Berta", "Aritz", "Joshua", "Josep"};
	
	numNodes = 13;
	nodes.resize(numNodes);
	nodes = { "Tu", "Marta", "Maria", "Jordi", "Berta", "Aritz", "Nikita", "Joshua", "Marc", "Mar", "Umair", "Neus", "LA persona" };
	arestes = { { 0,2 },{ 0,3 },{ 0,8 },{ 1,2 },{ 2,3 },{ 2,5 },{ 3,4 },{ 4,6 },{ 4,7 },{ 5,6 },{ 7,12 },{ 8,9 },{ 8,10 },{ 10,11 },{ 10,12 },{ 11,12 } };
	
	cout << endl;
	cout << "Comment :=>> Iniciant test de trobar numero de connexions entre dos nodes" << endl;
	cout << "Comment :=>> ============================================================" << endl;
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

	Graf gConnexions(nodes, arestes, false);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;

	gConnexions.mostra();

	for (int nProva = 0; nProva < N_PROVES; nProva++)
	{
		cout << "Comment :=>>" << endl;
		cout << "Comment :=>> TEST " << nProva + 1 << endl;
		cout << "Comment :=>> -----------------------------" << endl;
		cout << "Comment :=>> Buscant numero de passos....." << endl;
		cout << "Comment :=>> Node Inicial: " << nodeInicial << endl;
		cout << "Comment :=>> Node Final: " << nodeFinal[nProva] << endl;

		int nPassos = gConnexions.BFS(nodeInicial, nodeFinal[nProva], recorregut);

		cout << "Comment :=>> -----" << endl;
		cout << "Comment :=>> Resultat esperat: " << resultat[nProva] << endl;
		cout << "Comment :=>> Resultat obtingut: " << nPassos << endl;

		if (resultat[nProva] == nPassos)
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2.0;
		}

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

	reduccio = testNPassos();
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade += (5.0 - reduccio);

	cout << "Grade :=>> " << grade << endl;

	reduccio = testCami();
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade += (5.0 - reduccio);

	cout << "Grade :=>> " << grade << endl;


	testProfunditat();


	if (grade < 0)
		grade = 0.0;
	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
	return 0;
}