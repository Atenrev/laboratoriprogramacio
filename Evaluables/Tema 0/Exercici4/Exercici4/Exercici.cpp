#include "Exercici.h"
#include <fstream>
using namespace std;

Exercici::Exercici(const Exercici & e)
{
	m_nEstudiants = e.m_nEstudiants;
	m_dataLimit = e.m_dataLimit;
	m_descripcio = e.m_descripcio;

	if (e.m_lliuraments != nullptr)
	{
		m_lliuraments = new LliuramentsEstudiant[m_nEstudiants];
		for (int i = 0; i < m_nEstudiants; i++)
			m_lliuraments[i] = e.m_lliuraments[i];
	}
	else
		m_lliuraments = nullptr;
}

Exercici::~Exercici()
{
	if (m_lliuraments != nullptr)
		delete[] m_lliuraments;
}

Exercici & Exercici::operator=(const Exercici & e)
{
	if (this != &e)
	{
		m_nEstudiants = e.m_nEstudiants;
		m_dataLimit = e.m_dataLimit;
		m_descripcio = e.m_descripcio;

		if (m_lliuraments != nullptr)
			delete[] m_lliuraments;
		if (e.m_lliuraments != nullptr)
		{
			m_lliuraments = new LliuramentsEstudiant[m_nEstudiants];
			for (int i = 0; i < m_nEstudiants; i++)
				m_lliuraments[i] = e.m_lliuraments[i];
		}
		else
			m_lliuraments = nullptr;
	}
	return *this;
}

void Exercici::inicialitzaEstudiants(const string & fitxerEstudiants)
{
	int idEstudiant;
	string line;
	ifstream fitxer;
	fitxer.open(fitxerEstudiants);

	if (fitxer.is_open())
	{
		if (getline(fitxer, line))
		{
			try 
			{
				m_nEstudiants = stoi(line);
				m_lliuraments = new LliuramentsEstudiant[m_nEstudiants];

				int i = 0;
				LliuramentsEstudiant* nouLE;
				while (getline(fitxer, line))
				{	
					nouLE = new LliuramentsEstudiant();
					nouLE->setNiu(line);
					m_lliuraments[i] = *nouLE;
					i++;
				}
			}
			catch (exception e) {}
		}
		fitxer.close();
	}

	
}

bool Exercici::afegeixTramesa(const string & niu, const string & fitxer, const string & data)
{
	bool succ = false;
	LliuramentsEstudiant* le = cercarLliuramentEstudiants(niu);

	if (le != nullptr)
	{
		succ = le->afegeixTramesa(fitxer, data);
	}

	return succ;
}

bool Exercici::consultaTramesa(const string & niu, const string & data, string & fitxer)
{
	bool found = false;
	LliuramentsEstudiant* le = cercarLliuramentEstudiants(niu);

	if (le != nullptr && le->consultaTramesa(data, fitxer)) 
		found = true;

	return found;
}

bool Exercici::eliminaTramesa(const string & niu, const string & data)
{
	bool succ = false;
	LliuramentsEstudiant* le = cercarLliuramentEstudiants(niu);

	if (le != nullptr)
		succ = le->eliminaTramesa(data);

	return succ;
}

LliuramentsEstudiant* Exercici::cercarLliuramentEstudiants(const string & niu)
{
	LliuramentsEstudiant* le = nullptr;
	LliuramentsEstudiant* it = nullptr;
	for (int i = 0; i < m_nEstudiants; i++)
	{
		it = &m_lliuraments[i];

		if (it->getNiu() == niu)
		{
			le = it;
			break;
		}
	}
	return le;
}
