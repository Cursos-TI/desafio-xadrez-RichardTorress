
#include <stdio.h>
#include <stdlib.h>  // para abs()

#define TAM_TAB 10
#define NAVIO_COD 3
#define AGUA 0
#define EFEITO 5

// padrão das matrizes de habilidade
#define H_LIN 3
#define H_COL 5
#define H_CENT_LIN 1
#define H_CENT_COL 2

// inicializa todo o tabuleiro com água (0)
void initTabuleiro(int T[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++)
        for (int j = 0; j < TAM_TAB; j++)
            T[i][j] = AGUA;
}

// coloca navios fixos (nível intermediário)
// 1) horizontal em (1,2→4)
// 2) vertical em (4→6,5)
// 3) diagonal ↘ em (6→8,1→3)
// 4) diagonal ↙ em (3→1,7→9)
void posicionaNavios(int T[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < 3; i++) {
        T[1][2 + i] = NAVIO_COD;       // horiz
        T[4 + i][5] = NAVIO_COD;       // vert
        T[6 + i][1 + i] = NAVIO_COD;   // diag ↘
        T[3 - i][7 + i] = NAVIO_COD;   // diag ↙
    }
}

// cria a matriz 3×5 do CONE (ponta para baixo)
void criarCone(int M[H_LIN][H_COL]) {
    for (int i = 0; i < H_LIN; i++) {
        for (int j = 0; j < H_COL; j++) {
            // linha 0: só coluna 2
            // linha 1: colunas 1 a 3
            // linha 2: colunas 0 a 4
            if (j >= H_CENT_COL - i && j <= H_CENT_COL + i)
                M[i][j] = 1;
            else
                M[i][j] = 0;
        }
    }
}

// cria a matriz 3×5 da CRUZ (ponto central)
void criarCruz(int M[H_LIN][H_COL]) {
    for (int i = 0; i < H_LIN; i++) {
        for (int j = 0; j < H_COL; j++) {
            if (i == H_CENT_LIN || j == H_CENT_COL)
                M[i][j] = 1;
            else
                M[i][j] = 0;
        }
    }
}

// cria a matriz 3×5 do OCTAEDRO (losango) via distância de Manhattan ≤ 1
void criarOctaedro(int M[H_LIN][H_COL]) {
    for (int i = 0; i < H_LIN; i++) {
        for (int j = 0; j < H_COL; j++) {
            if ( abs(i - H_CENT_LIN) + abs(j - H_CENT_COL) <= 1 )
                M[i][j] = 1;
            else
                M[i][j] = 0;
        }
    }
}

// sobrepõe M (0/1) no tabuleiro T, centrando em (origLinha,origColuna)
// marca com EFEITO=5 sem apagar navios (3)
void aplicarHabilidade(int T[TAM_TAB][TAM_TAB],
                      int M[H_LIN][H_COL],
                      int origLinha, int origColuna)
{
    for (int i = 0; i < H_LIN; i++) {
        for (int j = 0; j < H_COL; j++) {
            if (M[i][j] == 1) {
                int li = origLinha + (i - H_CENT_LIN);
                int co = origColuna + (j - H_CENT_COL);
                if (li >= 0 && li < TAM_TAB && co >= 0 && co < TAM_TAB) {
                    if (T[li][co] != NAVIO_COD)
                        T[li][co] = EFEITO;
                }
            }
        }
    }
}

// exibe o tabuleiro inteiro 10×10
void exibirTabuleiro(int T[TAM_TAB][TAM_TAB]) {
    printf("\nTabuleiro Final (0=Água,3=Navio,5=Efeito):\n\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            printf("%d ", T[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tab[TAM_TAB][TAM_TAB];
    int cone[H_LIN][H_COL],
        cruz[H_LIN][H_COL],
        octa[H_LIN][H_COL];

    // 1. inicializa tabuleiro e navios
    initTabuleiro(tab);
    posicionaNavios(tab);

    // 2. cria dinamicamente as matrizes 3×5
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octa);

    // 3. aplica as habilidades em pontos de origem distintos
    //    você pode alterar essas coordenadas direto aqui
    aplicarHabilidade(tab, cone, 2, 5);   // cone apontando pra baixo, com topo em (2,5)
    aplicarHabilidade(tab, cruz, 5, 2);   // cruz centrada em (5,2)
    aplicarHabilidade(tab, octa, 7, 7);   // octaedro centrado em (7,7)

    // 4. exibe o resultado final
    exibirTabuleiro(tab);

    return 0;
}
