#pragma once
#include "Data.h"
#include <fstream>
#include <string>
#include <sstream>
#include <list>

#include "Publicacio.h"
#include "Llibre.h"
#include "Revista.h"
#include "Prestec.h"
using namespace std;

class Biblioteca
{
public:
	Biblioteca() {}
	~Biblioteca() {}

	void llegirPublicacions(const string& nomFitxer);
	bool prestar(const string& idUsuari, const string& codi, const Data& dataPrestec, Data& dataRetorn, int nExemplar = 0);
	bool retornar(const string& idUsuari, const string& codi, const Data& data, bool &dataCorrecta, int nExmplar = 0);
private:
	list<Publicacio*> publicacions;
	list<Prestec> prestecs;
};

