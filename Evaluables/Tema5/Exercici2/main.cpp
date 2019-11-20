#pragma once
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <vector>
#include "GrafList.h"

using namespace std;


bool comparaCamins(vector<list<string>>& caminsEsperats, vector<list<string>>& camins)
{
	bool iguals = (caminsEsperats.size() == camins.size());
	int i = 0;
	while (iguals && (i < caminsEsperats.size()))
	{
		int j = 0;
		iguals = false;
		while (!iguals && (j < camins.size()))
		{
			if (caminsEsperats[i] == camins[j])
				iguals = true;
			else
				j++;
		}
		i++;
	}
	return iguals;
}

bool comparaCicle(string cicleEsperat[], vector<vector<string>>& ciclesGraf, int posCicle)
{
	bool iguals = true;
	int i = 0;
	while (iguals && (i < 3))
	{
		int j = 0;
		iguals = false;
		while (!iguals && (j < 3))
		{
			if (cicleEsperat[i] == ciclesGraf[posCicle][j])
				iguals = true;
			else
				j++;
		}
		i++;
	}
	return iguals;
}

bool comparaCicles(string ciclesEsperats[][3], vector<vector<string>>& ciclesGraf, int nCiclesEsperats)
{
	bool iguals = (ciclesGraf.size() == nCiclesEsperats);
	int i = 0;
	while (iguals && (i < nCiclesEsperats))
	{
		int j = 0;
		iguals = false;
		while (!iguals && (j < ciclesGraf.size()))
		{
			if (comparaCicle(ciclesEsperats[i], ciclesGraf, j))
				iguals = true;
			else
				j++;
		}
		i++;
	}
	return iguals;
}


float testGrafNoDirigit()
{
	float reduccio = 0.0;

	int numNodes = 11;

	vector<string> nodes;
	nodes.resize(numNodes);
	nodes = { "Tasca 1","Tasca 2","Tasca 3","Tasca 4","Tasca 5","Tasca 6","Tasca 7","Tasca 8","Tasca 9","Tasca 10","Tasca 11" };

	vector<vector<int>> arestes;
	arestes = { { 0,1 },{ 0,2 },{ 3,0 },{ 2,1 },{ 2,3 },{ 4,1 },{ 1,5 },{ 3,5 },{ 6,3 },{ 5,4 },{ 5,6 },{ 4,7 },{ 6,9 },{ 7,8 },{ 7,10 }};

	vector<int> pesos = { 5,5,7,7,10,10,4,4,6,6,3,3,9,9,1}; //20 pesos


	cout << endl;
	cout << "Comment :=>> Iniciant test de Graf NO Dirigit" << endl;
	cout << "Comment :=>> ================================" << endl;
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

	Graf g(nodes, arestes, pesos, false);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;
	g.mostra();

	// TEST CICLES DEL GRAF
	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ==============================================" << endl;
	cout << "Comment :=>> Test del metode per trobar els cicles del graf" << endl;
	vector<vector<string>> ciclesGraf;
	ciclesGraf = g.cicles();

	const int MAX_CICLES = 4;
	string ciclesEsperats[MAX_CICLES][3] =
	{
		{ "Tasca 1", "Tasca 2", "Tasca 3" },
		{ "Tasca 1", "Tasca 3", "Tasca 4" },
		{ "Tasca 2", "Tasca 5", "Tasca 6" },
		{ "Tasca 4", "Tasca 6", "Tasca 7" },
	};

	cout << "Comment :=>> Resultat esperat: " << endl;
	for (int i = 0; i < MAX_CICLES; i++)
		cout << "Comment : = >> " << ciclesEsperats[i][0] << ", " << ciclesEsperats[i][1] << ", " << ciclesEsperats[i][2] << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	for (int i = 0; i < ciclesGraf.size(); i++)
		cout << "Comment : = >> " << ciclesGraf[i][0] << ", " << ciclesGraf[i][1] << ", " << ciclesGraf[i][2] << endl;

	bool correcte = comparaCicles(ciclesEsperats, ciclesGraf, MAX_CICLES);

	if (correcte)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 2.0;
	}

	// TEST GRAUS d'un node
	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ======================================================" << endl;
	cout << "Comment :=>> Test del metode per trobar grau IN dels nodes del graf" << endl;
	cout << "Comment :=>> Calculant grau IN per tots els nodes del graf........." << endl;
	vector<int> grausIn;
	grausIn.resize(numNodes);
	for (int i = 0; i < numNodes; i++)
		grausIn[i] = g.grauInNode(nodes[i]);

	vector<int> grausInEsperat = { 3, 4, 3, 4, 3, 4, 3, 3, 1, 1, 1 };
	cout << "Comment :=>> Resultat esperat: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausInEsperat[i] << ",";
	cout << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausIn[i] << ",";
	cout << endl;

	if (grausInEsperat == grausIn)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 2.0;
	}


	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ======================================================" << endl;
	cout << "Comment :=>> Test del metode per trobar grau OUT dels nodes del graf" << endl;
	cout << "Comment :=>> Calculant grau IN per tots els nodes del graf........." << endl;
	vector<int> grausOut;
	grausOut.resize(numNodes);
	for (int i = 0; i < numNodes; i++)
		grausOut[i] = g.grauOutNode(nodes[i]);

	vector<int> grausOutEsperat = { 3, 4, 3, 4, 3, 4, 3, 3, 1, 1, 1 };
	cout << "Comment :=>> Resultat esperat: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausOutEsperat[i] << ",";
	cout << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausOut[i] << ",";
	cout << endl;

	if (grausOutEsperat == grausOut)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 2.0;
	}

	// TEST DELS CAMINS d'una tasca a una altra
	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ===================================================" << endl;
	cout << "Comment :=>> *************** TEST NO AVALUABLE *****************" << endl;
	cout << "Comment :=>> Test del metode per trobar els camins possibles entre dos nodes del graf" << endl;
	cout << "Comment :=>> Calculant els damins des de tasca 1 fins a tasca 1" << endl;

	vector<list<string>> camins;
	g.camins("Tasca 1", "Tasca 2", camins);

	vector<list<string>> caminsEsperats =
	{
		{ "Tasca 1", "Tasca 2" },
		{ "Tasca 1", "Tasca 3", "Tasca 2"},
		{ "Tasca 1", "Tasca 3", "Tasca 4", "Tasca 6", "Tasca 2" },
		{ "Tasca 1", "Tasca 3", "Tasca 4", "Tasca 6", "Tasca 5", "Tasca 2" },
		{ "Tasca 1", "Tasca 3", "Tasca 4", "Tasca 7", "Tasca 6", "Tasca 2" },
		{ "Tasca 1", "Tasca 3", "Tasca 4", "Tasca 7", "Tasca 6", "Tasca 5", "Tasca 2" },
		{ "Tasca 1", "Tasca 4", "Tasca 3", "Tasca 2" },
		{ "Tasca 1", "Tasca 4", "Tasca 6", "Tasca 2" },
		{ "Tasca 1", "Tasca 4", "Tasca 6", "Tasca 5", "Tasca 2" },
		{ "Tasca 1", "Tasca 4", "Tasca 7", "Tasca 6", "Tasca 2" },
		{ "Tasca 1", "Tasca 4", "Tasca 7", "Tasca 6", "Tasca 5", "Tasca 2" },
	};

	cout << "Comment :=>> Resultat esperat: " << endl;
	for (int i = 0; i < caminsEsperats.size(); i++)
	{
		list<string>::iterator it;
		cout << "Comment :=>> ";
		for (it = caminsEsperats[i].begin(); it != caminsEsperats[i].end(); it++)
			cout << (*it) << ",";
		cout << endl;
	}
	cout << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	for (int i = 0; i < camins.size(); i++)
	{
		cout << "Comment :=>> ";
		list<string>::iterator it;
		for (it = camins[i].begin(); it != camins[i].end(); it++)
			cout << (*it) << ",";
		cout << endl;
	}
	if (comparaCamins(caminsEsperats, camins))
		cout << "Comment :=>> CORRECTE" << endl;
	else
		cout << "Comment :=>> ERROR" << endl;

	return reduccio;
}
float testGrafDirigit()
{
	float reduccio = 0.0;

	int numNodes = 11;

	vector<string> nodes;
	nodes.resize(numNodes);
	nodes = { "Tasca 1","Tasca 2","Tasca 3","Tasca 4","Tasca 5","Tasca 6","Tasca 7","Tasca 8","Tasca 9","Tasca 10","Tasca 11" };

	vector<vector<int>> arestes;
	arestes = { { 0,1 },{ 0,2 },{ 3,0 },{ 2,1 },{ 2,3 },{ 4,1 },{ 1,5 },{ 3,5 },{ 6,3 },{ 5,4 },{ 5,6 },{ 4,7 },{ 4,8 },{ 6,8 },{ 6,9 },{ 7,8 },{ 8,9 },{ 7,10 },{ 8,10 },{ 9,10 } };

	vector<int> pesos = { 5,5,5,7,7,10,10,4,4,6,6,3,3,9,9,1,8,2,8,4 }; //20 pesos


	cout << endl;
	cout << "Comment :=>> Iniciant test de Graf Dirigit" << endl;
	cout << "Comment :=>> =============================" << endl;
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

	Graf g(nodes, arestes, pesos, true);

	cout << "Comment :=>> -----------------------------" << endl;
	cout << "Comment :=>> Graf despres inicialitzacio:" << endl;
	g.mostra();

	// TEST CICLES DEL GRAF
	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ==============================================" << endl;
	cout << "Comment :=>> Test del metode per trobar els cicles del graf" << endl;
	vector<vector<string>> ciclesGraf;
	ciclesGraf = g.cicles();

	const int MAX_CICLES = 3;
	string ciclesEsperats[MAX_CICLES][3] =
	{
		{ "Tasca 1", "Tasca 3", "Tasca 4" },
		{ "Tasca 2", "Tasca 6", "Tasca 5" },
		{ "Tasca 4", "Tasca 6", "Tasca 7" },
	};

	cout << "Comment :=>> Resultat esperat: " << endl;
	for (int i = 0; i < MAX_CICLES; i++)
		cout << "Comment : = >> " << ciclesEsperats[i][0] << ", " << ciclesEsperats[i][1] << ", " << ciclesEsperats[i][2] << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	for (int i = 0; i < ciclesGraf.size(); i++)
		cout << "Comment : = >> " << ciclesGraf[i][0] << ", " << ciclesGraf[i][1] << ", " << ciclesGraf[i][2] << endl;

	bool correcte = comparaCicles(ciclesEsperats, ciclesGraf, MAX_CICLES);

	if (correcte)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 2.0;
	}

	// TEST GRAUS d'un node
	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ======================================================" << endl;
	cout << "Comment :=>> Test del metode per trobar grau IN dels nodes del graf" << endl;	
	cout << "Comment :=>> Calculant grau IN per tots els nodes del graf........." << endl;	
	vector<int> grausIn;
	grausIn.resize(numNodes);
	for (int i = 0; i < numNodes; i++)
		grausIn[i] = g.grauInNode(nodes[i]);

	vector<int> grausInEsperat = { 1, 3, 1, 2, 1, 2, 1, 1, 3, 2, 3 };
	cout << "Comment :=>> Resultat esperat: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausInEsperat[i] << ",";
	cout << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausIn[i] << ",";
	cout << endl;

	if (grausInEsperat == grausIn)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 2.0;
	}


	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ======================================================" << endl;
	cout << "Comment :=>> Test del metode per trobar grau OUT dels nodes del graf" << endl;
	cout << "Comment :=>> Calculant grau IN per tots els nodes del graf........." << endl;
	vector<int> grausOut;
	grausOut.resize(numNodes);
	for (int i = 0; i < numNodes; i++)
		grausOut[i] = g.grauOutNode(nodes[i]);

	vector<int> grausOutEsperat = { 2, 1, 2, 2, 3, 2, 3, 2, 2, 1, 0 };
	cout << "Comment :=>> Resultat esperat: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausOutEsperat[i] << ",";
	cout << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	cout << "Comment :=>> ";
	for (int i = 0; i < numNodes; i++)
		cout << grausOut[i] << ",";
	cout << endl;

	if (grausOutEsperat == grausOut)
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio += 2.0;
	}

	// TEST DELS CAMINS d'una tasca a una altra
	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> ===================================================" << endl;
	cout << "Comment :=>> *************** TEST NO AVALUABLE *****************" << endl;
	cout << "Comment :=>> Test del metode per trobar els camins possibles entre dos nodes del graf" << endl;
	cout << "Comment :=>> Calculant els damins des de tasca 2 fins a tasca 9" << endl;
	
	vector<list<string>> camins;
	g.camins("Tasca 2", "Tasca 9", camins);
	
	vector<list<string>> caminsEsperats = 
	{
		{ "Tasca 2", "Tasca 6", "Tasca 5", "Tasca 8", "Tasca 9" },
		{ "Tasca 2", "Tasca 6", "Tasca 5", "Tasca 9" },
		{ "Tasca 2", "Tasca 6", "Tasca 7", "Tasca 9" },
	};

	cout << "Comment :=>> Resultat esperat: " << endl;
	for (int i = 0; i < caminsEsperats.size(); i++)
	{
		list<string>::iterator it;
		cout << "Comment :=>> ";
		for (it = caminsEsperats[i].begin(); it != caminsEsperats[i].end(); it++)
			cout << (*it) << ",";
		cout << endl;
	}
	cout << endl;
	cout << "Comment :=>> ---" << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	for (int i = 0; i < camins.size(); i++)
	{
		list<string>::iterator it;
		cout << "Comment :=>> ";
		for (it = camins[i].begin(); it != camins[i].end(); it++)
			cout << (*it) << ",";
		cout << endl;
	}
	if (comparaCamins(caminsEsperats, camins))
		cout << "Comment :=>> CORRECTE" << endl;
	else
		cout << "Comment :=>> ERROR" << endl;

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

	reduccio = testGrafNoDirigit();
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade += (5.0 - reduccio);

	cout << "Grade :=>> " << grade << endl;

	reduccio = testGrafDirigit();
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade += (5.0 - reduccio);


	if (grade < 0)
		grade = 0.0;
	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
	return 0;
}