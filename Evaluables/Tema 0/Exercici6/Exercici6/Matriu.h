#pragma once


class Matriu
{
public:
	Matriu();
	Matriu(int nFiles, int nColumnes);
	Matriu(const Matriu& m);
	~Matriu();

	void resize(int nFiles, int nColumnes);
	void transpose();
	Matriu& operator=(const Matriu& m);
	void initValor(float valor);
	void setValor(int fila, int columna, float valor);
	Matriu operator+(const Matriu& m);
	Matriu operator+(float s);
	bool operator==(const Matriu& m);
	void deleteMatrix();

	bool esBuida() const;
	int getNFiles() const { return m_nFiles; }
	int getNColumnes() const { return m_nColumnes; }
	float getValor(int fila, int columna) const;
private:
	int m_nFiles, m_nColumnes;
	float* m_matriu = nullptr;
};