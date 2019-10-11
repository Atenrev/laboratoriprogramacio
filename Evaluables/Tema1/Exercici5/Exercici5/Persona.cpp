#include "Persona.h"

ostream& operator<<(ostream &out, const Persona& p)
{
	out << "(" << p.m_nom << ", " << p.m_edat << ")";
	return out;
}

