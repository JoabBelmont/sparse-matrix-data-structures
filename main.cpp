#include <iostream>
#include "SparseMatrix.hpp"

using namespace std;

SparseMatrix *sum(SparseMatrix *A, SparseMatrix *B);
SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B);

int main() {
	SparseMatrix *m1 = new SparseMatrix(1, 2);
	SparseMatrix *m2 = new SparseMatrix(2, 1);

	m1->insert(1, 1, 2);
	m1->insert(1, 2, 3);

	m2->insert(1, 1, 4);
	m2->insert(2, 1, 5);

	SparseMatrix *m3 = multiply(m1, m2);
	m3->print();

	return 0;
}

SparseMatrix *sum(SparseMatrix *A, SparseMatrix *B) {
	SparseMatrix *C = new SparseMatrix(A->getLineQty(), A->getColQty()); // Matriz C é inicializada com a mesma ordem de A e B

	/* Este bloco de código preenche os espacos(i, j) de C com os respectivos valores(i, j) de A.
	Basicamente, C vira uma cópia de A. */
	Node *auxLine = A->getHead()->down; // Ptr que apontará para as linhas (respectivo nó sentinela).
	while (auxLine != A->getHead()){
		Node *auxCol = auxLine; // Ptr que percorre os nós das linhas apontadas por auxLine.

		while (auxCol->right != auxLine){
			/* À medida que auxCol percorre a linha, inserimos seus valores(i, j) nos espaços(i, j) de C */
			auxCol = auxCol->right;
			C->insert(auxCol->line, auxCol->col, auxCol->value);
		}
		auxLine = auxLine->down; // Faz com que auxLine aponte para a próx linha.
	}

	/* O processo anterior é repetido, mas somamos os valores de B(i, j) aos valores de C(i, j) */
	auxLine = B->getHead()->down; // Ptr que apontará para as linhas (respectivo nó sentinela).
	while (auxLine != B->getHead()){
		Node *auxCol = auxLine; // Ptr que percorre os nós das linhas apontadas por auxLine.

		while (auxCol->right != auxLine){
			/* À medida que auxCol percorre a linha, somamos B(i, j) à C(i, j) e inserimos */
			auxCol = auxCol->right;
			C->insert(auxCol->line, auxCol->col, C->get(auxCol->line, auxCol->col) + auxCol->value);
		}
		auxLine = auxLine->down; // Faz com que auxLine aponte para a próx linha.
	}

	return C; // Retorna a matriz soma.
}

SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B) {
	if(A->getColQty() != B->getLineQty()) {
		throw std::runtime_error("Erro: Numero de colunas de A deve ser igual numero de linhas de B");
	}

	SparseMatrix *C = new SparseMatrix(A->getLineQty(), B->getColQty());

	Node *aux_lineA = A->getHead(); // Aponta para as linhas de A
	Node *aux_colB = B->getHead();	// Aponta para as colunas de B

	for(int i = 1; i <= A->getLineQty(); i++) {
		aux_lineA = aux_lineA->down;
		
		for (int j = 1; j <= B->getColQty(); j++){
			aux_colB = aux_colB->right;
			Node *correA = aux_lineA; // Percorre as linhas de A
			Node *correB = aux_colB;  // Percorre as colunas de B
			double soma = 0; // Guarda a soma dos produtos dos elementos das linhas e colunas de A e B
			for (int k = 0; k < A->getColQty(); k++){
				correA = correA->right;
				correB = correB->down;
				soma = soma + correA->value * correB->value;
			}
			C->insert(aux_lineA->line, aux_colB->col, soma);
		}
	}

	return C;
}
