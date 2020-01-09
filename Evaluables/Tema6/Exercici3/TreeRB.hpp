#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;



template <class T>
class TreeRB 
{
public:

	TreeRB() { m_left = NULL; m_right = NULL; m_father = NULL; m_data = NULL;  m_color = RED; };
	TreeRB(string nomFitxer);
	TreeRB(const TreeRB<T>& t);
	~TreeRB();

	void setVal(const T& val) { if (m_data==NULL) m_data = new T(); (*m_data) = val;};
	bool isLeave() const { return ((m_left == NULL) && (m_right == NULL)); }
	bool isEmpty() const { return (m_data == NULL); }
	TreeRB<T>* getRight(){ return m_right; }
	TreeRB<T>* getLeft() { return m_left; }
	T& getData() { return (*m_data); }
	bool cerca(const T& val, TreeRB<T>*& valTrobat);
	TreeRB<T>* oncle();
	bool esFillDret();
	bool esFillEsq();
	friend std::ostream& operator<<(std::ostream& out, const TreeRB<T>& t)
	{
		t.coutArbreRec(0, out);
		return out;
	};
	void insert(T& val);

private:
	enum COLOR { RED, BLACK };
	TreeRB<T>* m_left;
	TreeRB<T>* m_right;
	TreeRB<T>* m_father;
	T* m_data;
	COLOR m_color;

	void arreglaREDRED(TreeRB<T>* nouNode);
	void TreeRBRec(ifstream& fitxerNodes, int h, TreeRB<T>* father);
	std::ostream& coutArbreRec(int n, std::ostream& out) const;
	void rota(TreeRB<T>* nouNode, TreeRB<T>* pPare, TreeRB<T>* pAvi);
	void swapColor(TreeRB<T>* pNod1, TreeRB<T>* pNod2);
	void rotaEsq(TreeRB<T>* pNode);
	void rotaDreta(TreeRB<T>* pNode);
	void canviaPunters(TreeRB<T>* pPare, bool esFillDret, TreeRB<T>* pFillEsq, TreeRB<T>* pFillDret, T* pDades, COLOR c);
};


template<class T>
void TreeRB<T>::canviaPunters(TreeRB<T>* pPare, bool esFillDret, TreeRB<T>* pFillEsq, TreeRB<T>* pFillDret,T* pDades,COLOR c)
{
	m_left = pFillEsq;
	if (m_left != NULL)
		m_left->m_father = this;
	m_right = pFillDret;
	if (m_right!= NULL)
		m_right->m_father = this;
	
	m_father = pPare;
	if (m_father != NULL)
	{
		if (esFillDret)
			m_father->m_right = this;
		else
			m_father->m_left = this;
	}
	m_color = c;
	m_data = pDades;
}

template<class T>
TreeRB<T>::TreeRB(const TreeRB<T>& t)
{
	m_color = t.m_color;

	if (t.m_left != NULL)
	{
		m_left = new TreeRB<T>(*(t.m_left));
		m_left->m_father = this;
	}
	else
		m_left = NULL;

	if (t.m_right != NULL)
	{
		m_right = new TreeRB<T>(*(t.m_right));
		m_right->m_father = this;
	}
	else
		m_right = NULL;
	
	//m_father: here m_father must be NULL
	//we are creating a TreeRB, if it has to be connected with another one you will use setRight o r left.
	m_father = NULL;

	if (t.m_data != NULL)
		m_data = new T(*t.m_data);
	else
		m_data = NULL;
}

template<class T>
bool TreeRB<T>::esFillDret()
{
	if (m_father != NULL)
		return this == m_father->m_right;
	else
		return false;
}

template<class T>
bool TreeRB<T>::esFillEsq()
{
	if (m_father != NULL)
		return this == m_father->m_left;
	else
		return false;
}

template<class T>
TreeRB<T>* TreeRB<T>::oncle()
{
	if (m_father == NULL)
	{
		return NULL;
	}
	else
	{
		if (m_father->m_father == NULL)
			return NULL;
		else
		{
			if (m_father->esFillEsq())
			{
				//oncle es fill dret
				return m_father->m_father->m_right;
			}
			else
			{
				//oncle es fill esquerre
				return m_father->m_father->m_left;
			}
		}
	}
}

template<class T>
void TreeRB<T>::swapColor(TreeRB<T>* pNod1, TreeRB<T>* pNod2)
{
	COLOR c = pNod1->m_color;
	pNod1->m_color = pNod2->m_color;
	pNod2->m_color = c;
}


template<class T>
void TreeRB<T>::rotaEsq(TreeRB<T>* pNodAct)
{
	//El pNode es avi que pasara a ser fill esquerre del seu filldret
	//El fill dret passara a ser el pare
	//El fill esquerre del fill dret passara a ser el fill dret de l'avi (pNode)

	//Com avi pot ser l'arrel no movem node de lloc
	//Guardem apuntador a Node de Fill Dret
	TreeRB<T>* pFD;
	pFD = pNodAct->m_right;

	TreeRB<T>* pPareNodAct, *pPareFD;
	bool esFillDretNodAct, esFillDretFD;
	TreeRB<T>* pFillDretNodAct, *pFillDretFD;
	TreeRB<T>* pFillEsqNodAct, *pFillEsqFD;
	T* pDadesNodAct, *pDadesFD;
	COLOR cNodAct, cFD;

	//El nou NodAct sera el fill dret del nodAct actual
	//El seu pare sera el mateix del pNodAct actual
	pPareNodAct = pNodAct->m_father;
	esFillDretNodAct = pNodAct->esFillDret();
	//El seu fill dret sera l'actual fill dret de PFD
	pFillDretNodAct = pFD->m_right;
	//El seu fill esquerre sera l'actual pNodActual
	pFillEsqNodAct = pNodAct;
	//Les dades seran les que hi ha ara a PFD
	pDadesNodAct = pFD->m_data;
	cNodAct = pFD->m_color;

	//El nou PFD sera el pNodAct actual i serà el fill esquerre del nou nodAct
	//El seu pare sera el nou pNodAct
	pPareFD = pNodAct;
	esFillDretFD = false;
	//El seu fill dret sera el fill esquerre de PFD actual
	pFillDretFD = pFD->m_left;
	//El seu fill esquerre es el fill esquerre que te ara a pNodAct actual
	pFillEsqFD = pNodAct->m_left;
	//Les dades seran les que hi ha ara a PNodAct
	pDadesFD = pNodAct->m_data;
	cFD = pNodAct->m_color;

	pNodAct->canviaPunters(pPareNodAct, esFillDretNodAct, pFillEsqNodAct, pFillDretNodAct, pDadesNodAct, cNodAct);
	pFD->canviaPunters(pPareFD, esFillDretFD, pFillEsqFD, pFillDretFD, pDadesFD, cFD);
}

template<class T>
void TreeRB<T>::rotaDreta(TreeRB<T>* pNodAct)
{
	//El pNodAct es avi o pare que pasara a ser fill dret del seu fillesquerre
	//El fill esquerre de pNodAct passara a ser pare
	//El fill dret del fill esquerre de pNodAct (si no es NULL) passara a ser el fill esquerre de l'avi (pNodAct)

	//Com avi pot ser l'arrel no movem node de lloc
	//intercanviem node pNodAct amb pFE i modifiquem els seus fills i pares de la seguent manera

	//Guardem apuntador a Node de Fill Esquerre
	TreeRB<T>* pFE;
	pFE = pNodAct->m_left;

	TreeRB<T>* pPareNodAct,*pPareFE;
	bool esFillDretNodAct, esFillDretFE;
	TreeRB<T>* pFillDretNodAct, *pFillDretFE;
	TreeRB<T>* pFillEsqNodAct, *pFillEsqFE;
	T* pDadesNodAct, *pDadesFE;
	COLOR cNodAct, cFE;

	//El nou NodAct sera el fill esquerre del nodAct actual
	//El seu pare sera el mateix del pNodAct actual
	pPareNodAct = pNodAct->m_father;
	esFillDretNodAct= pNodAct->esFillDret();
	//El seu fill dret sera l'actual PNodAct que estara a PFE
	pFillDretNodAct = pFE;
	//El seu fill esquerre es el que te ara a PFE
	pFillEsqNodAct = pFE->m_left;
	//Les dades seran les que hi ha ara a PFE
	pDadesNodAct = pFE->m_data;
	cNodAct = pFE->m_color;

	//El nou PFE sera el pNodAct actual i serà el fill dret del nou nodAct
	//El seu pare sera el nou pNodAct
	pPareFE = pNodAct;
	esFillDretFE = true;
	//El seu fill dret sera el que tenia a PNodAct
	pFillDretFE = pNodAct->m_right;
	//El seu fill esquerre es el fill dret del que te ara a PFE
	pFillEsqFE = pFE->m_right;
	//Les dades seran les que hi ha ara a PNodAct
	pDadesFE = pNodAct->m_data;
	cFE = pNodAct->m_color;

	pNodAct->canviaPunters(pPareNodAct, esFillDretNodAct, pFillEsqNodAct, pFillDretNodAct, pDadesNodAct, cNodAct);
	pFE->canviaPunters(pPareFE, esFillDretFE,pFillEsqFE, pFillDretFE, pDadesFE, cFE);
}

template<class T>
void TreeRB<T>::rota(TreeRB<T>* nouNode, TreeRB<T>* pPare, TreeRB<T>* pAvi)
{
	if (pPare->esFillEsq())
	{
		if (nouNode->esFillEsq())
		{//Esquerre-esquerre
			swapColor(pPare, pAvi);
		}
		else
		{//Esquerre-dret
			swapColor(nouNode, pAvi);
			rotaEsq(pPare);

		}
		//Per esquerre-esquerre i esquerre-dret
		rotaDreta(pAvi);
	}
	else
	{
		if (nouNode->esFillEsq())
		{//Dret-esquerre
			swapColor(nouNode, pAvi);
			rotaDreta(pPare);
		}
		else
		{//dreta-dreta
			swapColor(pPare, pAvi);
		}
		//dret-dret i dret-esquerre
		rotaEsq(pAvi);
	}
}

template<class T>
void TreeRB<T>::arreglaREDRED(TreeRB<T>* nouNode)
{
	if (nouNode->m_father == NULL)
	{
		//Es arrel
		nouNode->m_color = BLACK;
	}
	else
	{
		//Mirem pare, avi i oncle
		TreeRB<T>* pPare = nouNode->m_father;
		TreeRB<T>* pAvi = nouNode->m_father->m_father;
		TreeRB<T>* pOncle = nouNode->oncle();
		if (pPare->m_color != BLACK)
		{
			//Si el pare es BLACK ja hem acabat
			if (pOncle!=NULL)
				if (pOncle->m_color == RED)
				{
					pPare->m_color = BLACK;
					pOncle->m_color = BLACK;
					pAvi->m_color = RED;
					arreglaREDRED(pAvi);
				}
				else
				{
					rota(nouNode,pPare,pAvi);
				}
			else
			{
				rota(nouNode, pPare, pAvi);
			}
		}
	}
}

template<class T>
void TreeRB<T>::insert(T& val)
{
	if (m_data == NULL)
	{
		//Arbre buit
		m_data = new T;
		(*m_data) = val;
		m_color = BLACK;
	}
	else
	{
		TreeRB<T>* ptAux=nullptr;
		bool trobat = cerca(val, ptAux);
		if (!trobat)
		{
			//Si trobem valor no fem res; si no el trobem
			//Creem un node RED amb valor val fill de ptAux
			TreeRB<T>* nouNode = new TreeRB<T>;
			nouNode->m_data = new T;
			(*nouNode->m_data) = val;
			nouNode->m_father = ptAux;

			if (val < (*ptAux->m_data))
			{
				//El nou valor sera fillEsq de ptAux
				ptAux->m_left= nouNode;
			}
			else
			{
				//El nou valor sera fillDret de ptAux
				ptAux->m_right= nouNode;
			}

			arreglaREDRED(nouNode);
		}
		else 
		{
			*ptAux->m_data = val;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// TreeRB(nomFitxer):                                                        //
//                 constructor que obre fitxer i crida a metode privat     //
// TreeRBRec(ifstream& fitxerNodes, int h, TreeRB<T>* father)              //
//            metode privat que llegeix arbre de forma recursiva           //
//Lectura d'un fitxer a on tindrem                                         //
//alcada                                                                   //
//estat: 0 o 1 segons sigui buit o amb informacio al costat dada           //
//Esta en preordre Preordre(FillEsq) Arrel Preordre(FillDret)                //
/////////////////////////////////////////////////////////////////////////////
template<class T>
TreeRB<T>::TreeRB(string nomFitxer)
{
	ifstream fitxerNodes;

	fitxerNodes.open(nomFitxer.c_str());
	if (fitxerNodes.is_open())
	{
		//Llegim alçada arbre binari
		int h;
		fitxerNodes >> h;
		if (!fitxerNodes.eof())
		{
			int estat;
			fitxerNodes >> estat;
			if (estat == 1)
			{
				if (fitxerNodes.is_open())	TreeRBRec(fitxerNodes, h, NULL);
			}
		}
		fitxerNodes.close();
	}
}

template<class T>
void TreeRB<T>::TreeRBRec(ifstream& fitxerNodes, int h, TreeRB<T>* father)
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
					m_left = new(TreeRB<T>);
					m_left->TreeRBRec(fitxerNodes, h - 1, this);
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
					m_right = new(TreeRB<T>);
					m_right->TreeRBRec(fitxerNodes, h - 1, this);
				}
			}
		}
	}
}


template<class T>
TreeRB<T>::~TreeRB()
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

//Suposem l'arbre ordenat amb valors menors a arrel a esquerra i valors majors a dreta
template<class T>
bool TreeRB<T>::cerca(const T& val, TreeRB<T>*& valTrobat)
{
	bool trobat = false;
	if (m_data != NULL)
	{
		if (val == (*m_data))
		{
			trobat = true;
			valTrobat = this;
		}
		else
			if (val < (*m_data))
			{
				if (m_left != NULL)
				{
					trobat = m_left->cerca(val, valTrobat);
				}
				else
					valTrobat = this;
			}
			else
			{
				if (m_right != NULL)
				{
					trobat = (m_right->cerca(val, valTrobat));
				}
				else
					valTrobat = this;
			}		
	}
	return trobat;
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
std::ostream& TreeRB<T>::coutArbreRec(int n, std::ostream& out) const
{
	if (isEmpty())
	{//Pintem arbre buit
		out << "Comment :=>> ";
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "-->BUIT" << endl;
	}
	else
	{
		out << "Comment :=>> ";
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "|-->";
		if (m_color == RED)
			out << "RED,";
		else
			out << "BLACK,"; 
		out << (*m_data) << endl;
		if (!isLeave())
		{
			if (m_left != NULL)
			{
				m_left->coutArbreRec(n + 1,out);
			}
			else
			{
				out << "Comment :=>> ";
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
				out << "Comment :=>> ";
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