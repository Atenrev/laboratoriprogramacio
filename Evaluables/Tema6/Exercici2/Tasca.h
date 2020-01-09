#pragma once

#include "Data.h"
#include <string>
using namespace std;

class Tasca
{
public:
	Tasca() : m_codi(""), m_prioritat(-1), m_data(Data()) {};
	Tasca(const string& codi, int prioritat, const Data& data) : m_codi(codi), m_prioritat(prioritat), m_data(data) {}
	string getCodi() const { return m_codi; }
	int getPrioritat() const { return m_prioritat; }
	Data getData() const { return m_data; }
	bool operator<(const Tasca& tasca);
	bool operator==(const Tasca& tasca);
private:
	string m_codi;
	int m_prioritat;
	Data m_data;
};