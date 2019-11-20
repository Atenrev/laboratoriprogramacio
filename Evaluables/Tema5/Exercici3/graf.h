#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <cstdio>
using namespace std;

class Graf
{
public:
	Graf();
	Graf(vector<string>& nodes, vector<vector<int>> parellesNodes, bool dirigit);
	Graf(vector<string>& nodes, vector<vector<int>> parellesNodes, vector<int> pesos, bool dirigit);
	~Graf();

	int getNumNodes() { return m_numNodes; }

	void inserirAresta(int posNode1, int posNode2);
	void inserirAresta(int posNode1, int posNode2, int pes);
	void eliminarAresta(int posNode1, int posNode2);

	void afegirNode(string node);
	void eliminarNode(string node);

	void DFS(string nodeInicial, queue<string>& recorregut);
	void DFS(string nodeInicial, queue<string>& recorregut, stack<string>& ordre);
	bool existeixCicle();
	
	void mostra();
private:
	vector<string> m_nodes;
	vector<vector<int>> m_matriuAdj;
	int m_numNodes;
	int m_numArestes;
	bool m_dirigit;

	void crearMatriu(vector<vector<int>> parelles);
	void crearMatriu(vector<vector<int>> parelles, vector<int> pesos);
	void DFSRec(int pos, queue<string>& recorregut, vector<bool>& visitat);
	void DFSRec(int pos, queue<string>& recorregut, stack<string>& ordre, vector<bool>& visitat);
	bool cicleRec(int pos, vector<bool> visitat);
};

