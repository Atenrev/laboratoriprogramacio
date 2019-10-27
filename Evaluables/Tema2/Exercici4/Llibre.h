#pragma once
#include "Publicacio.h"
class Llibre :
	public Publicacio
{
public:
	Llibre() { autor = ""; copies = 0; dies_prestec = 0; }
	~Llibre() {}

	virtual bool esLlibre() { return true; }

	void setAutor(string& autor) { this->autor = autor; }
	void setCopies(int copies) { this->copies = copies; }
	void setDiesPrestec(int dies) { this->dies_prestec = dies; }
	string getAutor() const { return autor; }
	int getCopies() const { return copies; }
private:
	string autor;
	int copies;
};

