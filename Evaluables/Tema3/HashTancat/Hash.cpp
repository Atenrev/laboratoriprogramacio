#include "Hash.h"
#include <math.h>

Hash::Hash(int numIni, float factorCarrega, const string& descripcioDefecte)
{
	m_maxElements = numIni;
	m_factorCarrega = factorCarrega;
	m_descripcioDefecte=descripcioDefecte;
	
	m_diccionari.resize(m_maxElements,pair<string,string>("",""));
	int init =LLIURE;
	m_estat.resize(m_maxElements,init);
	
	m_numOcupats = 0;
}

Hash::~Hash()
{
	
}

int Hash::codi(string s) const
{
	unsigned long valor = 0;
	for (int i = 0; i < s.size(); i++)
	{
		valor+= (s[i]*pow(2,i));
		valor = valor%m_maxElements;
	}	
	return valor;
}

int Hash::codi2(int index, int vegades) const
{
	return (int)(index + pow(vegades,2)) % m_maxElements;
}


int Hash::cerca(const string& clau) const
{//Cerquem posicio amb collisions
	bool trobat = false;
	int indexInicial = codi(clau);
	int index = indexInicial;
	int vegades = 0;
	while ((m_estat[index] != LLIURE) && (!trobat))
	{
		if ((m_estat[index] == OCUPAT) && (m_diccionari[index].first == clau))
			trobat = true;
		else
		{
			index = codi2(indexInicial, vegades);
			vegades++;
		}
	}
	return index;
}


void Hash::resize()
{
	//Fem copia de seguretat vectors Taula Hash
	vector<pair<string, string>> diccAux;
	vector<int> estatAux;
	int maxelsAux = m_maxElements;
	
	estatAux = m_estat;
	diccAux = m_diccionari;

	//Creem nova Taula Hash
	m_maxElements *= 2;
	m_diccionari.clear();
	m_diccionari.resize(m_maxElements,pair<string,string>("",""));
	m_estat.clear();
	int init =LLIURE;
	m_estat.resize(m_maxElements,init);

	m_numOcupats = 0;
	for (int i = 0; i < maxelsAux; i++)
	{
		if (estatAux[i] == OCUPAT)
		{
			insertIntern(diccAux[i].first, diccAux[i].second);
		}		
	}
}

void Hash::insertIntern(const string& clau, const string& descripcio)
{
	int indexInicial = codi(clau);
	int index = indexInicial;
	int vegades = 1;

	while ((m_estat[index] == OCUPAT) && (vegades <m_maxElements))
	{
		index = codi2(indexInicial, vegades);
		vegades++;
	}
	
	if (vegades >= m_maxElements)throw "ERROR AL TROBAR POSICIO INSERCIO A HASH";

	m_diccionari[index].first = clau;
	m_diccionari[index].second = descripcio;
	m_estat[index] = OCUPAT;
	m_numOcupats++;

	if ((m_numOcupats /(float)(m_diccionari.size())) >= m_factorCarrega)
	{
		//RESIZE this taked time
		resize();
	}		
}

bool Hash::find(const string& clau, string& definicio) const
{
	bool trobat = false;

	int index = cerca(clau);
	
	if ((m_estat[index] == OCUPAT) && (m_diccionari[index].first == clau))
	{
		definicio = m_diccionari[index].second;
		trobat = true;
	}
	else { definicio = ""; }
	return trobat;	
}

bool Hash::esborra(const string& clau)
{
	int index = codi(clau);
	int vegades = 0;
	bool trobat = false;
	while ((m_estat[index] != LLIURE) && (m_diccionari[index].first != clau) && (vegades <m_maxElements))
	{
		index = codi2(index,vegades);
		vegades++;
	}

	if (m_diccionari[index].first == clau)
	{//Trobat l'esborrem
		m_diccionari[index].second="";
		m_diccionari[index].first= "";
		m_estat[index] = ESBORRAT;
		m_numOcupats--;
		trobat = true;		
	}
	
	return trobat;
}


void Hash::insert(const string& clau, const string& descripcio)
{
	int index = cerca(clau);
	
	if ((m_estat[index] == OCUPAT) && (m_diccionari[index].first == clau))
	{//Element trobat es una modificacio de la seva descripcio
		// m_diccionari[index].second = descripcio;
	}
	else
	{   //Inserim un nou element
		insertIntern(clau, descripcio);
	}	
}

string& Hash::operator[](const string& clau)
{
	int index = cerca(clau);

	if ((m_estat[index] == OCUPAT) && (m_diccionari[index].first == clau))
	{
		//Element trobat
		return m_diccionari[index].second;
	}
	else
	{//Element no trobat, l'inserim
		// insertIntern(clau, m_descripcioDefecte);
		return m_descripcioDefecte;
	}
}

pair<string,string>& Hash::operator[](const int& index)
{
	return m_diccionari[index];	
}

ostream& operator<<(ostream &out, const Hash& h)
{
	for (int i = 0; i < h.m_diccionari.size(); i++)
	{
		if (h.m_estat[i] == h.OCUPAT)
		{
			out<< "POS: " <<i <<"  CLAU: " << h.m_diccionari[i].first <<"  VALOR: " << h.m_diccionari[i].second <<endl;
		}		
	}
	return out;
}
