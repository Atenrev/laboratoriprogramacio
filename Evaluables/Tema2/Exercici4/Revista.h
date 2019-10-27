#pragma once
#include "Publicacio.h"
#include <vector>
class Revista :
	public Publicacio
{
public:
	Revista() { 
		periodicitat = "";
		dies_prestec = 30;
	}
	~Revista() {}

	void setPeriodicitat(string periodicitat) { this->periodicitat = periodicitat; }
	string getPeriodicitat() const { return periodicitat; }
	int getNombreExemplars() const { return exemplars.size(); }
	void addExemplar(int exemplar) { exemplars.push_back(exemplar); }
	bool trobarExemplar(int exemplar) {
		for (auto it = exemplars.begin(); it != exemplars.end(); it++) 
			if ((*it) == exemplar) return true;
	}
private:
	string periodicitat;
	list<int> exemplars;
};
