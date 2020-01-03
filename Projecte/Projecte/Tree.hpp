#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include<string>

using namespace std;

template <class T>
class Tree {
public:
	Tree();
	Tree(const T& data);
	Tree(const Tree<T>& t);
	Tree(string nomFitxer);
	~Tree();
	bool isLeave() const { return ((m_left == NULL) && (m_right == NULL)); }
	bool isEmpty() const { return (m_data == NULL);}
	Tree<T>* getRight(){return m_right;}
	Tree<T>* getLeft() { return m_left; }
	void setRight(Tree<T>* tR);
	void setLeft(Tree<T>* tL);
	T& getData() { return (*m_data); }
	
	friend std::ostream& operator<<(std::ostream& out, const Tree<T>& t)
	{
		t.coutArbreRec(0, out);
		return out;
	}
private:
	Tree<T>* m_left;
	Tree<T>* m_right;
	Tree<T>* m_father;
	T* m_data;
	
	void TreeRec(ifstream& fitxerNodes, int h, Tree<T>* father);
	std::ostream& coutArbreRec(int n, std::ostream& out) const;
};

template<class T>
Tree<T>::Tree()
{//Inicialitzem tota l'estructura
	m_left = NULL;
	m_right = NULL;
	m_father = NULL;
	m_data = NULL;
}
template<class T>
Tree<T>::Tree(const T& data)
{
	m_left = NULL;
	m_right = NULL;
	m_father = NULL;
	m_data = new(T);
	(*m_data) = data;
}

template<class T>
Tree<T>::Tree(const Tree<T>& t)
{
	if (t.m_left != NULL)
	{
		m_left = new(Tree<T>);
		m_left = t.m_left;
	}
	else
	{
		m_left = NULL;
	}

	if (t.m_right != NULL)
	{
		m_right = new(Tree<T>);
		m_right = t.m_right;
	}
	else
	{
		m_right = NULL;
	}
	//m_father: here m_father must be NULL
	//we are creating a tree, if it has to be connected with another one you will use setRight o r left.
	m_father = NULL;

	if (t.m_data != NULL)
	{
		m_data = new(T);
		m_data = t.m_data;
	}
	else
	{
		m_data = NULL;
	}
}

template<class T>
void Tree<T>::setLeft(Tree<T>* tL)
{
	m_left = tL;
	if (m_left != NULL)
	{
		//Fem que this sigui el pare de left
		m_left->m_father = this;
	}
}

template<class T>
void Tree<T>::setRight(Tree<T>* tR)
{
	m_right = tR;
	if (m_right != NULL)
	{		
		//Fem que this sigui el pare de right
		m_right->m_father = this;		
	}	
}

/////////////////////////////////////////////////////////////////////////////
// Tree(nomFitxer):                                                        //
//                 constructor que obre fitxer i crida a metode privat     //
// TreeRec(ifstream& fitxerNodes, int h, Tree<T>* father)              //
//            metode privat que llegeix arbre de forma recursiva           //
//Lectura d'un fitxer a on tindrem                                         //
//alcada                                                                   //
//estat: 0 o 1 segons sigui buit o amb informacio al costat dada           //
//Esta en preordre Preordre(FillEsq) Arrel Preordre(FillDret)                //
/////////////////////////////////////////////////////////////////////////////
template<class T>
Tree<T>::Tree(string nomFitxer)
{
	ifstream fitxerNodes;

	fitxerNodes.open(nomFitxer.c_str());
	if (fitxerNodes.is_open())
	{
		//Llegim al�ada arbre binari
		int h;
		fitxerNodes >> h;
		if (!fitxerNodes.eof())
		{
			int estat;
			fitxerNodes >> estat;
			if (estat == 1)
			{
				if (fitxerNodes.is_open())	TreeRec(fitxerNodes, h, NULL);
			}
		}
		fitxerNodes.close();
	}
}

template<class T>
void Tree<T>::TreeRec(ifstream& fitxerNodes, int h, Tree<T>* father)
{
	m_father = father;
	m_data = new(T);
	fitxerNodes >> (*m_data);
	if (h > 0)
	{
		int estat;
		if (!fitxerNodes.eof())
		{			
			fitxerNodes >> estat;
			if (!fitxerNodes.eof())
			{
				if (estat == 1)
				{
					m_left = new(Tree<T>);
					m_left->TreeRec(fitxerNodes, h - 1, this);
				}
			}
		}
		if (!fitxerNodes.eof())
		{
			fitxerNodes >> estat;
			if (!fitxerNodes.eof())
			{
				if (estat == 1)
				{
					m_right = new(Tree<T>);
					m_right->TreeRec(fitxerNodes, h - 1, this);
				}
			}
		}
	}
}


template<class T>
Tree<T>::~Tree()
{
	if (m_right != NULL)
	{
		delete m_right;
	}

	if (m_left != NULL)
	{
		delete m_left;
	}

	if (m_data != NULL)
	{
		delete m_data;
	}

	m_father = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// coutArbreRec():                                                         //
//         Metode privat cridat per operator<<                             //
//                       que escriu arbre per pantalla de forma recursiva  //
// |--arrel                                                                //
// |---->FillDret1                                                         //
// |------>FillDret2                                                       //
// |------>FillEsquerre2                                                   //
// |---->FillEsquerre1                                                     //
//alcada                                                                   //
//estat: 0 o 1 segons sigui buit o amb informacio al costat dada           //
//Esta en inordre Inordre(FillEsq) Arrel Inordre(FillDret)                 //
/////////////////////////////////////////////////////////////////////////////
template<class T>
std::ostream& Tree<T>::coutArbreRec(int n, std::ostream& out) const
{
	if (isEmpty())
	{//Pintem arbre buit
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "-->BUIT" << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "|-->" << (*m_data) << endl;
		if (!isLeave())
		{
			if (m_left != NULL)
			{
				m_left->coutArbreRec(n + 1,out);
			}
			else
			{
				for (int i = 0; i < n + 1; i++)
				{
					out << "|--";
				}
				out << "|-->BUIT" << endl;
			}
			if (m_right != NULL)
			{
				m_right->coutArbreRec(n + 1,out);
			}
			else
			{
				for (int i = 0; i < n + 1; i++)
				{
					out << "|--";
				}
				out << "|-->BUIT" << endl;
			}
		}
	}
	return out;
}
