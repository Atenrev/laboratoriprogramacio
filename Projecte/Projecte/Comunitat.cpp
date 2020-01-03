#include "Comunitat.h"

Comunitat::Comunitat(MatriuSparse* pMAdj)
{
	m_pMAdj = pMAdj;
	m_primComdeltaQ = 0; // Estava a -1
	m_Q = 0;
	m_M2 = 0;
}

Comunitat::~Comunitat()
{
	m_pMAdj = nullptr;	
}

void Comunitat::init()
{

}

void Comunitat::clear()
{
	m_pMAdj = nullptr;
	m_deltaQ.clear();
	m_indexComs.clear();
	m_maxDeltaQFil.clear();
	m_primComdeltaQ=-1;
	m_vDendrograms.clear();
	m_k.clear();
	m_A.clear();
	m_hTotal.clear();
	m_Q=0;
	m_M2=0;	
}

void Comunitat::calculaA()
{
	m_A.reserve(m_pMAdj->getNFiles());
	for (auto it = m_k.begin(); it != m_k.end(); it++)
		m_A.emplace_back((double) *it / m_M2);
}

void Comunitat::creaIndexComs()
{
	m_indexComs.reserve(m_pMAdj->getNFiles());
	for (int i = 0; i < m_pMAdj->getNFiles(); i++)
		m_indexComs.emplace_back(i+1, i-1);
}

void Comunitat::creaDeltaQHeap()
{
	m_pMAdj->createMaps(m_deltaQ);
	m_maxDeltaQFil.resize(m_deltaQ.size());
	m_hTotal.resize(m_deltaQ.size());
	int index;
	ElemHeap elh;

	for (auto it = m_deltaQ.begin(); it != m_deltaQ.end(); it++)
	{
		index = distance(m_deltaQ.begin(), it);

		for (auto it_map = (*it).begin(); it_map != (*it).end(); it_map++)
		{
			// (1/m2) - (k[i]*k[j]) / (m2*m2)
			(*it_map).second = 1.0 / m_M2 
				- (((double) m_k[(*it_map).first.first] * m_k[(*it_map).first.second]) 
					/ ((double) m_M2 * m_M2));
			
			if (m_maxDeltaQFil[index].second < (*it_map).second)
			{
				m_maxDeltaQFil[index].first = (*it_map).first.second;
				m_maxDeltaQFil[index].second = (*it_map).second;
			}
		}

		if ((*it).size() > 0)
			elh = ElemHeap(m_maxDeltaQFil[index].second, pair<int, int>(index, m_maxDeltaQFil[index].first));
		else
			elh = ElemHeap(-2, pair<int, int>(index, -1));
		m_hTotal.insert(elh);
	}
}

void Comunitat::modificaVei(int vei)
{
	ElemHeap elh;

	if (m_deltaQ[vei].size() > 0)
	{
		m_maxDeltaQFil[vei].second = -2;
		for (auto it = m_deltaQ[vei].begin(); it != m_deltaQ[vei].end(); it++)
		{
			if (m_maxDeltaQFil[vei].second < (*it).second)
			{
				m_maxDeltaQFil[vei].first = (*it).first.second;
				m_maxDeltaQFil[vei].second = (*it).second;
			}
		}

		elh = ElemHeap(m_maxDeltaQFil[vei].second, pair<int, int>(vei, m_maxDeltaQFil[vei].first));
	}
	else
	{
		elh = ElemHeap(-2, pair<int, int>(vei, -1));
	}

	m_hTotal.modifElem(elh);
}

void Comunitat::fusiona(int com1, int com2)
{
	pair<int, int> j_vei, vei_j, vei_i;
	double a;

	for (auto it = m_deltaQ[com1].begin(); it != m_deltaQ[com1].end(); it++)
	{
		j_vei = pair<int, int>(com2, (*it).first.second);
		vei_j = pair<int, int>(j_vei.second, j_vei.first);
		vei_i = pair<int, int>((*it).first.second, (*it).first.first);

		if (vei_i.first != com2)
		{
			if (m_deltaQ[com2].count(j_vei) > 0)
			{
				m_deltaQ[vei_j.first][vei_j] += m_deltaQ[vei_i.first][vei_i];
				m_deltaQ[vei_i.first].erase(vei_i);
				m_deltaQ[com2][j_vei] += (*it).second;
			}
			else
			{
				a = 2.0 * m_A[com2] * m_A[vei_i.first];
				m_deltaQ[vei_j.first][vei_j] = m_deltaQ[vei_i.first][vei_i] - a;
				m_deltaQ[vei_i.first].erase(vei_i);
				// Nova relació
				m_deltaQ[com2][j_vei] = (*it).second - a;
			}

			modificaVei(vei_i.first);
		}
	}

	// i i j invertits
	for (auto it = m_deltaQ[com2].begin(); it != m_deltaQ[com2].end(); it++)
	{
		j_vei = pair<int, int>(com1, (*it).first.second);
		vei_j = pair<int, int>(j_vei.second, j_vei.first);
		vei_i = pair<int, int>((*it).first.second, (*it).first.first);

		if (m_deltaQ[com1].count(j_vei) == 0)
		{
			a = 2.0 * m_A[com1] * m_A[vei_i.first];
			m_deltaQ[vei_i.first][vei_i] -= a;
			(*it).second -= a;
			modificaVei(vei_i.first);
		}
	}

	m_deltaQ[com2].erase(pair<int, int>(com2, com1));
	modificaVei(com2);

	m_deltaQ[com1].clear();
	m_hTotal.delElem(com1);
}

void Comunitat::generaDendrogram(int pos1, int pos2, double deltaQp1p2)
{
	Tree<double>* tree_com2 = new Tree<double>(deltaQp1p2);
	tree_com2->setLeft(m_vDendrograms[pos2]);
	tree_com2->setRight(m_vDendrograms[pos1]);
	m_vDendrograms[pos2] = tree_com2;
	m_vDendrograms[pos1] = nullptr;
}

void Comunitat::calculaComunitats(list<Tree<double>*>& listDendrogram)
{
	calculaM2();
	calculaK();
	calculaA();
	creaIndexComs();
	creaDeltaQHeap();
	m_k.clear();
	InicialitzaDendrograms();
	
	ElemHeap e = m_hTotal.max();
	m_hTotal.delMax();
	int i, j;
	while (m_hTotal.size() > 0 && e.getVal() > 0.0) 
	{
		i = e.getPos().first;
		j = e.getPos().second;
		m_Q += e.getVal();
		fusiona(i, j);

		if (m_indexComs[i].first < m_indexComs.size())
			m_indexComs[m_indexComs[i].first].second = m_indexComs[i].second;

		if (m_indexComs[i].second != -1)
			m_indexComs[m_indexComs[i].second].first = m_indexComs[i].first;
		else
			m_primComdeltaQ = m_indexComs[i].first;

		generaDendrogram(i, j, m_Q);
		m_A[j] = m_A[j] + m_A[i];

		e = m_hTotal.max();
		m_hTotal.delMax();
	}

	int c = m_primComdeltaQ;
	while (c < m_indexComs.size())
	{
		listDendrogram.emplace_back(m_vDendrograms[c]);
		c = m_indexComs[c].first;
	}
}

