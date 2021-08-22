//Lorrayne Cristine Ferreira Santos     BCC201-44      20.1.4009

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define TAM 100

void tabuleiroAceito(int x, int y, int **matriz);//usuario escolhe se quer aquele tabuleiro

void tituloRestaUm(); //imprime o titulo "resta um"

void Menu(int *n);//menu para dimensão aleatoria ou escolhida 

void dimensaoAleatoria(int *x, int *y);//define a dimensão aleatoria

void dimensaoEscolhida(int *x, int *y);//define a dimensão de acordo com a opção do usuario

void instrucoes();//imprime as instruções do jogo

void criaJogo(int x, int y, int **matriz);//cria a matriz que será utilizada

void jogadas(int x, int y, int **matriz);//define as jogadas, movimentos e comandos

int ContinuaPerde(int x, int y,int  **matriz);//analisa perdeu ou ainda tem jogo, retorna caso ganho também

void imprimeJogo(int x, int y, int **matriz);//imprime o jogo na tela

int ganhou(int x, int y, int **matriz);//analisa se ganhou

int **lerumarquivo(char *argv, int *x, int *y);//le o arquivo disponibilizado pelo usuário na entrada

int validaDirecao(char direcao);//valida a direção digitada

int validaColuna(int y, int colunaPassa);//valida a coluna digitada

int validalinha(int x, int linhaPassa);//valida a linha digitada

void imprimePerdeuGanhou(int resultado);//imprime na tela se o usuário ganhou ou perdeu

void JogarSalvarSair(int *opcao);//opções caso queira jogar, ajuda, retroceder movimento, salvar, sair

void salvaJogo (int x, int y, int **matriz);//salva o jogo quando o usuário pede

void salvaRetornaJogada (int x, int y, int **matriz);//salva o jogo para que seja possivel retornar jogada

void retornaJogada(int **matriz);// retorna a jogada

void ajuda(int x, int y, int **matriz);//faz os movimentos de ajuda

void movimentos(char direcao, int linha, int coluna, int x, int y, int **matriz);//faz os movimentos requiridos pelo usuário









