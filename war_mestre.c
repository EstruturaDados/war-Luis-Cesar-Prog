#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------- CONSTANTES --------------------
#define QTD_TERRITORIOS 5
#define QTD_MISSOES 5

// -------------------- ESTRUTURAS --------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
    int dono; // 1 = Jogador, 2 = Inimigo
} Territorio;

// -------------------- PROTÓTIPOS --------------------
Territorio* cadastrarTerritorios(int qtd);
void listarTerritorios(Territorio *t, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *t, char *missaoJogador, char *missaoInimigo);

void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void exibirMissao(const char *missao);

// -------------------- FUNÇÃO PRINCIPAL --------------------
int main() {
    srand(time(NULL));

    // Aloca dinamicamente os territórios
    Territorio *territorios = (Territorio*) calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória para os territórios!\n");
        return 1;
    }

    // Cria o vetor de missões disponíveis
    char *missoes[QTD_MISSOES] = {
        "Conquistar 2 territórios inimigos.",
        "Eliminar todas as tropas da cor vermelha.",
        "Manter pelo menos 3 territórios com 5 tropas ou mais.",
        "Conquistar o primeiro e o último território do mapa.",
        "Reduzir todos os inimigos a menos de 2 tropas em qualquer território."
    };

    // Aloca memória para as missões dos jogadores
    char *missaoJogador = (char*) malloc(200 * sizeof(char));
    char *missaoInimigo = (char*) malloc(200 * sizeof(char));
    if (!missaoJogador || !missaoInimigo) {
        printf("Erro ao alocar memória para as missões!\n");
        free(territorios);
        return 1;
    }

    // Sorteia missões diferentes para cada jogador
    atribuirMissao(missaoJogador, missoes, QTD_MISSOES);
    atribuirMissao(missaoInimigo, missoes, QTD_MISSOES);

    // Cadastra os territórios
    territorios = cadastrarTerritorios(QTD_TERRITORIOS);

    printf("\n=== MISSÃO DO JOGADOR ===\n");
    exibirMissao(missaoJogador);

    int opcao;
    do {
        printf("\n=== MENU DE GUERRA ===\n");
        printf("1 - Listar Territórios\n");
        printf("2 - Atacar\n");
        printf("3 - Consultar Missão\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                listarTerritorios(territorios, QTD_TERRITORIOS);
                break;

            case 2: {
                int atq, def;
                listarTerritorios(territorios, QTD_TERRITORIOS);
                printf("\nEscolha o território atacante (1 a %d): ", QTD_TERRITORIOS);
                scanf("%d", &atq);
                printf("Escolha o território defensor (1 a %d): ", QTD_TERRITORIOS);
                scanf("%d", &def);
                getchar();

                if (atq < 1 || atq > QTD_TERRITORIOS || def < 1 || def > QTD_TERRITORIOS) {
                    printf("Entrada inválida.\n");
                    break;
                }

                if (territorios[atq - 1].dono == territorios[def - 1].dono) {
                    printf("Você não pode atacar um território aliado!\n");
                    break;
                }

                atacar(&territorios[atq - 1], &territorios[def - 1]);
                break;
            }

            case 3:
                exibirMissao(missaoJogador);
                break;

            case 4:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

        // Após cada turno, verifica se a missão foi cumprida
        if (verificarMissao(missaoJogador, territorios, QTD_TERRITORIOS)) {
            printf("\n🎉 PARABÉNS! Você completou sua missão e venceu o jogo!\n");
            break;
        }

    } while (opcao != 4);

    liberarMemoria(territorios, missaoJogador, missaoInimigo);
    return 0;
}

// -------------------- FUNÇÕES AUXILIARES --------------------

// Cria e cadastra os territórios dinamicamente
Territorio* cadastrarTerritorios(int qtd) {
    Territorio *t = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (t == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    printf("\n=== Cadastro de Territórios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        fgets(t[i].nome, 30, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(t[i].cor, 10, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &t[i].tropas);
        getchar();

        t[i].dono = (i % 2 == 0) ? 1 : 2; // alterna dono: jogador/inimigo
    }

    printf("\nTerritórios cadastrados com sucesso!\n");
    return t;
}

// Lista todos os territórios e seus estados
void listarTerritorios(Territorio *t, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] %s\n", i + 1, t[i].nome);
        printf("Cor: %s\n", t[i].cor);
        printf("Tropas: %d\n", t[i].tropas);
        printf("Dono: %s\n", t[i].dono == 1 ? "Jogador" : "Inimigo");
    }
}

// Simula o ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("O território atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    printf("\n--- Batalha: %s (A) vs %s (D) ---\n", atacante->nome, defensor->nome);

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("Dado do ataque: %d | Dado da defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        defensor->tropas -= 1;
        printf("Ataque bem-sucedido! %s perdeu 1 tropa.\n", defensor->nome);
        if (defensor->tropas <= 0) {
            printf("%s foi conquistado!\n", defensor->nome);
            defensor->dono = atacante->dono;
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas /= 2;
        }
    } else {
        atacante->tropas -= 1;
        printf("Defesa bem-sucedida! %s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Sorteia uma missão e copia para a variável do jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão do jogador (sem alterar nada)
void exibirMissao(const char *missao) {
    printf("Sua missão: %s\n", missao);
}

// Verifica se a missão foi cumprida
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    // Simplificação: se o jogador controlar todos os territórios inimigos, ele vence
    int territoriosJogador = 0;
    for (int i = 0; i < tamanho; i++) {
        if (mapa[i].dono == 1)
            territoriosJogador++;
    }

    if (territoriosJogador == tamanho) {
        return 1; // missão cumprida
    }

    // Outras verificações específicas (podem ser expandidas futuramente)
    if (strstr(missao, "2 territorios") && territoriosJogador >= 2) return 1;
    if (strstr(missao, "3 territorios") && territoriosJogador >= 3) return 1;

    return 0;
}

// Libera toda a memória alocada dinamicamente
void liberarMemoria(Territorio *t, char *missaoJogador, char *missaoInimigo) {
    free(t);
    free(missaoJogador);
    free(missaoInimigo);
}