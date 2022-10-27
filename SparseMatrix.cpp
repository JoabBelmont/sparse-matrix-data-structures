/**
 * @file SparseMatrix.cpp
 * @authors Antonio Joabe Alves Morais  | Matrícula: 539029
 *          Iarley Natã Souza Lopes     | Matrícula: 535779
 * @brief
 * Arquivo de implementação de um TAD de uma Matriz Esparsa. */

#include "SparseMatrix.hpp"
#include <iostream>

SparseMatrix::SparseMatrix(int m, int n) {
	/* Lança uma exceção caso m ou n não forem positivos */
	if(m <= 0 || n <= 0)
		throw std::invalid_argument("Parameters m & n must be positive");

	/* Primeiro sentinela: linha 0, coluna 0 */
	Node * firstSentinel = new Node(nullptr, nullptr, 0, 0, 0);
	m_head = firstSentinel; // Faz o nó cabeça apontar pra ele
	firstSentinel->right = firstSentinel->down = firstSentinel; // E os ptrs. right e down do sentinela apontarem para ele mesmo

	Node *current = firstSentinel; // Ponteiro usado para percorrer os sentinelas nos for's seguintes

	/* Inicializa os sentinelas das linhas */
	for(int i = 1; i <= n; i++) {
		/* Inicializa e "trata" os atributos do novo nó sentinela */
		Node *sentinel = new Node(nullptr, nullptr, 0, 0, 0);
		sentinel->line = i; // Atribui o número da linha
		current->down = sentinel; // "Linka" o sentinela atual com o anterior
		sentinel->right = sentinel; // Faz o ptr. right apontar para ele mesmo
		sentinel->down = firstSentinel; // E o ptr. down apontar para o início da coluna
		current = current->down; // Anda o ptr atual
		lineQty++; // Incrementa o número de linhas
	}

	current = firstSentinel; // Renicia o ptr

	/* Inicializa os sentinelas das colunas */
	for(int j = 1; j <= m; j++) {
		/* Inicializa e "trata" os atributos do novo nó sentinela */
		Node *sentinel = new Node(nullptr, nullptr, 0, 0, 0);
		sentinel->col = j; // Atribui o número da coluna
		current->right = sentinel; // "Linka" o sentinela atual com o anterior
		sentinel->right = firstSentinel; // Faz o ptr. right apontar para o início da linha
		sentinel->down = sentinel; // E o ptr. down apontar para ele mesmo
		current = current->right; // Anda o ptr atual
		colQty++; // Incrementa o número de colunas
	}
}

SparseMatrix::~SparseMatrix() {
	Node *aux_line = m_head; 
	/* Deleta os elementos a partir da coluna 1 */
	while(aux_line->down != m_head) { 
		while(aux_line->right != aux_line){
			Node *aux_col = aux_line;
			while (aux_col->right->right != aux_line){
				aux_col = aux_col->right; // Anda na linha
			}
			delete aux_col->right; // Deleta o último elemento da linha
			aux_col->right = aux_line; // Faz o penúltimo (agr último) apontar para o início
		}
		aux_line = aux_line->down; // Anda na coluna
	}

	/* Deleta os elementos da coluna 0 */
	while(m_head->down != m_head) {
		aux_line = m_head;
		while(aux_line->down->down != m_head) {
			aux_line = aux_line->down; // Anda na coluna 0
		}
		delete aux_line->down; // Deleta o último elemento da coluna
		aux_line->down = m_head; // Faz o penúltimo (agr último) apontar para o início
	}

	delete m_head; // Deleta o primeiro sentinela (0, 0)

	m_head = nullptr;
	aux_line = nullptr;
	lineQty = colQty = 0;

	std::cout << "Matrix destructed";
}

void SparseMatrix::print() {
	Node *currentLine = m_head->down; // Aponta para o sentinela da linha
	Node *currentCol = nullptr; // Vai apontar para os elementos da linha (colunas)
	for(int i = 1; i <= lineQty; i++) {
		currentCol = currentLine->right;
		for(int j = 1; j <= colQty; j++) {
			/* Imprime o valor do elemento se ele existir */
			if((currentCol->line == i) && (currentCol->col = j)) {
				std::cout << currentCol->value << " "; 
				if(currentCol->right != currentLine) // Se não for o último elemento 
					currentCol = currentCol->right; // Anda a coluna
			} else {
				std::cout << "0" << " "; // Senão existir, imprime 0
			}

			/* Anda a linha se chegar na última coluna e se  */
			if((currentCol->right == currentLine) && (currentCol->col == j)) {
				currentLine = currentLine->down;
			}
		}
		std::cout << std::endl;
	}
}

double SparseMatrix::get(int i, int j) {
	/* Lança uma exceção se a coordenada não for válida */
	if(i <= 0 || j <= 0 || i > lineQty || j > colQty) 
		throw std::invalid_argument("Invalid coordinate");

	Node *currentLine = m_head->down; // Ponteiro que aponta para o início das linhas	
	/* Encontra a linha "i" */
	while(currentLine->line != i) {
		currentLine = currentLine->down;
	}

	Node *currentCol = currentLine->right; // Ponteiro que aponta para os nós na linha "i" 
	/* Faz "currentCol" percorrer a linha "i" até que o nó(i, j) seja encontrado */
	while(currentCol->col != j) { 
		currentCol = currentCol->right;
		if (currentCol->right == currentLine && currentCol->col != j){
			return 0; // Se a lista foi percorrida e não foi encontrado o nó(i, j), retorna "0"
		}
	}
	return currentCol->value; // Retorna "currentCol.value" se o nó(i, j) foi encontrado
}
