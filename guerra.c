// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
#include <stdio.h>
#include <string.h>

// Definição da struct Territorio

typedef struct {

    char nome [50];
    char cor [20];
    int tropas;
    
} Territorio;

int main() {
    struct Territorio;
    int i;

    printf("=== Cadastro de Territorios ===\n");

    for (i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritorio %d:\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]", t[i].nome); // lê até o enter

        printf("Cor do exercito: ");
        scanf(" %[^\n]", t[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &t[i].tropas);
    }

    printf("\n=== Estado Atual do Mapa ===\n");
    for (i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", t[i].nome);
        printf("Cor do exercito: %s\n", t[i].cor);
        printf("Numero de tropas: %d\n", t[i].tropas);
    }

    return 0;
}

