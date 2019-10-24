#include "MatriuSparse.h"

// CONSTRUCTORS AND DESTRUCTORS

MatriuSparse::MatriuSparse()
{
	this->num_columns = 0;
	this->num_rows = 0;
	this->columns = new vector<int>;
	this->values = new vector<float>;
	this->row_ptr = new vector<int>;
	(*this->row_ptr).push_back(0);
}

MatriuSparse::MatriuSparse(int num_rows, int num_columns)
{
	this->num_columns = num_columns;
	this->num_rows = num_rows;
	this->columns = new vector<int>;
	this->values = new vector<float>;
	this->row_ptr = new vector<int>;
	(*this->row_ptr).push_back(0);
}

MatriuSparse::MatriuSparse(const MatriuSparse & m)
{

}

MatriuSparse::~MatriuSparse()
{

}

// INITIALIZATION

void MatriuSparse::init(int files, int columnes)
{
	this->num_columns = num_columns;
	this->num_rows = num_rows;
}

// GETTERS AND SETTERS OF VALUES

bool MatriuSparse::getVal(int row, int col, float & val) const
{
	bool success;

	if (row < 0 || col < 0
		|| row >= this->num_rows || col >= this->num_columns)
	{
		success = false;
	}
	else
	{
		success = true;
		val = 0;

		int index = (*(this->row_ptr))[row];
		for (; index < (*(this->row_ptr))[row + 1]; index++)
		{
			if ((*(this->columns))[index] == col)
			{
				val = (*(this->values))[index];
				break;
			}
		}
	}

	return success;
}

void MatriuSparse::setVal(int row, int col, float val)
{
	if (val != 0)
	{
		if (col >= this->num_columns)
			this->num_columns = col + 1;
		if (row >= this->num_rows)
		{
			this->num_rows = row + 1;
			while ((*(this->row_ptr)).size() < this->num_rows)
				(*(this->row_ptr)).push_back(
					(*(this->row_ptr))[(*(this->row_ptr)).size() - 1]
				);
		}

		int index = (*(this->row_ptr))[row];

		// Falta afegir el valor a columnes i valors. 
		// Cal comprovar que no hi hagi ja un element a la fila:columna
		// En aquest cas, què es faria?

		for (int i = row + 1; i <= this->num_rows; i++)
		{
			(*(this->row_ptr))[i]++;
		}
		
		int row_end = (*(this->row_ptr))[row + 1];
	}
}

// OPERATORS

MatriuSparse MatriuSparse::operator*(float v)
{
	return MatriuSparse();
}

MatriuSparse MatriuSparse::operator*(float * v)
{
	return MatriuSparse();
}

MatriuSparse MatriuSparse::operator/(float v)
{
	return MatriuSparse();
}

MatriuSparse & MatriuSparse::operator=(const MatriuSparse & m)
{
	// TODO: insertar una instrucción return aquí
}
