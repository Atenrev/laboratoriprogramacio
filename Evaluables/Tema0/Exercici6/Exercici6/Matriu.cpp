#include "Matriu.h"
#include <cmath>

Matriu::Matriu()
{
	m_nFiles = 0;
	m_nColumnes = 0;
	m_matriu = nullptr; 
}

Matriu::Matriu(int nFiles, int nColumnes)
{
	m_nFiles = nFiles;
	m_nColumnes = nColumnes;
	resize(nFiles, nColumnes);
	initValor(0);
}

Matriu::Matriu(const Matriu & m)
{
	m_nFiles = m.getNFiles();
	m_nColumnes = m.getNColumnes();
	resize(m_nFiles, m_nColumnes);

	for (int i = 0; i < m_nFiles; i++)
	{
		for (int j = 0; j < m_nColumnes; j++)
		{
			setValor(i, j, m.getValor(i, j));
		}
	}
}

Matriu::~Matriu()
{
	delete[] m_matriu;
}

void Matriu::resize(int nFiles, int nColumnes)
{
	if (m_matriu == nullptr)
		m_matriu = new float[nFiles*nColumnes];
	else 
	{
		float* novaMatriu = new float[nFiles * nColumnes];
		for (int i = 0; i < nFiles; i++)
		{
			for (int j = 0; j < nColumnes; j++)
			{
				novaMatriu[i*nColumnes+j] = getValor(i, j);
			}
		}
		delete[] m_matriu;
		m_matriu = novaMatriu;
	}
	m_nFiles = nFiles;
	m_nColumnes = nColumnes;
}

void Matriu::transpose()
{
	int nColumnes = m_nFiles,
		nFiles = m_nColumnes;
	float* novaMatriu = new float[m_nColumnes * m_nFiles];

	for (int i = 0; i < m_nFiles; i++)
	{
		for (int j = 0; j < m_nColumnes; j++)
		{
			novaMatriu[j*m_nFiles+i] = getValor(i, j);
		}
	}

	delete[] m_matriu;
	m_matriu = novaMatriu;
	m_nColumnes = nColumnes;
	m_nFiles = nFiles;
}

Matriu & Matriu::operator=(const Matriu & m)
{
	if (this != &m)
	{
		m_nFiles = m.getNFiles();
		m_nColumnes = m.getNColumnes();

		if (m_matriu != nullptr)
			delete[] m_matriu;

		resize(m_nFiles, m_nColumnes);
		
		if (!m.esBuida())
		{
			for (int i = 0; i < m_nFiles; i++)
			{
				for (int j = 0; j < m_nColumnes; j++)
				{
					setValor(i, j, m.getValor(i, j));
				}
			}
		}
		else
			m_matriu = nullptr;
	}

	return *this;
}

void Matriu::initValor(float valor)
{
	int total = m_nFiles * m_nColumnes;
	for (int i = 0; i < total; i++)
	{
		m_matriu[i] = valor;
	}
}

void Matriu::setValor(int fila, int columna, float valor)
{
	if (fila < m_nFiles && columna < m_nColumnes)
		m_matriu[fila*m_nColumnes+columna] = valor;
}

Matriu Matriu::operator+(const Matriu & m)
{
	Matriu result(*this);
	if (m.getNColumnes() == m_nColumnes && m.getNFiles() == m_nFiles)
	{
		for (int i = 0; i < m_nFiles; i++)
		{
			for (int j = 0; j < m_nColumnes; j++)
			{
				result.setValor(i, j, result.getValor(i, j) + m.getValor(i, j));
			}
		}
	}
	else
	{
		result.deleteMatrix();
		result.m_nColumnes = 0;
		result.m_nFiles = 0;
	}
	return result;
}

Matriu Matriu::operator+(float s)
{
	for (int i = 0; i < m_nFiles; i++)
	{
		for (int j = 0; j < m_nColumnes; j++)
		{
			setValor(i, j, getValor(i,j)+s);
		}
	}
	return *this;
}

bool Matriu::operator==(const Matriu & m)
{
	bool igual = true;

	if (m.getNFiles() == m_nFiles && m.getNColumnes() == m_nColumnes)
	{
		for (int i = 0; i < m_nFiles; i++)
		{
			for (int j = 0; j < m_nColumnes; j++)
			{
				if (getValor(i, j) != m.getValor(i, j))
				{
					igual = false;
					break;
				}
			}
		}
	}
	else
		igual = false;

	return igual;
}

bool Matriu::esBuida() const
{
	return (m_matriu == nullptr);
}

float Matriu::getValor(int fila, int columna) const
{
	int valor = 0;
	if (fila < m_nFiles && columna < m_nColumnes)
		valor = m_matriu[fila*m_nColumnes + columna];
	return valor;
}

void Matriu::deleteMatrix() {
	delete[] m_matriu;
	m_matriu = nullptr;
}