#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
    int dono;
} Territorio;

Territorio* cadastrarTerritorios(int qtd);
void listarTerritorios(Territorio *t, int qtd);
void simularBatalha(Territorio *t, int qtd);
void liberarMemoria(Territorio *t);

int main() {
    srand(time(NULL));

    Territorio *territorios = NULL;
    int opcao;

    territorios = (Territorio*) calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    do {
        printf("\n=== NÍVEL AVENTUREIRO: BATALHAS ESTRATÉGICAS ===\n");
        printf("1 - Cadastrar Territorios\n");
        printf("2 - Listar Territorios\n");
        printf("3 - Fase de Ataque\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                free(territorios);
                territorios = cadastrarTerritorios(QTD_TERRITORIOS);
                break;
            case 2:
                listarTerritorios(territorios, QTD_TERRITORIOS);
                break;
            case 3:
                simularBatalha(territorios, QTD_TERRITORIOS);
                break;
            case 4:
                liberarMemoria(territorios);
                printf("Memoria liberada. Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 4);

    return 0;
}

Territorio* cadastrarTerritorios(int qtd) {
    Territorio *t = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (t == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    printf("\n=== Cadastro de Territorios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: ");
        fgets(t[i].nome, 50, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(t[i].cor, 20, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &t[i].tropas);
        getchar();

        t[i].dono = 1;
    }

    printf("\nTerritorios cadastrados com sucesso!\n");
    return t;
}

void listarTerritorios(Territorio *t, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", t[i].nome);
        printf("Cor: %s\n", t[i].cor);
        printf("Tropas: %d\n", t[i].tropas);
        printf("Dono: %s\n", t[i].dono == 1 ? "Jogador" : (t[i].dono == 2 ? "Inimigo" : "Neutro"));
    }
}

void simularBatalha(Territorio *t, int qtd) {
    int atq, def;
    int dadoAtaque, dadoDefesa;

    listarTerritorios(t, qtd);

    printf("\nEscolha o número do território ATACANTE (1 a %d): ", qtd);
    scanf("%d", &atq);
    printf("Escolha o número do território DEFENSOR (1 a %d): ", qtd);
    scanf("%d", &def);

    atq--;
    def--;

    if (atq < 0 || atq >= qtd || def < 0 || def >= qtd) {
        printf("Territórios inválidos!\n");
        return;
    }

    if (t[atq].tropas <= 1) {
        printf("O território atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    printf("\nIniciando batalha entre %s e %s!\n", t[atq].nome, t[def].nome);

    dadoAtaque = rand() % 6 + 1;
    dadoDefesa = rand() % 6 + 1;

    printf("Dado do ataque: %d\n", dadoAtaque);
    printf("Dado da defesa: %d\n", dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        t[def].tropas--;
        printf("Ataque bem-sucedido! %s perdeu 1 tropa.\n", t[def].nome);
        if (t[def].tropas <= 0) {
            printf("%s foi conquistado!\n", t[def].nome);
            t[def].dono = t[atq].dono;
            t[def].tropas = 1;
            t[atq].tropas--;
        }
    } else if (dadoDefesa > dadoAtaque) {
        t[atq].tropas--;
        printf("Defesa bem-sucedida! %s perdeu 1 tropa.\n", t[atq].nome);
    } else {
        printf("Empate! Nenhuma tropa perdida.\n");
    }

    printf("\n--- Resultado Após Batalha ---\n");
    listarTerritorios(t, qtd);
}

void liberarMemoria(Territorio *t) {
    free(t);
}
