#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//============================================================================

// Estrutura de território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//============================================================================

// Limpar buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//============================================================================

// Vetor de missões
char *missoes[] = {
    "Conquistar 2 territorios",
    "Ter pelo menos 10 tropas no total",
    "Possuir mais de 15 tropas no total",
    "Controlar um territorio da cor vermelha",
    "Eliminar um territorio inimigo"
};

int totalMissoes = 5;

//============================================================================

// Atribuir missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

//============================================================================

// Exibir missão
void exibirMissao(char* missao) {
    printf("===================================\n");
    printf("Sua missao: %s\n", missao);
    printf("===================================\n");
}

//============================================================================

// Verificar missão
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    if (strcmp(missao, "Conquistar 2 territorios") == 0) {
        int count = 0;

        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) {
                count++;
            }
        }
        return count >= 2;
    }

    if (strcmp(missao, "Ter pelo menos 10 tropas no total") == 0) {
        int total = 0;

        for (int i = 0; i < tamanho; i++) {
            total += mapa[i].tropas;
        }
        return total >= 10;
    }

    if (strcmp(missao, "Possuir mais de 15 tropas no total") == 0) {
        int total = 0;

        for (int i = 0; i < tamanho; i++) {
            total += mapa[i].tropas;
        }
        return total > 15;
    }

    if (strcmp(missao, "Controlar um territorio da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) {
                return 1;
            }
        }
    }

    return 0;
}

//============================================================================

// Adicionar território
void adicionarTerritorio(Territorio mapa[], int tamanhoMax, int *numTerritorios) {

    if (*numTerritorios < tamanhoMax) {
        printf("====================================\n");
        printf("Cadastro do Território %d:\n", *numTerritorios + 1);

        printf("Digite o nome do território: ");
        fgets(mapa[*numTerritorios].nome, 30, stdin);
        mapa[*numTerritorios].nome[strcspn(mapa[*numTerritorios].nome, "\n")] = '\0';

        printf("Digite a cor do território: ");
        fgets(mapa[*numTerritorios].cor, 10, stdin);
        mapa[*numTerritorios].cor[strcspn(mapa[*numTerritorios].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[*numTerritorios].tropas);

        limparBuffer();
        (*numTerritorios)++;
    } else {
        printf("Limite de territórios atingido!\n");
    }
}

//============================================================================

// Listar territórios
void listarTerritorios(Territorio mapa[], int numTerritorios) {
    printf("====================================\n");
    printf("Mapa dos Territórios:\n");
    printf("====================================\n");

    for (int i = 0; i < numTerritorios; i++) {
        printf("%d. %s - Cor: %s - Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

//============================================================================

// Função de ataque (atualizada)
void atacar(int numTerritorios, Territorio mapa[]) {
    int territorioAtacante, territorioDefensor;

    printf("===================================\n");
    printf("Fase de Ataque\n");
    printf("===================================\n");

    printf("Escolha o territorio atacante (1-%d): ", numTerritorios);
    scanf("%d", &territorioAtacante);

    printf("Escolha o territorio defensor (1-%d): ", numTerritorios);
    scanf("%d", &territorioDefensor);

    limparBuffer();

    territorioAtacante--;
    territorioDefensor--;

    // Validações
    if (territorioAtacante < 0 || territorioAtacante >= numTerritorios ||
        territorioDefensor < 0 || territorioDefensor >= numTerritorios) {
        printf("Territorio invalido!\n");
        return;
    }

    if (territorioAtacante == territorioDefensor) {
        printf("Um territorio nao pode atacar ele mesmo!\n");
        return;
    }

    if (strcmp(mapa[territorioAtacante].cor, mapa[territorioDefensor].cor) == 0) {
        printf("Nao pode atacar territorio da mesma cor!\n");
        return;
    }

    if (mapa[territorioAtacante].tropas < 1) {
        printf("Atacante sem tropas!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Atacante (%s): %d\n", mapa[territorioAtacante].nome, dadoAtacante);
    printf("Defensor (%s): %d\n", mapa[territorioDefensor].nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");

        int tropasTransferidas = mapa[territorioAtacante].tropas / 2;

        mapa[territorioDefensor].tropas = tropasTransferidas;
        mapa[territorioAtacante].tropas -= tropasTransferidas;

        strcpy(mapa[territorioDefensor].cor, mapa[territorioAtacante].cor);

    } else {
        printf("Defensor venceu!\n");
        mapa[territorioAtacante].tropas--;
    }
}

//============================================================================

// Liberar memória
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

//============================================================================

int main() {

    srand(time(NULL));

    int tamanhoMax;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &tamanhoMax);
    limparBuffer();

    Territorio *mapa = malloc(tamanhoMax * sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    int numTerritorios = 0;

    while (numTerritorios < tamanhoMax) {
        adicionarTerritorio(mapa, tamanhoMax, &numTerritorios);
    }

    listarTerritorios(mapa, numTerritorios);

    // Missão
    char *missaoJogador = malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    exibirMissao(missaoJogador);

    int resposta;

    do {
        atacar(numTerritorios, mapa);

        listarTerritorios(mapa, numTerritorios);

        // Verifica missão
        if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
            printf("\nMISSÃO CUMPRIDA! VOCE VENCEU!\n");
            break;
        }

        printf("Continuar? (1 = sim / 0 = nao): ");
        scanf("%d", &resposta);
        limparBuffer();

    } while (resposta != 0);

    liberarMemoria(mapa, missaoJogador);

    return 0;
}