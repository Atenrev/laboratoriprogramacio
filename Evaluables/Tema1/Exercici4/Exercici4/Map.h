#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

template<class TClau, class TValor>
class Map
{
public:
	Map();
	Map(const Map& copy);
	~Map();

	int longitud() const { return data->size(); }
	bool esBuit() const { return data->empty(); }
	TValor & operator[](const TClau& clau);
	const TValor & operator[](const TClau& clau) const;
	TClau & operator[](const int& pos);
	const TClau & operator[](const int& pos) const;
	void afegeix(const TClau& clau, const TValor& valor);

	Map<TClau, TValor>& operator=(const Map<TClau, TValor>& m);
private:
	vector<pair<TClau, TValor>> * data;
};

template<class TClau, class TValor>
inline Map<TClau, TValor>::Map()
{
	data = new vector<pair<TClau, TValor>>;
}

template<class TClau, class TValor>
inline Map<TClau, TValor>::Map(const Map & copy)
{
	data = new vector<pair<TClau, TValor>>;
	for (auto i = 0; i < copy.longitud(); i++)
	{
		data->push_back(make_pair(copy[i], copy[copy[i]]));
	}
}

template<class TClau, class TValor>
inline Map<TClau, TValor>::~Map()
{
	delete data;
}

template<class TClau, class TValor>
inline TValor & Map<TClau, TValor>::operator[](const TClau & clau)
{
	for (auto it = data->begin(); it != data->end(); it++)
	{
		if (it->first == clau)
			return it->second;
	}
	return *(new TValor);
}

template<class TClau, class TValor>
inline const TValor & Map<TClau, TValor>::operator[](const TClau & clau) const
{
	for (auto it = data->begin(); it != data->end(); it++)
	{
		if (it->first == clau)
			return it->second;
	}
	return *(new TValor);
}

template<class TClau, class TValor>
inline TClau & Map<TClau, TValor>::operator[](const int & pos)
{
	if (pos >= 0 && pos < data->size())
		return data->at(pos).first;
	else
		return *(new TClau);
}

template<class TClau, class TValor>
inline const TClau & Map<TClau, TValor>::operator[](const int & pos) const
{
	if (pos >= 0 && pos < data->size())
		return data->at(pos).first;
	else 
		return *(new TClau);
}

template<class TClau, class TValor>
inline void Map<TClau, TValor>::afegeix(const TClau & clau, const TValor & valor)
{
	for (auto it = data->begin(); it != data->end(); it++)
	{
		if (it->first < clau)
		{
			data->insert(it, make_pair(clau, valor));
		}
	}
}

template<class TClau, class TValor>
inline Map<TClau, TValor>& Map<TClau, TValor>::operator=(const Map<TClau, TValor>& copy)
{
	if (this != copy)
	{
		if (data != nullptr)
			delete data;

		data = new vector<pair<TClau, TValor>>;
		for (auto i = 0; i < copy.longitud(); i++)
		{
			data->push_back(make_pair(copy[i], copy[copy[i]]));
		}
	}
	return *this;
}
