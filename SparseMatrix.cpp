/**
 * @file SparseMatrix.cpp
 * @authors Antonio Joabe Alves Morais  | Matrícula: 539029
 *          Iarley Natã Souza Lopes     | Matrícula: 535779
 * @brief
 * Arquivo de implementação de um TAD de uma Matriz Esparsa.
 */

#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix(int m, int n) {
	/* Lança uma exceção caso m ou n não forem positivos */
	if(m <= 0 || n <= 0)
		throw std::invalid_argument("Parameters m & n must be positive");

	/* Primeiro sentinela: linha 0, coluna 0 */
	Node * firstSentinel = new Node(nullptr, nullptr, 0, 0, 0);
	m_head = firstSentinel; // Faz o nó cabeça apontar pra ele
	firstSentinel->right = firstSentinel->down = firstSentinel; // E os ptrs. right e down apontarem para ele mesmo

	Node *current = firstSentinel; // Ponteiro usado para percorrer os sentinelas nos for's seguintes

	/* Inicializa os sentinelas das linhas */
	for(int i = 1; i <= m; i++) {
		/* Inicializa e "trata" os atributos do novo nó sentinela */
		Node *sentinel = new Node(nullptr, nullptr, 0, 0, 0);
		sentinel->line = i; // Atribui o número da linha
		current->right = sentinel; // "Linka" o sentinela atual com o anterior
		sentinel->right = firstSentinel; // Faz o ptr. right apontar para o início da linha
		sentinel->down = sentinel; // E o ptr. down apontar para ele mesmo
		current = current->right; // Anda o ptr atual
		lineSize++; // Incrementa o número de linhas
	}

	current = firstSentinel; // Renicia o ptr

	/* Inicializa os sentinelas das colunas */
	for(int j = 1; j <= n; j++) {
		/* Inicializa e "trata" os atributos do novo nó sentinela */
		Node *sentinel = new Node(nullptr, nullptr, 0, 0, 0);
		sentinel->col = j; // Atribui o número da coluna
		current->down = sentinel; // "Linka" o sentinela atual com o anterior
		sentinel->right = sentinel; // Faz o ptr. right apontar para ele mesmo
		sentinel->down = firstSentinel; // E o ptr. down apontar para o início da coluna
		current = current->down; // Anda o ptr atual
		colSize++; // Incrementa o número de colunas
	}
}