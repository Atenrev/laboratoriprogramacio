#include "Map.h"

template<class TClau, class TValor>
std::ostream& operator<<(std::ostream& out, const Map<TClau, TValor>& m)
{
	if (!m.esBuit())
		out << m.tree;
	else
		out << "";
}
