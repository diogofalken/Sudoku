/*
 * Aluno: Diogo Costa n16829
*/
#pragma once

typedef unsigned short ushort;
#define N 9 
#define BUFFER_SIZE 32
#define DELIM " \n"

struct pixel {
	ushort lista_possibilidades[9];
	ushort valor;
};

struct sudoku {
	struct pixel canvas[9][9];
};