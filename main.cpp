#include <iostream>
#include <fstream>
#include "SparseMatrix.hpp"

using namespace std;

/* Soma 2 matrizes e retorna uma matriz resultado */
SparseMatrix *sum(SparseMatrix *A, SparseMatrix *B);
/* Multiplica 2 matrizes e retorna uma matriz resultado */
SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B);
/* Lê um arquivo .txt e monta uma matriz com base nos dados desse arquivo */
SparseMatrix *readSparseMatrix(string fileName);

int main() {
	SparseMatrix *A = readSparseMatrix("A.txt");
	A->print();

	return 0;
}

SparseMatrix *sum(SparseMatrix *A, SparseMatrix *B) {
	if(A->getLineQty() != B->getLineQty() || A->getColQty() != B->getColQty()) {
		throw std::runtime_error("Matrices must have equal orders");
	}

	SparseMatrix *C = new SparseMatrix(A->getLineQty(), A->getColQty()); // Matriz C é inicializada com a mesma ordem de A e B

	/* Este bloco de código preenche os espacos(i, j) de C com os respectivos valores(i, j) de A.
	Basicamente, C vira uma cópia de A. */
	Node *auxLine = A->getHead()->down; // Ptr que apontará para as linhas (respectivo nó sentinela).
	while(auxLine != A->getHead()) {
		Node *auxCol = auxLine; // Ptr que percorre os nós das linhas apontadas por auxLine.

		while(auxCol->right != auxLine) {
			/* À medida que auxCol percorre a linha, inserimos seus valores(i, j) nos espaços(i, j) de C */
			auxCol = auxCol->right;
			C->insert(auxCol->line, auxCol->col, A->get(auxCol->line, auxCol->col));
		}
		auxLine = auxLine->down; // Faz com que auxLine aponte para a próx linha.
	}

	/* O processo anterior é repetido, mas somamos os valores de B(i, j) aos valores de C(i, j) */
	auxLine = B->getHead()->down; // Ptr que apontará para as linhas (respectivo nó sentinela).
	while(auxLine != B->getHead()) {
		Node *auxCol = auxLine; // Ptr que percorre os nós das linhas apontadas por auxLine.

		while(auxCol->right != auxLine) {
			/* À medida que auxCol percorre a linha, somamos B(i, j) à C(i, j) e inserimos */
			auxCol = auxCol->right;
			C->insert(auxCol->line, auxCol->col, C->get(auxCol->line, auxCol->col) + B->get(auxCol->line, auxCol->col));
		}
		auxLine = auxLine->down; // Faz com que auxLine aponte para a próx linha.
	}

	return C; // Retorna a matriz soma.
}

SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B) {
	if(A->getColQty() != B->getLineQty()) {
		throw std::runtime_error("Number of collumns of the 1st matrix must be equal to the number of lines of the 2nd matrix");
	}

	SparseMatrix *C = new SparseMatrix(A->getLineQty(), B->getColQty());

	Node *aux_lineA = A->getHead(); // Aponta para as linhas de A
	Node *aux_colB = B->getHead();	// Aponta para as colunas de B

	/* Faz com que aux_lineA alterne entre as linhas de A */
	for(int i = 1; i <= A->getLineQty(); i++) { 
		aux_lineA = aux_lineA->down;
		
		for(int j = 1; j <= B->getColQty(); j++) { // Faz com que aux_colB alterne entre as colunas de B
			aux_colB = aux_colB->right;
			Node *correA = aux_lineA->right; // Percorre as linhas de A
			Node *correB = aux_colB->down;  // Percorre as colunas de B
			static double soma = 0; // Guarda a soma dos produtos dos elementos das linhas e colunas de A e B
			for(int k = 1; k <= A->getColQty(); k++) { // Faz com que correA e correB percorram as linhas e colunas de A e B, respectivamente
				soma = soma + A->get(i, k) * B->get(k, j);
				correA = correA->right;
				correB = correB->down;
			}
			C->insert(i, j, soma); // Insere o valor da soma no nó(i, j) de C
			soma = 0;
		}
	}

	return C;
}

SparseMatrix *readSparseMatrix(string fileName) {
	ifstream file;
	int lineQty, colQty, i, j;
	double value;

	/* Abre o arquivo com o nome passado pelo parâmetro da função */
	file.open(fileName);

	/* Se não conseguir abrir o arquivo, lança uma exceção */
	if(!file.is_open()) {
		throw std::runtime_error("File not found");
	}

	/* Lê a quantidade de linhas e colunas da matriz */
	file >> lineQty >> colQty;
	SparseMatrix *matrix = new SparseMatrix(lineQty, colQty);

	/* Lê as cordenadas, os valores e insere-os na matriz */
	while(file >> i >> j >> value) {
		matrix->insert(i, j, value);
	}

	return matrix;
}