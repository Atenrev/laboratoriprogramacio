#include <string>
using namespace std;
#pragma once

class Publicacio
{
public:
	Publicacio() { codi = ""; titol = ""; }
	~Publicacio() {}

	virtual bool esLlibre() { return false; }

	void setCodi(string& codi) { this->codi = codi; }
	void setTitol(string& titol) { this->titol = titol; }
	string getCodi() const { return codi; }
	string getTitol() const { return titol; }
	int getDiesPrestec() const { return dies_prestec; }
protected:
	string codi;
	string titol;
	int dies_prestec;
};

