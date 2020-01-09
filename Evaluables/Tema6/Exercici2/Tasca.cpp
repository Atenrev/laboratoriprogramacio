#include "Tasca.h"

bool Tasca::operator<(const Tasca& tasca)
{
	bool menor = false;
	if (m_prioritat < tasca.m_prioritat)
		menor = true;
	else
		if ((m_prioritat == tasca.m_prioritat) && (m_data < tasca.m_data))
			menor = true;
	return menor;
}

bool Tasca::operator==(const Tasca& tasca)
{
	return (m_codi == tasca.m_codi);
}