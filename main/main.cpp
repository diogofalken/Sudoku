/*
 * Aluno: Diogo Costa n16829
*/

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Numero parametros incorreto.\n");
		return 1;
	}

	struct sudoku *sudoku = lerFicheiro(argv[1]);
	ushort row = 0, col = 0;
	switch(verificarSudoku(sudoku->canvas, row, col)) {
		case 1: printf("\nErro na linha, na posicao [%hu,%hu].\n", row + 1, col + 1); return 0; break;
		case 2: printf("\nErro na coluna, na posicao [%hu,%hu].\n", row + 1, col + 1); return 0; break;
		case 3: printf("\nErro no quadrado, na posicao [%hu,%hu].\n", row + 1, col + 1); return 0; break;
	}
	printf("\n+------Inicio-----+");
	mostrarSudoku(sudoku->canvas);
	if (resolverSudoku(sudoku->canvas)) {
		printf("\n+----Resolucao----+");
		mostrarSudoku(sudoku->canvas);
	}
	free(sudoku);
}