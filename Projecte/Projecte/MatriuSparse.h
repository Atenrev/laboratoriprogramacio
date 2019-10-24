#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class MatriuSparse
{
public:
	MatriuSparse();
	MatriuSparse(int num_rows, int num_columns);
	MatriuSparse(const MatriuSparse& m);
	~MatriuSparse();

	void init(int files, int columnes);
	int getNFiles() const { return num_rows; }
	int getNColumnes() const { return num_columns; }
	bool getVal(int row, int col, float& val) const;
	void setVal(int row, int col, float val);

	MatriuSparse operator*(float v);
	MatriuSparse operator*(float * v);
	MatriuSparse operator/(float v);
	MatriuSparse& operator=(const MatriuSparse& m);
private:
	int num_rows, num_columns;
	vector<int> * row_ptr = nullptr,
		* columns = nullptr;
	vector<float> * values = nullptr;
};