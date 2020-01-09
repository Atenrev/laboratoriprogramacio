#pragma once
#include "Heap.hpp"

template <class T>
class CuaPrioritat
{
public:
	CuaPrioritat() {}
	~CuaPrioritat() {}
	CuaPrioritat(const CuaPrioritat<T>& cua);
	CuaPrioritat<T>& operator=(const CuaPrioritat<T>& cua);

	bool esBuida() const;
	int getNElements() const;
	T& top();
	void push(const T& element);
	void pop();
	void remove(const T& element);
private:
	Heap<T> heap;
};


template<class T>
inline CuaPrioritat<T>::CuaPrioritat(const CuaPrioritat<T>& cua)
{
	heap = cua.heap;
}

template<class T>
inline CuaPrioritat<T>& CuaPrioritat<T>::operator=(const CuaPrioritat<T>& cua)
{
	if (this != &cua)
	{
		heap = cua.heap;
	}
	return *this;
}

template<class T>
inline bool CuaPrioritat<T>::esBuida() const
{
	return heap.esBuit();
}

template<class T>
inline int CuaPrioritat<T>::getNElements() const
{
	return heap.getMida()+1;
}

template<class T>
inline T& CuaPrioritat<T>::top()
{
	return heap.getMinim();
}

template<class T>
inline void CuaPrioritat<T>::push(const T& element)
{
	heap.insereix(element);
}

template<class T>
inline void CuaPrioritat<T>::pop()
{
	heap.esborraMinim();
}

template<class T>
inline void CuaPrioritat<T>::remove(const T& element)
{
	heap.esborra(element);
}
