#pragma once
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int NINF = -9999;

template <class T>
class Heap 
{
public:
	Heap() { m_actual = -1; m_max = 0; };
	Heap(const Heap<T>& h);
	~Heap() {};
	Heap<T>& operator=(const Heap<T>& h);

	T& getMinim() { return m_data[0]; }
	int getMida() { return m_actual; }
	void llegeix(const string& nomFitxer);
	friend std::ostream& operator<<(std::ostream& out, const Heap<T>& h)
	{
		if (h.m_actual  == -1)
			out << "|---->BUIT" << endl;
		else	
			h.escriuRec(out,0, 0);
		return out;
	}
	
	void insereix(const T& el);
	void esborra(const T& el);
	void esborraMinim();
	bool esBuit();

private:
	vector<T> m_data;
	int m_max;
	int m_actual;	//indica posicio ultima ocupada: inicialment -1

	void corregeix(int posAct);
	int cerca(const T& el);

	int getPare(int pos) const { return ((pos - 1) / 2); }
	int getFillEsq(int pos) const  { return ((2 * pos) + 1); }
	int getFillDret(int pos) const { return ((2 * pos) + 2); }
	void intercanvia(T& v1, T& v2) { T aux = v1; v1 = v2; v2 = aux;}
	
	std::ostream& escriuRec(std::ostream& out, int pos, int n) const;
	void descendeix(int pos);
};

template<class T>
Heap<T>::Heap(const Heap<T>& h)
{
	//constructor de copia
	m_data = h.m_data;
	m_actual = h.m_actual;
	m_max = h.m_max;
}

template<class T>
Heap<T>& Heap<T>::operator=(const Heap<T>& h)
{
	if (this != &h)
	{
		m_data = h.m_data;	
		m_max = h.m_max;
		m_actual = h.m_actual;
	}	
	return *this;
}

template<class T>
inline int Heap<T>::cerca(const T& el)
{
	int p = 0;
	for (; p <= m_actual; p++)
	{
		if (m_data[p] == el)
			return p;
	}

	/*
	while (p < m_actual)
	{
		if (m_data[p] == el)
			return p;
		else if (m_data[p] < el)
			p = getFillEsq(p);
		else
			p = getFillDret(p);
	}*/

	return -1;
}

template<class T>
void Heap<T>::insereix(const T& el)
{
	// Inserim element al final
	m_actual++;
	if (m_actual < m_max)
		m_data[m_actual] = el;
	else
	{
		m_data.push_back(el);
		m_max++;
	}
	corregeix(m_actual);
}


template<class T>
void Heap<T>::esborraMinim()
{
	if (m_actual >= 0)
	{
		// Posar element ultim a l'arrel, decrementar nombre elements i descendir l'arrel per mantenir propietat de heap
		intercanvia(m_data[0], m_data[m_actual]);
		m_actual--;
		descendeix(0);
	}
}

template<class T>
inline bool Heap<T>::esBuit()
{
	return (m_actual == -1);
}

template<class T>
inline void Heap<T>::corregeix(int posAct)
{
	// Si no es compleix la propietat del heap, intercanviem amb el pare per solucionar-ho
	while ((posAct != 0) && (m_data[posAct] < m_data[getPare(posAct)]))
	{
		intercanvia(m_data[posAct], m_data[getPare(posAct)]);
		posAct = getPare(posAct);
	}
}

template<class T>
void Heap<T>::esborra(const T& el)
{
	int index = cerca(el);

	if (index != -1) 
	{
		m_data[index] = T();
		corregeix(index);
		esborraMinim();
	}
}

template<class T>
void Heap<T>::descendeix(int posAct)
{
	int fEsq = getFillEsq(posAct);
	int fDret = getFillDret(posAct);
	int mesPetit = posAct;
	if ((fEsq <= m_actual) && (m_data[fEsq] < m_data[posAct]))
		mesPetit = fEsq;
	if ((fDret <= m_actual) && (m_data[fDret] < m_data[mesPetit]))
		mesPetit = fDret;
	if (mesPetit != posAct)
	{
		intercanvia(m_data[posAct], m_data[mesPetit]);
		descendeix(mesPetit);
	}
}

/////////////////////////////////////////////////////////////////////////////
// llegeix(nomFitxer):                                                        //
//                 Metode public que obre fitxer i llegeix Heap            //
//Lectura d'un fitxer a on tindrem                                         //
//nombre elements maxim admet Heap                                         //
//nombre elements que cont� el Heap                                        //
//Valors elements                                                          //
/////////////////////////////////////////////////////////////////////////////
template<class T>
void Heap<T>::llegeix(const string& nomFitxer)
{
	ifstream fitxerNodes;

	fitxerNodes.open(nomFitxer.c_str());
	if (fitxerNodes.is_open())
	{
		//Llegim maxim nombre de nodes i nombre nodes actual
		fitxerNodes >> m_max;
		fitxerNodes >> m_actual;
		m_data.resize(m_max, T());

		int i = 0;
		while ((!fitxerNodes.eof()) && (i <= m_actual))
		{
			fitxerNodes >> m_data[i];
			i++;
		}
		fitxerNodes.close();
	}
}

/////////////////////////////////////////////////////////////////////////////
// escriu():                                                                //
//         Metode public presenta Heap per pantalla                        //
// escriuRec(int pos, int n)                                                 //
//         Metode privat que escriu Heap per pantalla de forma recursiva   //
// |--arrel                                                                //
// |---->FillDret1                                                         //
// |------>FillDret2                                                       //
// |------>FillEsquerre2                                                   //
// |---->FillEsquerre1                                                     //
/////////////////////////////////////////////////////////////////////////////
template<class T>
std::ostream& Heap<T>::escriuRec(std::ostream& out, int pos, int n) const
{
	if (pos <= m_actual)
	{
		//Pintem arbre
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "|-->" << m_data[pos] << endl;
		if (((2*pos)+1) <= m_max)
		{
			//printem subarbre esquerre
			escriuRec(out, getFillEsq(pos), n + 1);
		}
		if ((2 * pos) < m_max)
		{//printem subarbre dret
			escriuRec(out, getFillDret(pos), n + 1);
		}
	}
	return out;
}
