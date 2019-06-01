/*
 * Aluno: Diogo Costa n16829
*/
#pragma once

#include "tipos.h"

/**
 * @brief Lê o ficheiro que contém o sudoku
 * @param *nf contém o caminho relativo para o ficheiro
 * @return o array bidemensional com os valores do sudoku
 */
struct sudoku *lerFicheiro(char *nf);

/**
 * @brief Imprime o canvas de jogo
 * @param **sudoku array bidemensional com a canvas de jogo
 */
void mostrarSudoku(struct pixel sudoku[N][N]);

/**
 * @brief Verifica se o sudoku ainda tem valores a 0
 * @param sudoku[N][N] array bidemensional com a canvas de jogo
 * @param &row serve para caso exista um valor que esteja a 0 devolva a row deste
 * @param &col serve para caso exista um valor que esteja a 0 devolva a col deste
 * @return 1 se existe ainda valores por atribuir
 * @return 0 se todos os valores estao atribuidos
 */
int valorLivre(struct pixel sudoku[N][N], ushort &row, ushort &col);

/**
 * @brief Verifica todos os valores de uma linha e coloca a 0 na "lista" de possibilidades os valores que ja se encontram na linha
 * @param sudoku[N][N] array bidemensional com a canvas de jogo
 * @param row onde se pretende fazer a pesquisa
 * @param col onde se pretende fazer a pesquisa
 */
void verificarLinha(struct pixel sudoku[N][N], ushort row, ushort col);

/**
 * @brief Verifica todos os valores de uma coluna e coloca a 0 na "lista" de possibilidades os valores que ja se encontram na linha
 * @param sudoku[N][N] array bidemensional com a canvas de jogo
 * @param row onde se pretende fazer a pesquisa
 * @param col onde se pretende fazer a pesquisa
 */
void verificarColuna(struct pixel sudoku[N][N], ushort row, ushort col);

/**
 * @brief Verifica todos os valores de um "quadrado" e coloca a 0 na "lista" de possibilidades os valores que ja se encontram na linha
 * @param sudoku[N][N] array bidemensional com a canvas de jogo
 * @param row_pos onde se pretende fazer a pesquisa
 * @param col_pos onde se pretende fazer a pesquisa
 */
void verificarQuadrado(struct pixel sudoku[N][N], ushort row_pos, ushort col_pos);

/**
 * @brief Utiliza uma metodologia de "grafo" isto e, muito parecido com o metodo de pesquisa DFS vai atribuindo valores e se for atribuido o valor errado volta atras
 * @param sudoku[N][N] array bidemensional com a canvas de jogo
 * @see valorLivre()
 * @see verificarPosicao()
 * @return 1 se o sudoku for resolvido
 * @return 0 se encontrar um "beco sem saida"
 */
int resolverSudoku(struct pixel sudoku[N][N]);

/**
 * @brief Utiliza as funcoes verificar Linha, Coluna e Quadrado para calcular a lista de possibilidades
 * @param sudoku[N][N] array bidemensional com a canvas de jogo
 * @param row row do elemento onde se comeca a pesquisa
 * @param col col do elemento onde se comeca a pesquisa
 * @see verificarQuadrado()
 * @see verificarLinha()
 * @see verificarColuna()
 */
void verificarRegras(struct pixel sudoku[N][N], ushort row, ushort col);

int verificarSudoku(struct pixel sudoku[N][N], ushort &row, ushort &col);