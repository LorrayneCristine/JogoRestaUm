//Lorrayne Cristine Ferreira Santos     BCC201-44      20.1.4009
#include "funcoes.h"
    
int main (int argc, char **argv){

    int n, x = 0, y=0; 

    if(argc == 1){//quando for passado só um argumento

        tituloRestaUm();
        Menu(&n);

        while(n != 1 && n != 2){//valida a opção de n
            Menu(&n);
        }

        if(n == 1){
            dimensaoAleatoria(&x, &y);//define dimensões aleatórias
        }
        
        else if(n == 2){
            dimensaoEscolhida(&x, &y);//define dimensões escolhidas pelo usuário
        }

        int **matriz = malloc(x * sizeof(int*));//aloca matriz
        for(int i = 0; i < x; i ++){
            matriz[i] = malloc(y * sizeof(int));
        }

        instrucoes();
        criaJogo(x, y, matriz);
        tabuleiroAceito(x, y, matriz);
        jogadas(x, y, matriz);

        for (int i=0; i < x; i++) {//liberando a matriz
            free(matriz[i]);
        }

        free(matriz); 

    }

    if(argc == 2){// quando tem 2 argumentos

        int **matriz = malloc(x * sizeof(int*));//aloca matriz
        for(int i = 0; i < x; i ++){
            matriz[i] = malloc(y * sizeof(int));
        }
        
        matriz = lerumarquivo(argv[1], &x, &y);//define matriz de acordo com o arquivo

        tituloRestaUm();
        instrucoes();
        imprimeJogo(x, y, matriz);
        jogadas(x, y, matriz);

        for (int i=0; i < x; i++) {//liberando a matriz
            free(matriz[i]);
        }

        free(matriz); 
        
    }

    return 0;
}






