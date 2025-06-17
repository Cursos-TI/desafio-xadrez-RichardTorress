#include <stdio.h>

   int main() {
    // Variáveis movimentos
    int movimentosTorre = 5;
    int movimentosBispo = 5;
    int movimentosRainha = 8;
    
    // Variáveis das peças
    int i = 0;
    int j = 0;
    int k = 0;

    // Movimento da Torre (5 casas para a direita) usando for
    printf("Movimento da Torre:\n");
    for (int i = 0; i < movimentosTorre; i++) {
        printf("Direita\n");
    }

    // Movimento do Bispo (5 casas na diagonal superior direita) usando while
    printf("\nMovimento do Bispo:\n");
    
    while (j < movimentosBispo) {
        printf("Cima Direita\n");
        j++;
    }

    // Movimento da Rainha (8 casas para a esquerda) usando do while
    printf("\nMovimento da Rainha:\n");
    
    do {
        printf("Esquerda\n");
        k++;
    } while (k < movimentosRainha);

    return 0;
}