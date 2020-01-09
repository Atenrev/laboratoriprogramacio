#pragma once
#include <stdlib.h>
#include <iostream>
#include <utility>
#include "TreeRB.hpp"
using namespace std;



template<class TClau, class TValor>
class PairMap
{
public:
	TClau first;
	TValor second;
	PairMap() { first = TClau(); second = TValor(); }
	PairMap(TClau primer, TValor segon) { first = primer; second = segon; }
	PairMap(const PairMap& p) { first = p.first; second = p.second; }
	bool operator<(PairMap<TClau, TValor> valor) const { return (first < valor.first); }
	bool operator==(PairMap<TClau, TValor> valor) const {	return (first == valor.first); }
	friend ostream& operator<<(ostream& out, PairMap<TClau, TValor> valor)
	{
		out << "<" << valor.first << ", " << valor.second << ">";
		return out;
	}
};



template<class TClau, class TValor>
class Map
{
public:
	Map();
	Map(const Map<TClau, TValor>& m);
	~Map();
	bool esBuit() const;
	TValor& operator[](const TClau& clau);
	void afegeix(const TClau& clau, const TValor& valor);
	friend ostream& operator<<(ostream& out, const Map<TClau, TValor>& m)
	{
		if (!m.esBuit())
			out << m.tree;
		else
			out << "";
		return out;
	}
private:
	TreeRB<PairMap<TClau, TValor>> tree;
};


template<class TClau, class TValor>
inline Map<TClau, TValor>::Map()
{

}

template<class TClau, class TValor>
inline Map<TClau, TValor>::Map(const Map<TClau, TValor>& m)
{
	TreeRB<PairMap<TClau, TValor>>* new_tree = new TreeRB<PairMap<TClau, TValor>>(m.tree);
	tree = *new_tree;
}

template<class TClau, class TValor>
inline Map<TClau, TValor>::~Map()
{

}

template<class TClau, class TValor>
inline bool Map<TClau, TValor>::esBuit() const
{
	return tree.isEmpty();
}

template<class TClau, class TValor>
inline TValor& Map<TClau, TValor>::operator[](const TClau& clau)
{
	if (!esBuit())
	{
		TreeRB<PairMap<TClau, TValor>>* found;

		if (tree.cerca(PairMap<TClau, TValor>(clau, TValor()), found))
		{
			return found->getData().second;
		}
	}
	return *(new TValor);
}

template<class TClau, class TValor>
inline void Map<TClau, TValor>::afegeix(const TClau& clau, const TValor& valor)
{
	PairMap<TClau, TValor> entry = PairMap<TClau, TValor>(clau, valor);
	tree.insert(entry);
}