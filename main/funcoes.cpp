/*
 * Aluno: Diogo Costa n16829
*/

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sudoku *lerFicheiro(char *nf) {
	FILE *file = fopen(nf, "r");
	if (!file) {
		printf("Erro abrir ficheiro\n");
		return NULL;
	}

	char buf[BUFFER_SIZE];
	ushort row = 0;
	struct sudoku *sudoku = (struct sudoku*)calloc(1, sizeof(struct sudoku));

	while (!feof(file)) {
		fgets(buf, BUFFER_SIZE, file);
		for (ushort col = 0; col < N; col++) {
			sudoku->canvas[row][col].valor = buf[col] - '0';
		}
		row++;
	}
	fclose(file);
	return sudoku;
}

void mostrarSudoku(struct pixel sudoku[N][N]) {
	printf("\n+-----+-----+-----+\n");
	for (ushort row = 0; row < N; row++) {
		for (ushort col = 0; col < N; col++) {
			printf("|%d", sudoku[row][col].valor);
		}
		printf("|\n");
		if ((row + 1) % 3 == 0) printf("+-----+-----+-----+\n");
	}
}

void verificarLinha(struct pixel sudoku[N][N], ushort row, ushort col) {
		ushort possibilidades[N] = { 1,1,1,1,1,1,1,1,1 };
		for (ushort col = 0; col < N; col++) {
			if (sudoku[row][col].valor != 0) {
				possibilidades[sudoku[row][col].valor - 1] = 0;
			}
		}
		memcpy(sudoku[row][col].lista_possibilidades, possibilidades, sizeof(possibilidades));
}

void verificarColuna(struct pixel sudoku[N][N], ushort row_pos, ushort col) {
	for (ushort row = 0; row < N; row++) {
		if (sudoku[row][col].valor != 0) {
			sudoku[row_pos][col].lista_possibilidades[sudoku[row][col].valor - 1] = 0;
		}
	}
}

void verificarQuadrado(struct pixel sudoku[N][N], ushort row_pos, ushort col_pos) {
	ushort startRow = row_pos - row_pos % 3;
	ushort startCol = col_pos - col_pos % 3;

	for (ushort row = 0; row < 3; row++) {
		for (ushort col = 0; col < 3; col++) {
			if (sudoku[row + startRow][col + startCol].valor != 0)
				sudoku[row_pos][col_pos].lista_possibilidades[sudoku[row + startRow][col + startCol].valor - 1] = 0;
		}
	}
}

int valorLivre(struct pixel sudoku[N][N], ushort &row, ushort &col) {
	for (row = 0; row < N; ++row) {
		for (col = 0; col < N; ++col) {
			if (sudoku[row][col].valor == 0)
				return 1;
		}
	}
	return 0;
}

void verificarRegras(struct pixel sudoku[N][N], ushort row, ushort col) {
	verificarLinha(sudoku, row, col);
	verificarColuna(sudoku, row, col);
	verificarQuadrado(sudoku, row, col);
}

int verificarSudoku(struct pixel sudoku[N][N], ushort &row_erro, ushort &col_erro) {
	mostrarSudoku(sudoku);
	for (ushort row = 0; row < N; ++row) {
		for (ushort col = 0; col < N; ++col) {
			// Verificar valor na linha
			for (ushort aux = 0; aux < N; aux++) {
				if(sudoku[row][col].valor != 0 && aux != col)
					if (sudoku[row][aux].valor == sudoku[row][col].valor) {
						row_erro = row;
						col_erro = col;
						return 1;
					}
			}
				

			// Verificar valor na coluna
			for (int aux = 0; aux < N; aux++)
				for (ushort aux = 0; aux < N; aux++) {
					if (sudoku[row][col].valor != 0 && row != aux)
						if (sudoku[aux][col].valor == sudoku[row][col].valor) {
							row_erro = row;
							col_erro = col;
							return 2;
						}
				}

			// Verificar quadrado
			ushort startRow = row - row % 3;
			ushort startCol = col - col % 3;
			for (int aux_row = 0; aux_row < 3; aux_row++)
				for (int aux_col = 0; aux_col < 3; aux_col++)
					if (sudoku[aux_row + startRow][aux_col + startCol].valor != 0 && aux_row + startRow != row && aux_col + startCol != col)
						if (sudoku[aux_row + startRow][aux_col + startCol].valor == sudoku[row][col].valor) {
							row_erro = row;
							col_erro = col;
							return 3;
						}
		}
	}
	return 0;
}

int resolverSudoku(struct pixel sudoku[N][N]) {
	ushort row, col;

	// Se o array estiver vazio terminou 
	if (!valorLivre(sudoku, row, col))
		return 1;

	verificarRegras(sudoku, row, col);

	for (int num = 1; num <= N; num++) {
		if (sudoku[row][col].lista_possibilidades[num - 1] == 1) {
			// Testar com o valor
			sudoku[row][col].valor = num;
			
			// Se for o valor certo
			if (resolverSudoku(sudoku))
				return 1;

			// Se for o valor errado, resetamos o valor
			sudoku[row][col].valor = 0;
			sudoku[row][col].lista_possibilidades[num - 1] = 0;
		}
	}
	// Volta atras
	return 0; 
}