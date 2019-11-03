#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
const int MATRIX_DEBUG = false;

class MatriuSparse
{
public:
	MatriuSparse();
	MatriuSparse(int num_rows, int num_columns);
	MatriuSparse(const MatriuSparse& m);
	MatriuSparse(const string& filename);
	~MatriuSparse();

	void init(int files, int columnes);
	int getNFiles() const { return num_rows; }
	int getNColumnes() const { return num_columns; }
	bool getVal(int row, int col, float& val) const;
	void setVal(int row, int col, const float val);
	void pushVal(int row, int col, const float val);
	bool searchValue(int row, int col, int& index) const;
	void resizeRowVector();
	void squareIt();

	MatriuSparse operator*(float v);
	vector<float>& operator*(vector<float>& v);
	MatriuSparse operator/(float v);
	MatriuSparse& operator=(const MatriuSparse& m);

	friend ostream& operator<<(ostream &out, const MatriuSparse& m);
private:
	int num_rows, num_columns;
	vector<int> * row_ptr = nullptr,
		* columns = nullptr;
	vector<float> * values = nullptr;
};