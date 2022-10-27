#include <iostream>
#include "SparseMatrix.h"

int main() {
	SparseMatrix *matrix = new SparseMatrix(10, 10);
	matrix->print();
	delete matrix;

	return 0;
}