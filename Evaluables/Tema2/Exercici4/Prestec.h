#include <string>
#include "Data.h"
using namespace std;
#pragma once
class Prestec
{
public:
	Prestec(string idUsuari, string codi, const Data& dataPrestec, const Data& dataRetorn, int nExemplar)
	{
		usuari = idUsuari;
		codi_publicacio = codi;
		this->data_prestec = new Data(dataPrestec);
		this->data_devolucio = new Data(dataRetorn);
		exemplar = nExemplar;
	}
	~Prestec() { delete data_prestec; delete data_devolucio; }

	string getUsuari() const { return usuari; }
	string getCodi() const { return codi_publicacio; }
	int getExemplar() const { return exemplar; }
	Data& getDataRetorn();
private:
	string usuari, codi_publicacio;
	int exemplar;
	Data* data_prestec, *data_devolucio;
};

inline Data& Prestec::getDataRetorn() 
{ 
	return *data_devolucio;
}