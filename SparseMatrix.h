/**
 * @file SparseMatrix.h
 * @authors Antonio Joabe Alves Morais	| Matrícula: 539029
 * 			Iarley Natã Souza Lopes		| Matrícula:
 * @brief
 * 		Arquivo protóripo de um TAD de uma Matriz Esparsa.
 */

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

/* Estrutura nó da matriz */
struct Node {
private:
	Node *right;	// Aponta para o próximo elemento não-nulo da linha
	Node *down;		// Aponta para o próximo elemento não-nulo da coluna
	int line;		// Dado da linha
	int col;		// Dado da coluna
	double value;	// Valor do elemento
public:
	/* Construtor que inicializa o nó com seus 5 parâmetros */
	Node(Node *right, Node *down, int line, int col, double value) {
		this->right = right;
		this->down = down;
		this->line = line;
		this->col = col;
		this->value = value;
	}
};

/* TAD da matriz esparsa */
class SparseMatrix {
	/* Inicializa a matriz para conter m linhas e n colunas,
	 * além de checar se os parâmetros são > 0.
	 * Caso contrário, lança uma excessão. */
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