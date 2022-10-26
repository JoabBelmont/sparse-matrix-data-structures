/**
 * @file SparseMatrix.h
 * @authors Antonio Joabe Alves Morais  | Matrícula: 539029
 *          Iarley Natã Souza Lopes     | Matrícula:
 * @brief
 * Arquivo protóripo de um TAD de uma Matriz Esparsa. */

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "Node.h"

/* TAD da matriz esparsa */
class SparseMatrix {
private:
	Node *m_head { nullptr }; // Ponteiro inicial da matriz
	int lineQty { 0 }; // Número de linhas da matriz
	int colQty { 0 }; // Número de colunas da matriz
public:
	/* Inicializa a matriz para conter m linhas e n colunas,
	 * além de checar se os parâmetros são > 0.
	 * Caso contrário, lança uma exceção. */
	SparseMatrix(int m, int n);

	/* Libera a memória alocada pela "SparseMatrix(int m, int n)" */
	~SparseMatrix();
	
	/**/
	void insert(int i, int j, double value);

	/**/
	double get(int i, int j);

	/**/
	void print();
};

#endif