// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
#include <stdio.h>
#include <string.h>

// Quantos territórios serão cadastrados
#define QTD_TERRITORIOS 5

// Estrutura de um território usando typedef
typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

int main() {
    Territorio t[QTD_TERRITORIOS]; // Array de territórios
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