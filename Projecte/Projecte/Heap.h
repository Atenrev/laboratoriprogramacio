#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "ElemHeap.h"
using namespace std;

class Heap {
public:
	Heap() { m_act = -1; m_maxEls = 0; };
	Heap(int maxEls) { m_act = -1; m_maxEls = maxEls; m_data.resize(m_maxEls, ElemHeap()); m_index.resize(m_maxEls, -1);	};
	Heap(const Heap& h);
	~Heap() {};
	Heap& operator=(const Heap& h);

	ElemHeap& max() { return m_data[0]; }
	int size() { return m_act+1; }
	friend std::ostream& operator<<(std::ostream& out, const Heap& h);
	void insert(const ElemHeap& el);
	void resize(int mida) {	m_data.resize(mida, ElemHeap()); m_index.resize(mida, -1); m_maxEls = mida; m_act = -1;};
	void delMax();
	void delElem(int pos);
	void modifElem(const ElemHeap& nouVal);
	void clear();
	bool operator==(const Heap& h);

private:
	vector<ElemHeap> m_data;
	//Guardem els indexos del vei inicial per cada un dels valors que tenim guardats
	vector<int> m_index;
	int m_maxEls; //indica nombre total de nodes: array va de 0 a m_maxEls-1
	int m_act; //indica posicio ultima ocupada: inicialment -1

	int pare(int pos) const { return ((pos - 1) / 2); }
	int fillEsq(int pos) const  { return ((2 * pos) + 1); }
	int fillDret(int pos) const { return ((2 * pos) + 2); }
	void intercanvia(int pos1, int pos2) { ElemHeap aux = m_data[pos1]; m_data[pos1] = m_data[pos2]; m_data[pos2] = aux;}

	std::ostream& printRec(std::ostream& out,int pos,int n) const;
	void ascendir(int pos);
	void descendir(int pos);
};
