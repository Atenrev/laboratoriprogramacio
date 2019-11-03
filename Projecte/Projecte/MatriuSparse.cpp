#include "MatriuSparse.h"


// CONSTRUCTORS AND DESTRUCTORS

MatriuSparse::MatriuSparse()
{
	init(0, 0);
	(*this->row_ptr).emplace_back(0);
}

MatriuSparse::MatriuSparse(int num_rows, int num_columns)
{
	init(num_rows, num_columns);
	resizeRowVector();
}

MatriuSparse::MatriuSparse(const MatriuSparse & m)
{
	init(m.getNFiles(), m.getNColumnes());
	
	if (m.values != nullptr && m.columns != nullptr)
	{
		(*columns).reserve((*(m.columns)).size());
		(*values).reserve((*(m.values)).size());
		for (int i = 0; i < m.values->size(); i++)
		{
			(*columns).emplace_back((*(m.columns))[i]);
			(*values).emplace_back((*(m.values))[i]);
		}
	}
	if (m.row_ptr != nullptr)
	{
		(*row_ptr).reserve((*(m.row_ptr)).size());
		for (int i = 0; i < m.row_ptr->size(); i++)
		{
			(*row_ptr).emplace_back((*(m.row_ptr))[i]);
		}
	}
}

MatriuSparse::MatriuSparse(const string & filename)
{
	init(0, 0);
	string line;
	ifstream fitxer(filename);
	int row, col, size;

	if (fitxer.is_open())
	{
		size = fitxer.tellg();
		(*columns).reserve(size/4);
		(*values).reserve(size/4);
		fitxer.clear();
		fitxer.seekg(0, ios::beg);

		int last_row = -1, i = 0;
		while (fitxer >> row >> col)
		{
			pushVal(row, col, 1);
			if (row != last_row)
			{
				while ((*row_ptr).size() < this->num_rows)
					(*row_ptr).emplace_back(i);
			}
			last_row = row;
			i++;
		}

		(*row_ptr).emplace_back(i);
		squareIt();
		resizeRowVector();

		(*columns).shrink_to_fit();
		(*values).shrink_to_fit();
	}
}

MatriuSparse::~MatriuSparse()
{
	delete row_ptr;
	delete columns;
	delete values;
}

void MatriuSparse::init(int num_rows, int num_columns)
{
	if (num_columns > num_rows)
	{
		this->num_columns = num_columns;
		this->num_rows = num_columns;
	}
	else
	{
		this->num_columns = num_rows;
		this->num_rows = num_rows;
	}

	this->columns = new vector<int>;
	this->values = new vector<float>;
	this->row_ptr = new vector<int>;
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
		int index;
		bool found = searchValue(row, col, index);
		val = found ? (*values)[index] : 0;
	}
		
	return success;
}

void MatriuSparse::setVal(int row, int col, const float val)
{
	if (val != 0)
	{
		if (col >= this->num_columns || this->num_columns <= 0)
		{
			this->num_columns = col + 1;
		}
		if (row >= this->num_rows || this->num_rows <= 0)
		{
			this->num_rows = row + 1;
		}

		squareIt();
		if (this->num_rows >= (*row_ptr).size())
			resizeRowVector();

 		int index;
		bool exists = searchValue(row, col, index);

		if (!exists)
		{
			(*columns).emplace((*columns).begin() + index, col);
			(*values).emplace((*values).begin() + index, val);

			auto it = begin(*row_ptr),
				end_row_ptr = end(*row_ptr);
			it += row + 1;
			for (; it != end_row_ptr; it++)
				*it += 1;
		}
		else
		{
			(*values)[index] = val;
		}
	}
}

void MatriuSparse::pushVal(int row, int col, const float val)
{
	if (val != 0)
	{
		if (col >= this->num_columns || this->num_columns <= 0)
		{
			this->num_columns = col + 1;
		}
		if (row >= this->num_rows || this->num_rows <= 0)
		{
			this->num_rows = row + 1;
		}

		(*columns).emplace_back(col);
		(*values).emplace_back(val);
	}
}



// MATRIX FUNCTIONS

bool MatriuSparse::searchValue(int row, int col, int& index) const
{
	int left = (*(this->row_ptr))[row],
		right = (*(this->row_ptr))[row + 1] - 1;
	index = (left + right) / 2;
	auto it = (*columns).begin() + index;

	if (left > right)
	{
		index = left;
		return false;
	}

	while (left <= right)
	{
		if (*it > col)
			right = index - 1;
		else if (*it < col)
			left = index + 1;
		else
			return true;

		index = (left+right) / 2;
		it = (*columns).begin() + index;
	}

	if (*it < col)
		index++;
	return false;
}

void MatriuSparse::resizeRowVector()
{
	(*row_ptr).reserve(num_rows + 1);
	int back = (*row_ptr).back();
	while ((*row_ptr).size() <= num_rows)
		(*row_ptr).emplace_back(back);
}

void MatriuSparse::squareIt()
{
	if (this->num_columns > this->num_rows)
	{
		this->num_rows = num_columns;
	}
	else
	{
		this->num_columns = num_rows;
	}
}



// OPERATORS

MatriuSparse MatriuSparse::operator*(float v)
{
	MatriuSparse result(*this);

	if (v != 0)
	{
		for (auto it = (*result.values).begin(); it != (*result.values).end(); it++)
		{
			*it = *it * v;
		}
	}
	else
	{
		result.columns->resize(0);
		result.values->resize(0);
		result.row_ptr->assign(num_rows+1, 0);
	}

	return result;
}

vector<float>& MatriuSparse::operator*(vector<float>& v)
{
	vector<float>* result = new vector<float>;

	if (v.size() == this->num_columns)
	{
		result->reserve((*row_ptr).size() - 1);
		float sum, val;
		int index, row_end;

		for (int i = 0; i < (*row_ptr).size() - 1; i++)
		{
			sum = 0;
			index = (*row_ptr)[i];
			row_end = (*row_ptr)[i + 1];

			if (index != row_end)
			{
				for (int j = index; j < row_end; j++)
				{
					sum += (*values)[j] * v[(*columns)[j]];
				}
			}

			result->emplace_back(sum);
		}
	}
	else
		throw "Vector size and matrix rows are not equal.";

	return *result;
}

MatriuSparse MatriuSparse::operator/(float v)
{
	MatriuSparse result(*this);

	if (v != 0)
	{
		for (auto it = (*result.values).begin(); it != (*result.values).end(); it++)
		{
			*it = *it / v;
		}
	}
	else
	{
		throw "Dividing by zero is not allowed...";
	}

	return result;
}

MatriuSparse & MatriuSparse::operator=(const MatriuSparse & m)
{
	if (this != &m)
	{
		this->num_columns = m.getNColumnes();
		this->num_rows = m.getNFiles();

		if (columns != nullptr)
			delete columns;
		this->columns = new vector<int>;
		if (values != nullptr)
			delete values;
		this->values = new vector<float>;
		if (row_ptr != nullptr)
			delete row_ptr;
		this->row_ptr = new vector<int>;

		if (m.values != nullptr && m.columns != nullptr)
		{
			(*columns).reserve((*(m.columns)).size());
			(*values).reserve((*(m.values)).size());
			for (int i = 0; i < m.values->size(); i++)
			{
				(*columns).emplace_back((*(m.columns))[i]);
				(*values).emplace_back((*(m.values))[i]);
			}
		}
		if (m.row_ptr != nullptr)
		{
			(*row_ptr).reserve((*(m.row_ptr)).size());
			for (int i = 0; i < m.row_ptr->size(); i++)
			{
				(*row_ptr).emplace_back((*(m.row_ptr))[i]);
			}
		}
	}
	return *this;
}

ostream & operator<<(ostream & out, const MatriuSparse & m)
{
	out << "MATRIU DE FILES: " << m.num_rows << " : COLUMNES: " << m.num_columns;
	int j;
	for (int i = 0; i < m.row_ptr->size()-1; i++)
	{
		if ((*(m.row_ptr))[i] != (*(m.row_ptr))[i + 1]) 
		{
			out << "\nVALORS FILA:" << i << "(COL:VALOR)\n";
			for (j = (*(m.row_ptr))[i]; j < (*(m.row_ptr))[i + 1]; j++)
			{
				out << "(" << (*(m.columns))[j] << " : " << (*(m.values))[j] << ") ";
			}
		}
	}
	out << "\nMATRIUS\nVALORS\n(" << flush;
	for (int i = 0; i < m.values->size(); i++)
	{
		out << (*(m.values))[i] << "  ";
	}
	out << ")\nCOLS\n(";
	for (int i = 0; i < m.columns->size(); i++)
	{
		out << (*(m.columns))[i] << "  ";
	}
	out << ")\nINIFILA\n(" << flush;
	for (int i = 0; i < m.getNFiles(); i++)
	{
		if ((*(m.row_ptr))[i] != (*(m.row_ptr))[i+1])
			out << "[ " << i << " : " << (*(m.row_ptr))[i] << " ] ";
	}
	out << " [Num Elems:" << (*(m.row_ptr))[m.getNFiles()] << "] )\n" << flush;
	return out;
}
