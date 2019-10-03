#include "LliuramentsEstudiant.h"

bool LliuramentsEstudiant::afegeixTramesa(const string & fitxer, const string & data)
{
	bool succ = false;
	bool found = false;

	for (auto tr = m_trameses.begin(); tr != m_trameses.end(); ++tr)
	{
		if (tr->getData() == data)
		{
			found = true;
			break;
		}
	}

	if (!found) 
	{
		Tramesa novaTramesa(fitxer, data);
		m_trameses.push_front(novaTramesa);	
		succ = true;
	}
	
	return succ;
}

bool LliuramentsEstudiant::consultaTramesa(const string & data, string & fitxer)
{
	bool found = false;

	for (auto tr = m_trameses.begin(); tr != m_trameses.end(); ++tr)
	{
		if (tr->getData() == data)
		{
			fitxer = tr->getFitxer();
			found = true;
			break;
		}
	}

	return found;
}

bool LliuramentsEstudiant::eliminaTramesa(const string & data)
{
	bool succ = false;

	for (auto tr = m_trameses.begin(); tr != m_trameses.end(); ++tr)
	{
		if (tr->getData() == data)
		{
			m_trameses.remove(*tr);
			succ = true;
			break;
		}
	}

	return succ;
}
