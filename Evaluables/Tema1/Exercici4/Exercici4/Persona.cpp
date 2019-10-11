#include "Persona.h"

ostream& operator<<(ostream &out, const Persona& p)
{
	out << "(" << p.m_nom << ", " << p.m_edat << ")";
	return out;
}

bool Persona::operator==(const Persona & p) const
{
	return (m_nom == p.getNom() && m_edat == p.getEdat());
}
