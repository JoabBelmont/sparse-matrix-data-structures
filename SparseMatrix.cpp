/**
 * @file SparseMatrix.h
 * @authors Antonio Joabe Alves Morais  | Matrícula: 539029
 *          Iarley Natã Souza Lopes     | Matrícula:
 * @brief
 * Arquivo protóripo de um TAD de uma Matriz Esparsa.
 */

#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix(int m, int n) {
	/* Lança uma exceção caso m ou n não forem positivos */
	if(m <= 0 || n <= 0)
		throw std::invalid_argument("Parameters m & n must be positive");
	
}