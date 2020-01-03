#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ElemHeap
{
public:
	ElemHeap() { m_Val = 0; m_Pos = { 0, 0 }; }
	ElemHeap(double val, pair<int, int> pos) { m_Val = val; m_Pos = pos; };
	double getVal() const { return m_Val; }
	pair<int,int> getPos() const { return m_Pos; }
	bool operator<(const ElemHeap& e) { return (m_Val < e.m_Val); }
	bool operator<=(const ElemHeap& e) { return (m_Val <= e.m_Val); }
	bool operator>(const ElemHeap& e) { return (m_Val > e.m_Val);}
	bool operator>=(const ElemHeap& e) { return (m_Val >= e.m_Val); }
	bool operator==(const ElemHeap& e) { return ( m_Val == e.m_Val);	}
	~ElemHeap() {};
	ElemHeap& operator=(const ElemHeap& e) { m_Val = e.m_Val; m_Pos = e.m_Pos; return *this; }
	friend std::ostream& operator<<(std::ostream& out, const ElemHeap& elHeap)
	{
		out << "( < " << elHeap.m_Pos.first << " , " << elHeap.m_Pos.second << " > ; " << elHeap.m_Val << " )" << endl;
		return out;
	}

private:
	double m_Val;
	pair<int, int> m_Pos;
};