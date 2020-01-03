#include "Graph.h"

void Graph::calculaComunitats(list<Tree<double>*>& listDendrogram)
{
	Comunitat c(&m_mAdjacencia);
	c.calculaComunitats(listDendrogram);
}

