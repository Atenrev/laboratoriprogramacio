#include "Heap.h"

Heap::Heap(const Heap& h)
{//constructor de copia
	m_data = h.m_data;
	m_maxEls = h.m_maxEls;
	m_act = h.m_act;
	m_index = h.m_index;
}

void Heap::clear()
{
	m_data.clear();
	m_index.clear();
	m_maxEls=0;
	m_act=-1;
}

Heap& Heap::operator=(const Heap& h)
{
	if (this != &h)
	{
		m_data = h.m_data;
		m_maxEls = h.m_maxEls;
		m_act = h.m_act;
		m_index = h.m_index;
	}
	return *this;
}

bool Heap::operator==(const Heap& h) 
{
	bool iguals = true;
	if (m_act != h.m_act)
	{
		iguals = false;
	}
	else
	{

		int i = 0;
		while ((i <= m_act) && iguals)
		{
			if (!(m_data[i] == h.m_data[i]))
			{
				iguals = false;
				cout << "MDATA DIFERENT A POS: " << i << endl;
			}
			i++;
		}
	}
	return iguals;
}

std::ostream& operator<<(std::ostream& out, const Heap& h)
{
	if (h.m_act == -1) { out << "|---->BUIT" << endl; }
	else	h.printRec(out, 0, 0);
	return out;
}

void Heap::delElem(int pos1)
{
	int pos = m_index[pos1];
	if ((pos >= 0) && (pos <= m_act))
	{
		//Posar element ultim a pos i decrementar nombre elements

		//Modifiquem que ara element que estava a pos esta a 0
		m_index[m_data[pos].getPos().first] = 0;
		m_index[m_data[0].getPos().first] = -1;
				
		//Posar element ultim a pos i decrementar nombre elements
		intercanvia(0, pos);
		m_act--;
		descendir(pos);
	}
}

void Heap::modifElem(const ElemHeap& novaData)
{
	int pos = m_index[novaData.getPos().first];
	if ((pos >= 0) && (pos <= m_act))
	{
		//Modifiquem element
		if (m_data[pos] > novaData)
		{
			m_data[pos] = novaData;
			descendir(pos);
		}
		else
			if (m_data[pos] < novaData)
			{
				m_data[pos] = novaData;
				ascendir(pos);
			}
			else
			{
				m_data[pos] = novaData;
			}
	}
}

void Heap::insert(const ElemHeap& el)
{
	if ((m_act + 1) < m_maxEls) //Si hi ha espai
	{//inserim element al final
		m_act++;
		m_data[m_act] = el;
		//Indiquem que element el esta posicio m_act
		m_index[el.getPos().first] = m_act;

		int posAct = m_act;
		// Fix the max heap property if it is violated 
		while (posAct != 0 && m_data[posAct] >= m_data[pare(posAct)])
		{
			//Indiquem que element que estava a posAct estara a pare(posAct) i viceversa
			int indexAux = m_index[m_data[posAct].getPos().first];
			m_index[m_data[posAct].getPos().first] = m_index[m_data[pare(posAct)].getPos().first];
			m_index[m_data[pare(posAct)].getPos().first] = indexAux;
			
			intercanvia(posAct, pare(posAct));
			
			posAct = pare(posAct);
		}
	}
}

void Heap::delMax()
{
	if (m_act >= 0)
	{
		//Modifiquem que ara element que estava a m_act estara a 0
		m_index[m_data[m_act].getPos().first] = 0;
		m_index[m_data[0].getPos().first] = -1;
		//Posar element ultim a l'arrel i decrementar nombre elements
		intercanvia(0, m_act);
		
		m_act--;
		descendir(0);
	}
}

void Heap::descendir(int posAct)
{
	int fEsq = fillEsq(posAct);
	int fDret = fillDret(posAct);
	int mesGran = posAct;
	if (fEsq <= m_act && m_data[fEsq] > m_data[posAct])
		mesGran = fEsq;
	if (fDret <= m_act && m_data[fDret] > m_data[mesGran])
		mesGran = fDret;
	if (mesGran != posAct)
	{
		//Modifiquem que ara element que estava a m_act estara a 0
		int indAux = m_index[m_data[posAct].getPos().first];
		m_index[m_data[posAct].getPos().first] = m_index[m_data[mesGran].getPos().first];
		m_index[m_data[mesGran].getPos().first] = indAux;

		intercanvia(posAct, mesGran);
		descendir(mesGran);
	}
}

void Heap::ascendir(int posAct)
{
	int fPare = pare(posAct);
	if (fPare >= 0 && m_data[fPare] < m_data[posAct])
	{
		//Indiquem que element que estava a posAct estara a pare(posAct) i viceversa
		int indexAux = m_index[m_data[posAct].getPos().first];
		m_index[m_data[posAct].getPos().first] = m_index[m_data[fPare].getPos().first];
		m_index[m_data[fPare].getPos().first] = indexAux;

		intercanvia(posAct, fPare);
		ascendir(fPare);
	}
}

/////////////////////////////////////////////////////////////////////////////
// print():                                                                //
//         Metode public presenta Heap per pantalla                        //
// readRec(int pos, int n)                                                 //
//         Metode privat que escriu HEap per pantalla de forma recursiva   //
// |--arrel                                                                //
// |---->FillDret1                                                         //
// |------>FillDret2                                                       //
// |------>FillEsquerre2                                                   //
// |---->FillEsquerre1                                                     //
/////////////////////////////////////////////////////////////////////////////

std::ostream& Heap::printRec(std::ostream& out, int pos, int n) const
{
	if (pos <= m_act)
	{//Pintem arbre
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "|-->" << m_data[pos] << endl;
		if (((2 * pos) + 1) <= m_maxEls)
		{//printem subarbre esquerre
			printRec(out, fillEsq(pos), n + 1);
		}
		if ((2 * pos) < m_maxEls)
		{//printem subarbre dret
			printRec(out, fillDret(pos), n + 1);
		}
	}
	return out;
}
