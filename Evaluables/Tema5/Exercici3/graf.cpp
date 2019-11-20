#include "graf.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


Graf::Graf()
{
	m_numNodes = 0;
}

Graf::Graf(vector<string>& nodes, vector<vector<int>> parellesNodes, bool dirigit)
{
	m_nodes = nodes; 
	m_numNodes = m_nodes.size();
	m_dirigit = dirigit;
	crearMatriu(parellesNodes);
}

Graf::Graf(vector<string>& nodes, vector<vector<int>> parellesNodes, vector<int> pesos, bool dirigit)
{
	m_nodes = nodes;
	m_numNodes = m_nodes.size();
	m_dirigit = dirigit;
	crearMatriu(parellesNodes, pesos);
}


Graf::~Graf()
{
}

void Graf::crearMatriu(vector<vector<int>> parelles)
{
	m_matriuAdj.resize(m_numNodes);
	for (int i=0; i<m_numNodes;i++)
	{
		m_matriuAdj[i].resize(m_numNodes,0);
	}

	for (int i = 0; i < parelles.size(); i++)
	{
		m_matriuAdj[parelles[i][0]][parelles[i][1]] = 1;
		if (!m_dirigit)
			m_matriuAdj[parelles[i][1]][parelles[i][0]] = 1;
	}
}

void Graf::crearMatriu(vector<vector<int>> parelles, vector<int> pesos)
{
	m_matriuAdj.resize(m_numNodes);
	for (auto &it : m_matriuAdj)
	{
		it.resize(m_numNodes);
	}

	for (int i = 0; i < parelles.size(); i++)
	{
		m_matriuAdj[parelles[i][0]][parelles[i][1]] = pesos[i];
		if (!m_dirigit)
			m_matriuAdj[parelles[i][1]][parelles[i][0]] = pesos[i];
	}
}

void Graf::inserirAresta(int posNode1, int posNode2)
{
	m_matriuAdj[posNode1][posNode2] = 1;
	if (!m_dirigit)
		m_matriuAdj[posNode2][posNode1] = 1;
}

void Graf::inserirAresta(int posNode1, int posNode2, int pes)
{
	m_matriuAdj[posNode1][posNode2] = pes;
	if (!m_dirigit)
		m_matriuAdj[posNode2][posNode1] = pes;
}


void Graf::eliminarAresta(int posNode1, int posNode2)
{
	m_matriuAdj[posNode1][posNode2] = 0;
	if (!m_dirigit)
		m_matriuAdj[posNode2][posNode1] = 0;
}

void Graf::afegirNode(string node)
{
	//m_nodes.resize(m_numNodes);
	m_nodes.push_back(node);

	// add a row
	m_matriuAdj.push_back(std::vector<int>(m_numNodes));

	m_numNodes++;

	//m_matriuAdj.resize(m_numNodes);
	for (int i = 0; i < m_numNodes; i++) m_matriuAdj[i].push_back(0);
}

void Graf::eliminarNode(string node)
{
	//busquem la posici� del node a esborrar
	vector<string>::iterator it;
	
	it = find(m_nodes.begin(), m_nodes.end(), node);

	//eliminem el node del vector de nodes i de la matriu d'adjacencia
	if (it != m_nodes.end())
	{
		int pos = distance(m_nodes.begin(), it);
		// eliminem el node del vector de nodes
		//m_nodes.erase(m_nodes.begin() + pos);
		m_nodes.erase(it);

		// eliminem la fila i la columna de la matriu d'adjacencia corresponents a aquest node
		m_matriuAdj.erase(m_matriuAdj.begin() + pos);

		for (int i = 0; i < m_numNodes; i++)
		{			
			m_matriuAdj[i].erase(m_matriuAdj[i].begin() + pos);
		}
		m_numNodes--;
	}
}

void Graf::mostra() 
{
	int mida_c = 4;
	// imprimim el nom dels v�rtexs
	cout << setw(mida_c) << " ";
	for (int j = 0; j < m_numNodes; j++)
	{

		cout << setw(mida_c) << m_nodes[j] << " ";
	}
	cout << endl;

	for (int i = 0; i < m_numNodes; i++)
	{
		cout << setw(10) << m_nodes[i] << " ";
		for (int j = 0; j < m_numNodes; j++)
		{			
			cout << setw(mida_c) << m_matriuAdj[i][j] << " ";
		}
		cout << endl;
	}	
}


void Graf::DFSRec(int pos, queue<string>& recorregut, vector<bool>& visitat)
{
	visitat[pos] = true;
	recorregut.push(m_nodes[pos]);

	// Recur for all the vertices adjacent 
	// to this vertex 
	for (int col=0; col<m_numNodes;col++)
		if ((m_matriuAdj[pos][col]!=0) &&(!visitat[col]))
			DFSRec(col, recorregut, visitat);
}

void Graf::DFSRec(int pos, queue<string>& recorregut, stack<string>& ordre, vector<bool>& visitat)
{
	bool last_move = true;
	visitat[pos] = true;
	recorregut.push(m_nodes[pos]);

	// Recur for all the vertices adjacent 
	// to this vertex 
	for (int col = 0; col < m_numNodes; col++)
	{
		if ((m_matriuAdj[pos][col] != 0) && (!visitat[col]))
		{
			DFSRec(col, recorregut, ordre, visitat);
			last_move = false;
		}
	}

	ordre.push(m_nodes[pos]);
}

bool Graf::cicleRec(int pos, vector<bool> visitat)
{
	bool cicle = false;
	visitat[pos] = true;

	// Recur for all the vertices adjacent 
	// to this vertex 
	for (int col = 0; col < m_numNodes && !cicle; col++)
	{
		if (m_matriuAdj[pos][col] != 0)
		{
			if (visitat[col])
				cicle = true;
			else
				cicle = cicleRec(col, visitat);
		}
	}

	return cicle;
}

void Graf::DFS(string nodeInicial, queue<string>& recorregut)
{
	vector<string>::iterator itNode = find(m_nodes.begin(), m_nodes.end(), nodeInicial);
	vector<bool> visitat;
	visitat.resize(m_numNodes, false);

	if (itNode != m_nodes.end())
	{
		int pos = distance(m_nodes.begin(), itNode);
		DFSRec(pos, recorregut, visitat);
	}
}

void Graf::DFS(string nodeInicial, queue<string>& recorregut, stack<string>& ordre)
{
	vector<string>::iterator itNode = find(m_nodes.begin(), m_nodes.end(), nodeInicial);
	vector<bool> visitat;
	visitat.resize(m_numNodes, false);

	if (itNode != m_nodes.end())
	{
		int pos = distance(m_nodes.begin(), itNode);
		DFSRec(pos, recorregut, ordre, visitat);
	}
}


bool Graf::existeixCicle()
{
	bool cicle = false;
	vector<bool> visitat;
	visitat.resize(m_numNodes, false);

	for (auto itNode = m_nodes.begin(); itNode != m_nodes.end() && !cicle; itNode++)
	{
		int pos = distance(m_nodes.begin(), itNode);
		cicle = cicleRec(pos, visitat);
	}

	return cicle;
}