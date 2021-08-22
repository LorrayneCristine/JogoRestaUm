//Lorrayne Cristine Ferreira Santos     BCC201-44      20.1.4009

//importando bibliotecas padroes 
#include "funcoes.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include  <stdlib.h>
#include"CORES.h"
#define TAM 100

//definindo struct que será usada
typedef struct 
{   
    char linha;
    char coluna;
    char direcao;

}Jogadas;

//imprime o titulo do jogo
void tituloRestaUm(){

    printf("\n\n\t\t█▀▀█ █▀▀ █▀▀ ▀▀█▀▀ █▀▀█   █░░█ █▀▄▀█\n");//nome do jogo 
    printf("\t\t█▄▄▀ █▀▀ ▀▀█ ░░█░░ █▄▄█   █░░█ █░▀░█\n");
    printf("\t\t█░▒█ ▀▀▀ ▀▀▀ ░░▀░░ ▀░░▀   ░▀▀▀ ▀░░░▀\n\n");
}

//menu do jogo de dimensão aleatória ou escolhida
void Menu(int *n){
    char num;
    do{
        
        printf("\n\n\t\t\t𝕀 ℕ 𝕀 ℂ 𝕀 𝕆\n");//menu para escolha da dimensão
        printf("\n\t---------------------------------------------------------------\n");
        printf("\t 1 - Começar um novo jogo aleatório                           \n");
        printf("\t 2 - Começar um novo jogo escolhendo a dimensão do tabuleiro  \n");
        printf("\t                                                              \n");
        printf("\t Escolha a opção de jogo (1 ou 2): ");
        scanf(" %c", &num);
        printf("\t---------------------------------------------------------------\n");
        *n = num - 48;
    }while(*n != 1 && *n!= 2);
}  

//definindo dimensoes aleatorias do tabuleiro 
void dimensaoAleatoria(int *x, int *y){

    srand(time(NULL));
    *x = rand () % 10 + 1;//definindo uma dimensão aleatória entre 1 e 10
    *y = rand () % 10 + 1;

    if(*x <= 3){//caso for menor ou igual a 3, será somado 5
        *x = *x + 5;
    }

    if(*y <= 3){
        *y = *y + 5;
    }

    if(*x == 4){//caso for == 4, será somado 1
        *x = *x + 1;
    }

    if(*y == 4){
        *y = *y + 1;
    }
}

// definindo dimensoes escolnhidas do jogo 
void dimensaoEscolhida(int *x, int *y){

    do{
    printf("\n\t * Digite as dimensões da matriz: \n");
    printf("\t * Linha X coluna ( 4 < Linha && coluna < 16 ): ");
    scanf("%d %d", x, y);
    }while(*x < 5 || *y < 5 || *x > 15|| *y > 15);//definindo os limites da dimensão

}

//mostra as instruções e comandos de jogo para o usuario
void instrucoes(){
    printf("\n\n\t\t\t𝕀 ℕ 𝕊 𝕋 ℝ 𝕌 ℂ 𝕆 𝔼 𝕊\n");

    printf("\n\t--------------------------------\n");
    printf("\t| Espaços vazios         |"); printf("%s  o  %s|\n",ANSI_BG_COLOR_CYAN,ANSI_RESET);//colocando efeito de cor na impressão

    printf("\t| Espaços com peças      |"); printf("%s  *  %s|\n",ANSI_BG_COLOR_GREEN,ANSI_RESET);

    printf("\t| Buracos no tabuleiro   |"); printf("%s  -  %s|\n",ANSI_BG_COLOR_BLACK,ANSI_RESET);
    printf("\t--------------------------------\n\n");

    printf("\t-------------------------------------------------\n");
    printf("\t| Para direita  =   d   ");
    printf("|  Para esquerda =   a  |\n");
    printf("\t| Para baixo    =   s   ");
    printf("|  Para cima     =   w  |\n");
    printf("\t-------------------------------------------------\n\n");

}

//cria a matriz de acordo com X e Y estabelecidos
void criaJogo(int x, int y, int **matriz){
    
    int **matriz2 = malloc(x * sizeof(int*));//alocando matriz auxiliar

    for(int i = 0; i < x; i ++){
        matriz2[i] = malloc(y * sizeof(int));
    }

    //Definindo matriz.
    //-1 não faz parte do tabuleiro
    //0 é o buraco
    //1 é peça

    int contVazio = 0;
    do{
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){

                matriz2[i][j] = rand () % 3 - 1;

                if(matriz2[i][j] == -1){//controlando quantidade de espaços vazios do tabuleiro
                    
                    if (contVazio > x/2 && contVazio > y/2)// se a quantidade de -1 grande, ela se transforma em 1
                        matriz2[i][j] = 1;

                    contVazio++;
                }
            }
        }

        int aux;

        for(int i = 0; i < x; i++){

            for(int j = 0; j < y; j++){
                aux = matriz2[i][j];
                matriz[i][j] = aux;//atribuido os valores da matriz auxiliar a matriz principal
            }
        }
    
    }while(ContinuaPerde(x, y, matriz) != 0);//se a matriz não tiver jogadas ela será refeita aleatoriamente novamente

    imprimeJogo(x, y, matriz);

    for (int i=0; i < x; i++) {
            free(matriz2[i]);//liberando a matriz
    }

    free(matriz2); 
}

//o usuário escolhe se quer jogar aquele tabuleiro
void tabuleiroAceito(int x, int y, int **matriz){
    int n, cont =0;
    do{
        printf("\tDeseja gerar outro tabuleiro?\n");
        printf("\t1 sim - 2 não: ");
        scanf("%d", &n);
        cont++;
        if(n == 1)
            criaJogo(x, y, matriz);
    }while(n == 1);

    if(cont >= 2){//caso o usuario tenha pedido novo jogo as instruções aparecem novamente
        instrucoes();
        imprimeJogo(x, y, matriz);
    }

}

//define as jogadas, movimentos e comandos

void jogadas(int x, int y, int **matriz){

    Jogadas *jogadas = malloc(TAM * sizeof(int));//alocando struct de jogadas

    int coluna = 0, linha, i = 0, opcao;//variáveis auxiliares
    char direcao;//variável auxiliar

    salvaRetornaJogada(x, y, matriz);//função que salva o jogo constantemente para caso o usuário queira retornar um movimento
 
    while( ContinuaPerde(x, y, matriz) == 0)//determinará que as jogadas se repitam enquanto for diferente perder ou ganhar
    {   

        JogarSalvarSair(&opcao);//perguntando se quer jogar 1, ajuda 2, retornar jogada 3, salvar 4, ou sair 5

        if(opcao == 1){//caso o jogador escolha jogar ele dara os comandos
        salvaRetornaJogada(x, y, matriz);//salvo o jogo pra caso o usuário queira voltar um movimento feito

            do{

                // defininfo as jogadas de acordo com o usuário
                printf("\n * Digite - Coluna X Linha X Movimento: ");
                scanf(" %c %c %c",  &jogadas[i].coluna, &jogadas[i].linha, &jogadas[i].direcao);

                //atribuindo a variáveis auxiliares
                linha = (jogadas[i].linha - 49);
                direcao = jogadas[i].direcao;

                //tranformando letra em valor
                coluna = (int)jogadas[i].coluna;
                for(int j = 0; j < 57; j++){
                   if(jogadas[i].coluna == 65+j|| jogadas[i].coluna == 97+j){
                       coluna = 0+j;
                       break;}
                }

            //determinando se a linha,coluna e direção são válidos
            }while((validalinha(x, linha) == 1) || (validaColuna(y, coluna) == 1) || (validaDirecao(direcao) == 1));

            
            //fazendo os movimentos segundo as jogas que o usuário escolheu
            movimentos(direcao, linha, coluna, x, y, matriz);

            imprimeJogo(x, y,matriz);//imprimindo a matriz com devidas alterações

        }//fim do if opcao == 1

        else if (opcao == 2) {//caso o jogador escolha ajuda os comandos do jogo
            salvaRetornaJogada(x, y, matriz);//salvo o jogo pra caso o usuário queira voltar um movimento feito
            ajuda( x, y, matriz);//funcao que determina os movimentos da ajuda
            imprimeJogo(x, y,matriz);
        }

        else if (opcao == 3 ){//caso o jogador escolha retornar os comandos do jogo
            retornaJogada(matriz);//funcao que retorna a jogada a partir da matriz salva anteriormente
        }
                
        else if(opcao == 4){// salvar o programa com nome escolhido pelo usuário
            salvaJogo (x, y, matriz);
        }

        else if(opcao == 5){//sair do programa
            break;
        }

        i++;//esta direcionando o vetor das entradas da struct

        ContinuaPerde(x, y,matriz);// analisando se a pessoa perdeu ou ganhou a partir das alterações na matriz
    }

    if(opcao == 5)//sai do jogo
        printf("\n * Obrigado por jogar! Até logo :)\n\n");


    int auxiliar = ContinuaPerde(x, y,matriz); // pega o numero retornado da funcao se ganhou = 2 ou perdeu = 1

    imprimePerdeuGanhou(auxiliar); // imprime ganhou perdeu

}//fim da funcao

//define se o usuário ainda tem movimentos, caso sim o jogo prossegue, caso não analisa se perdeu ou ganhou
int ContinuaPerde(int x, int y, int **matriz){

    if (ganhou(x, y, matriz) == 0){//funcao que define se ganhou
        return 2;
    }
    
    int cont= 0;

    for (int i = 0; i < x; i++){//analisando se ainda resta movimentos válidos
        for(int j = 0; j < y; j++){
    
            if(matriz[i][j] == 1){

                if(j + 2 < y){

                    if(matriz[i][j+1] == 1 && matriz[i][j+2]== 0){
                        cont++; 
                        break;
                    }
                }

                if(j - 2 >= 0){

                    if(matriz[i][j-1] == 1 && matriz[i][j-2]== 0){        
                        cont++;
                        break;
                    }
                }

                if(i - 2 >= 0){

                    if(matriz[i-1][j] == 1 && matriz[i-2][j]== 0){
                        cont++;
                        break;          
                    }
                }

                if(i + 2 < x){

                    if(matriz[i+1][j] == 1 && matriz[i+2][j]== 0){
                        cont++;
                        break;    
				    } 
                }                
            }  
        } 


        if(cont > 0)//retorna 0 caso tiver movimentos
        return 0;
    }
    
    return 1;//retorna 1 se não tiver movimentos
}

//imprime o tabuleiro do jogo
void imprimeJogo(int x, int y, int **matriz){
    
    printf("\n\n");
    printf("\t\t%s    %s",ANSI_BG_COLOR_YELLOW,ANSI_RESET);//concerta o espaço que fica sobrando
    //Imprimir letras

    for(int j = 0; j < y; j++){
            printf("%s%s %c %s",ANSI_BG_COLOR_WHITE,ANSI_COLOR_BLACK, 65+j, ANSI_RESET);
    }

    printf("%s  %s\n", ANSI_BG_COLOR_WHITE, ANSI_RESET);//concerta o espaço sobra

    int w = 1;//auxiliar dos números

    //-1 = -
    //0 = o
    //1 = *

    for(int i = 0; i < x; i++){

        if(i < 9)//caso o numero for menor que 9 será impresso "0" antes
            printf("\t\t%s%s 0%d %s", ANSI_BG_COLOR_WHITE,ANSI_COLOR_BLACK, w++, ANSI_RESET);

        else 
            printf("\t\t%s%s %d %s", ANSI_BG_COLOR_WHITE,ANSI_COLOR_BLACK,w++, ANSI_RESET);

        for(int j = 0; j < y; j++){

            if(matriz[i][j] == -1)
                printf("%s - %s",ANSI_BG_COLOR_BLACK,ANSI_RESET);
            else if(matriz[i][j] == 0)
                printf("%s o %s",ANSI_BG_COLOR_CYAN,ANSI_RESET);
            else if(matriz[i][j] == 1)
                printf("%s * %s",ANSI_BG_COLOR_GREEN,ANSI_RESET);
        }

        printf("%s%s  %s\n",ANSI_BG_COLOR_WHITE,ANSI_COLOR_BLACK,ANSI_RESET);//concerta o espaço sobra do lado
    }

    printf("\t\t%s%s      %s",ANSI_BG_COLOR_WHITE,ANSI_COLOR_BLACK,ANSI_RESET);//concerta o espaço sobra

    for(int i= 0; i < y; i++){
        printf("%s%s   %s", ANSI_BG_COLOR_WHITE,ANSI_COLOR_BLACK, ANSI_RESET);//concerta o espaço sobra embaixo
    }

    printf("\n\n");
}

//valida se tem só 1 peça, caso sim, ganhou
int ganhou(int x, int y, int **matriz){

    int cont = 0;

    for (int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(matriz[i][j]==1)
                cont ++;
        }
    }

    if(cont == 1)
        return 0;

    return 1;
}

//lê o arquivo texto que o usuário disponibilizar
int **lerumarquivo(char *argv, int *x, int *y)
{
    FILE *entrada;
    entrada = fopen(argv , "r");

    while (*x == 0 && *y == 0)
    {
        fscanf (entrada, "%d %d" , x, y); //Lê o valor de linha no arquivo .txt
    }

    int **matriz = malloc(*x * sizeof(int*));

    for(int i = 0; i < *x; i ++){
        matriz[i] = malloc(*y * sizeof(int));//alocando matriz
    }

    for(int i = 0; i < *x;i++)
    {
        for(int j = 0; j < *y;j++)
        {
            fscanf(entrada, "%d" , &matriz[i][j]);
        }
    }

    fclose(entrada);

    return matriz;
}

//valida se a linha digitada está dentro dos números possíveis 
int validalinha(int x, int linhaPassa){

    if(linhaPassa < x){
        return 0;}

    printf("\n- Digite uma linha válida ( 0 < Linha <= %d)\n", x); 
    return 1;
}

//valida se a coluna digitada está dentro das letras possíveis
int validaColuna(int y, int colunaPassa){
    
    if(colunaPassa < y){
        return 0;}

    printf("\n- Digite uma coluna válida (A, B, C...)\n"); 
    return 1;
   
}

//valida se a direção digitada é um comando válido
int validaDirecao(char direcao){
    switch (direcao){
        case 'a': case 'A': case 's': case 'S':case 'w': case 'W':case 'd':case 'D':
            return 0;
            break;
   }

    printf("\n- Digite uma direção válida (a, s, w, d)\n"); 
    return 1;
}

//Imprime o resultado do jogo do usuário
void imprimePerdeuGanhou(int resultado){
    if(resultado == 1){
         printf(RED(BOLD("\n\n")));       
    printf(RED(BOLD("\t `YMM\'   `MM\'                     `7MMF\'                                 OO      \n"))); 
    printf(RED(BOLD("\t   VMA   ,V                         MM                                   88         \n"))); 
    printf(RED(BOLD("\t    VMA ,V ,pW\"Wq.`7MM  `7MM        MM         ,pW\"Wq.  ,pP\"Ybd  .gP\"Ya  ||     \n"))); 
    printf(RED(BOLD("\t     VMMP 6W\'   `Wb MM    MM        MM        6W\'   `Wb 8I   `\" ,M\'   Yb ||     \n"))); 
    printf(RED(BOLD("\t      MM  8M     M8 MM    MM        MM      , 8M     M8 `YMMMa. 8M\"\"\"\"\"\" `\'  \n"))); 
    printf(RED(BOLD("\t      MM  YA.   ,A9 MM    MM        MM     ,M YA.   ,A9 L.   I8 YM.    , ,,         \n")));      
    printf(RED(BOLD("\t    .JMML. `Ybmd9\'  `Mbod\"YML.    .JMMmmmmMMM  `Ybmd9\'  M9mmmP\'  `Mbmmd\' db    \n"))); 
    printf(RED(BOLD("\n\n")));       
    }

    if(resultado == 2){
        printf(BLUE(BOLD("\n\n")));       
        printf(BLUE(BOLD("\t                                                        ,,                        \n"))); 
        printf(BLUE(BOLD("\t `YMM\'   `MM\'                     `7MMF\'     A     `7MF\'db              OO    \n"))); 
        printf(BLUE(BOLD("\t   VMA   ,V                         `MA     ,MA     ,V                  88        \n"))); 
        printf(BLUE(BOLD("\t    VMA ,V ,pW\"Wq.`7MM  `7MM         VM:   ,VVM:   ,V `7MM  `7MMpMMMb.  ||       \n"))); 
        printf(BLUE(BOLD("\t     VMMP 6W\'   `Wb MM    MM          MM.  M\' MM.  M\'   MM    MM    MM  ||     \n"))); 
        printf(BLUE(BOLD("\t      MM  8M     M8 MM    MM          `MM A\'  `MM A\'    MM    MM    MM  `'      \n")));      
        printf(BLUE(BOLD("\t      MM  YA.   ,A9 MM    MM           :MM;    :MM;     MM    MM    MM  ,,        \n"))); 
        printf(BLUE(BOLD("\t    .JMML. `Ybmd9\'  `Mbod\"YML.          VF      VF    .JMML..JMML  JMML.db      \n"))); 
        printf(BLUE(BOLD("\n\n")));     
    }


}

//Determina se usuário quer 1 - jogar, 2 - ajuda, 3 - retornar um movimento, - 4 salvar, 5 - sair
void JogarSalvarSair(int *opcao){

    char numero[10];
    char *vet =" * Escolha o comando (1 jogar - 2 ajuda - 3 retornar um movimento - 4 salvar - 5 sair): ";
    printf("\n%s%s%s%s", ANSI_BOLD, ANSI_COLOR_YELLOW, vet, ANSI_RESET);//muda a cor da impressão

    fgets(numero, 9, stdin);//caso o usuário digite + de uma letra

    if(numero[0] == 10)//caso o valor seja igual ao enter deve ser lido novamente sem mensagem
        fgets(numero, 9, stdin);

    *opcao = numero[0] - 48;//transformando a entrada char em int para a validação

    while (*opcao  != 1 && *opcao != 2 && *opcao != 3 && *opcao != 4 && *opcao != 5){ //verificação caso valor digitado errado

        char *vet =" * Escolha o comando (1 jogar - 2 ajuda - 3 retornar um movimento - 4 salvar - 5 sair): ";
        printf("\n%s%s%s%s", ANSI_BOLD, ANSI_COLOR_YELLOW, vet, ANSI_RESET);
        scanf(" %c", numero);

        *opcao = numero[0] - 48;//transformando a entrada char em int para a validação      
    }
}  

//salva o jogo quando o usuário pede
void salvaJogo (int x, int y, int **matriz){

    char nome_documento[40];
    printf("\n * Digite o nome do arquivo para salvar: ");
    scanf(" %s", nome_documento);

    FILE *arquivo = fopen(nome_documento, "w");

    fprintf(arquivo, "%d %d\n", x, y);

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            fprintf(arquivo, " %3d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);

    printf(" * Seu jogo foi salvo com o nome: '%s'\n", nome_documento);
}

//salva o jogo constantemente para o usuário retornar jogada
void salvaRetornaJogada (int x, int y, int **matriz){

    FILE *arquivo = fopen("retornaJogada", "w");

    fprintf(arquivo, "%d %d\n", x, y);

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            fprintf(arquivo, " %3d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);

}

//analisa se o comando do movimento feito pelo usuário de acordo com dimensão, linha, coluna e direção. Caso certo, realiza
void movimentos(char direcao, int linha, int coluna, int x, int y, int **matriz){

    switch (direcao){

        case 'd': case 'D':
            if(coluna + 2 < y){

                if(matriz[linha][coluna+1] == 1 && matriz[linha][coluna+2]== 0){
                    matriz[linha][coluna] = 0;
                    matriz[linha][coluna+1] = 0;
                    matriz[linha][coluna+2]= 1;
                }
                else{
                    printf("\n- Movimento inválido\n");
                }
            }
            else{
                printf("\n- Movimento inválido, se atente aos limites do tabuleiro\n");
            }
            
        break;

        case 'a': case 'A':
            if(coluna - 2 >= 0){

                if(matriz[linha][coluna-1] == 1 && matriz[linha][coluna-2]== 0){
                    matriz[linha][coluna] = 0;
                    matriz[linha][coluna-1] = 0;
                    matriz[linha][coluna-2] = 1;
                }
                else{
                    printf("\n- Movimento inválido\n");
                }
            }
            else{
                printf("\n- Movimento inválido, se atente aos limites do tabuleiro\n");
            }

        break;

        case 'w': case 'W':
            if(linha - 2 >= 0){

                if(matriz[linha-1][coluna] == 1 && matriz[linha-2][coluna]== 0){
                    matriz[linha][coluna] = 0;
                    matriz[linha-1][coluna] = 0;
                    matriz[linha-2][coluna] = 1;
                }
                else{
                    printf("\n- Movimento inválido\n");
                }
            }
            else{
                printf("\n- Movimento inválido, se atente aos limites do tabuleiro\n");
            }

        break;

        case 's': case 'S':
            if(linha + 2 < x){
                if(matriz[linha+1][coluna] == 1 && matriz[linha+2][coluna]== 0){
                    matriz[linha][coluna] = 0;
                    matriz[linha+1][coluna] = 0;
                    matriz[linha+2][coluna] = 1;
                }
                else{
                    printf("\n- Movimento inválido\n");
                }
            }
            else{
                printf("\n - Movimento inválido, se atente aos limites do tabuleiro\n");
            }
        break;
        
    }
}

//le o arquivo para que seja possível retornar a jogada
void retornaJogada(int **matriz){
    int x, y;
    FILE *arquivo = fopen("retornaJogada", "r");

    fscanf(arquivo, "%d %d", &x, &y);

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }

    fclose(arquivo);
    imprimeJogo(x, y, matriz);//imprime novamente a matriz
}

//funcao para fazer os movimentos de ajuda requirido pelo usuário
void ajuda(int x, int y, int **matriz){
    int n;
    printf(" - Digite a quantidade de movimentos que deseja: ");
    scanf("%d", &n);

    int cont = 0;

    do{
    for(int i = 0; i < x; i++){
        if(n == cont)
            break;

        for (int j = 0; j < y; j++){ // variavel da linha da matriz 
            if(n == cont)
                break;

            if(matriz[i][j] == 1){

                if(j + 2 < y){

                    if(matriz[i][j+1] == 1 && matriz[i][j+2]== 0){
                        matriz[i][j] = 0;
                        matriz[i][j+1] = 0;
                        matriz[i][j+2] = 1;
                        printf("\n * Linha %d - Coluna %c - Movimento D\n", i+1, j+65);
                        cont ++;

                        if(n == cont)
                            break;
                    }
                }

                if(j - 2 >= 0){

                    if(matriz[i][j-1] == 1 && matriz[i][j-2]== 0){ 
                            matriz[i][j] = 0;
                            matriz[i][j-1] = 0;
                            matriz[i][j-2] = 1; 
                            printf("\n * Linha %d - Coluna %c - Movimento A\n", i+1, j+65);
                            cont++;
                            if(n == cont)
                                break;
                    }
                }

                if(i - 2 >= 0){

                    if(matriz[i-1][j] == 1 && matriz[i-2][j]== 0){
                            matriz[i][j] = 0;
                            matriz[i-1][j] = 0;
                            matriz[i-2][j] = 1;
                            printf("\n * Linha %d - Coluna %c - Movimento W\n", i+1, j+65);
                            cont++;
                            if(n == cont)
                                break;          
                    }
                }

                if(i + 2 < x){

                    if(matriz[i+1][j] == 1 && matriz[i+2][j]== 0){
                            matriz[i][j] = 0;
                            matriz[i+1][j] = 0;
                            matriz[i+2][j] = 1;
                            printf("\n * Linha %d - Coluna %c - Movimento S\n", i+1, j+65);
                            cont++;
                            if(n == cont)
                                break;    
                    } 
                }
            }
        }
    }
    }while(cont != n && ContinuaPerde(x, y, matriz) == 0);
    
}
