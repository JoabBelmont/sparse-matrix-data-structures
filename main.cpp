#include <iostream>
#include "SparseMatrix.hpp"

using namespace std;

int main() {
	SparseMatrix *matrix = new SparseMatrix(9, 9);

	matrix->print();
	cout << endl;

	for(int i = 4; i <= 6; i++)
		matrix->insert(1, i, 1);

	matrix->insert(2, 3, 1);
	matrix->insert(2, 7, 1);

	matrix->insert(3, 2, 1);
	matrix->insert(3, 8, 1);

	for(int i = 4; i <= 6; i++) {
		matrix->insert(i, 1, 1);
		matrix->insert(i, 9, 1);
	}

	matrix->insert(7, 2, 1);
	matrix->insert(7, 8, 1);

	matrix->insert(8, 3, 1);
	matrix->insert(8, 7, 1);

	for(int i = 4; i <= 6; i++)
		matrix->insert(9, i, 1);

	matrix->print();
	cout << endl;

	cout << endl;

	delete matrix;

	return 0;
}