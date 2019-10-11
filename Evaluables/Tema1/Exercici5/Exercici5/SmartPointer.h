#pragma once
#include <iostream>
using namespace std;

template <class T>
class SmartPointer
{
public:
	SmartPointer();
	SmartPointer(SmartPointer<T> & copy);

	SmartPointer<T>& operator=(SmartPointer& s);
	SmartPointer<T>& operator=(T* p);
	T& operator * ();
	T* operator -> ();
	bool isNull() const;

	T* getPointer() { return pointer; }
	void setPointerToNull() { pointer = nullptr; }
	void deletePointer() {
		if (pointer != nullptr)
			delete pointer;
	}
private:
	T * pointer;
};

template<class T>
inline SmartPointer<T>::SmartPointer()
{
	pointer = nullptr;
}

template<class T>
inline SmartPointer<T>::SmartPointer(SmartPointer<T>& copy)
{
	pointer = copy.getPointer();
	copy.setPointerToNull();
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer & s)
{
	deletePointer();
	pointer = s.getPointer();
	s.setPointerToNull();
	return *this;
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(T * p)
{
	deletePointer();
	pointer = p;
	return *this;
}

template<class T>
inline T & SmartPointer<T>::operator*()
{
	if (isNull())
		cout << "Error: null pointer.";
	return *pointer;
}

template<class T>
inline T * SmartPointer<T>::operator->()
{
	if (isNull())
		cout << "Error: null pointer.";
	return pointer;
}

template<class T>
inline bool SmartPointer<T>::isNull() const
{
	return (pointer == nullptr);
}
