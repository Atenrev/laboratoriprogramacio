#include "MatriuSparse.h"

// CONSTRUCTORS AND DESTRUCTORS

MatriuSparse::MatriuSparse()
{
	init(0, 0);
	(*this->row_ptr).push_back(0);
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
		for (int i = 0; i < m.values->size(); i++)
		{
			(*(this->columns)).push_back((*(m.columns))[i]);
			(*(this->values)).push_back((*(m.values))[i]);
		}
	}
	if (m.row_ptr != nullptr)
	{
		for (int i = 0; i < m.row_ptr->size(); i++)
		{
			(*(this->row_ptr)).push_back((*(m.row_ptr))[i]);
		}
	}
}

MatriuSparse::MatriuSparse(const string & filename)
{
	init(0, 0);
	(*this->row_ptr).push_back(0);
	string line;
	ifstream fitxer;
	fitxer.open(filename);

	int row, col;
	if (fitxer.is_open())
	{
		while (getline(fitxer, line))
		{
			try
			{
				stringstream linestream(line);
				string split_line;
				getline(linestream, split_line, '\t');
				row = stoi(split_line);
				getline(linestream, split_line, '\t');
				col = stoi(split_line);
				cout << row << " " << col << "\n";
				setVal(row, col, 1);
			}
			catch (exception e) 
			{
				cout << "An error has occurred while loading the matrix from file.";
			}
		}
	}
	try
	{
		fitxer.close();
	}
	catch (exception e)
	{
		cout << "File could not be closed.";
	}
}

MatriuSparse::~MatriuSparse()
{
	// TODO
}

// INITIALIZATION

void MatriuSparse::init(int num_rows, int num_columns)
{
	this->num_columns = num_columns;
	this->num_rows = num_rows;
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

void MatriuSparse::setVal(int row, int col, const float val)
{
	if (val != 0)
	{
		if (col > this->num_columns || this->num_columns <= 0)
			this->num_columns = col + 1;
		if (row > this->num_rows || this->num_rows <= 0)
		{
			this->num_rows = row + 1;
			resizeRowVector();
		}

		int index = (*(this->row_ptr))[row],
			row_end = (*(this->row_ptr))[row+1];
		bool exists = false;

		if (index != row_end)
		{
			while (index < row_end && col > (*(this->columns))[index])
			{
				exists = ((*(this->columns))[index] == col);
				index++;
			}
		}

		if (!exists)
		{
			(*(this->columns)).insert((*(this->columns)).begin() + index, col);
			(*(this->values)).insert((*(this->values)).begin() + index, val);

			for (int i = row + 1; i <= this->num_rows; i++)
			{
				(*(this->row_ptr))[i]++;
			}
		}
		else
		{
			(*(this->values))[index] = val;
		}
	}
}

void MatriuSparse::resizeRowVector()
{
	while ((*(this->row_ptr)).size() <= this->num_rows)
		(*(this->row_ptr)).push_back(
			(*(this->row_ptr))[(*(this->row_ptr)).size() - 1]
		);
}

// OPERATORS

MatriuSparse MatriuSparse::operator*(float v)
{
	// TODO
	return MatriuSparse();
}

vector<float>& MatriuSparse::operator*(vector<float>& v)
{
	// TODO
	return (*(new vector<float>));
}

MatriuSparse MatriuSparse::operator/(float v)
{
	// TODO
	return MatriuSparse();
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
			for (int i = 0; i < m.values->size(); i++)
			{
				(*(this->columns)).push_back((*(m.columns))[i]);
				(*(this->values)).push_back((*(m.values))[i]);
			}
		}
		if (m.row_ptr != nullptr)
		{
			for (int i = 0; i < m.row_ptr->size(); i++)
			{
				(*(this->row_ptr)).push_back((*(m.row_ptr))[i]);
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
		out << "\nVALORS FILA:" << i << "COL:VALOR\n";
		for (j = (*(m.row_ptr))[i]; j < (*(m.row_ptr))[i + 1]; j++)
		{
			out << "(" << (*(m.columns))[j] << " : " << (*(m.values))[j] << ") ";
		}
	}
	out << "\nMATRIUS\nVALORS\n(";
	for (int i = 0; i < m.values->size(); i++)
	{
		out << (*(m.values))[i] << " ";
	}
	out << ")\nCOLS\n(";
	for (int i = 0; i < m.columns->size(); i++)
	{
		out << (*(m.columns))[i] << " ";
	}
	out << ")\INIFILA\n(";
	for (int i = 0; i < m.row_ptr->size()-1; i++)
	{
		out << "[ " << i << " : " << (*(m.row_ptr))[i] << " ] ";
	}
	out << "[ Num Elems:" << (*(m.row_ptr))[m.row_ptr->size() - 1] << " ] )";
	return out;
}
