#include <iostream>
#include "SparseMatrix.hpp"

int main() {
	SparseMatrix *matrix = new SparseMatrix(3, 3);
	matrix->print();
	std::cout << matrix->get(1, 1) << std::endl;
	delete matrix;

	return 0;
}