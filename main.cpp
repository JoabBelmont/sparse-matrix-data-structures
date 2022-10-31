#include <iostream>
#include "SparseMatrix.hpp"

using namespace std;

int main() {
	SparseMatrix *matrix = new SparseMatrix(3, 3);

	matrix->print();
	cout << endl;

	matrix->insert(1, 2, 1);
	matrix->insert(2, 1, 1);
	matrix->insert(2, 2, 1);
	matrix->insert(2, 3, 1);
	matrix->insert(3, 2, 1);

	matrix->print();
	cout << endl;

	matrix->insert(2, 2, 0);

	matrix->print();
	cout << endl;

	delete matrix;

	return 0;
}