#include <iostream>
#include "SparseMatrix.hpp"

int main() {
	SparseMatrix *matrix = new SparseMatrix(1, 3);
	matrix->print();
	delete matrix;

	return 0;
}