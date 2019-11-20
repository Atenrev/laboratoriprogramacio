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

	void mostra();
	void BFS(string nodeInicial, queue<string>& recorregut);
	int BFS(string nodeInicial, string nodeFinal, queue<string>& recorregut);
	void BFS(string nodeInicial, int distancia, queue<string>& recorregut);
	void BFS(string nodeInicial, string nodeFinal, queue<string>& recorregut, stack<string>& cami);


private:
	vector<string> m_nodes;
	vector<vector<int>> m_matriuAdj;
	int m_numNodes;
	int m_numArestes;
	bool m_dirigit;

	void crearMatriu(vector<vector<int>> parelles);
	void crearMatriu(vector<vector<int>> parelles, vector<int> pesos);

};

