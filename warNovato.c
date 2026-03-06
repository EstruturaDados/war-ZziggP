#include <stdio.h>
#include <string.h> // Para manipulação de strings com strcspn

//============================================================================
// Definir as constantes globais
#define MAX_TERRITORIOS 5
#define MAX_STRING 20
//============================================================================

// Definindo a estrutura para representar um território
typedef struct {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropas;
} Territorio;

//limpar o buffer de entrada para evitar problemas com fgets
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main (){

// Criar um array de territórios
    Territorio mapa[MAX_TERRITORIOS];
    int numTerritorios = 0;
    int opcao;

    do {

        // Exibe o menu de opções
        printf("===================================\n");
        printf("\nJogo de Guerra\n");
        printf("===================================\n");
        printf("1. Adicionar território\n");
        printf("2. Listar Regras\n");
        printf("3. Listar Mapa\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Limpar o buffer de entrada para evitar problemas com fgets
        limparBuffer();

        switch (opcao) {
            case 1:
                while (numTerritorios < MAX_TERRITORIOS)
                {
                    // Adicionar um novo território
                    if (numTerritorios < MAX_TERRITORIOS) {
                        printf("Digite o nome do território: ");
                        fgets(mapa[numTerritorios].nome, MAX_STRING, stdin); // Lê o nome do território
                        mapa[numTerritorios].nome[strcspn(mapa[numTerritorios].nome, "\n")] = '\0'; // Remove a nova linha

                        printf("Digite a cor do território: ");
                        fgets(mapa[numTerritorios].cor, MAX_STRING, stdin); // Lê a cor do território
                        mapa[numTerritorios].cor[strcspn(mapa[numTerritorios].cor, "\n")] = '\0'; // Remove a nova linha

                        printf("Digite o número de tropas: ");
                        scanf("%d", &mapa[numTerritorios].tropas); // Lê o número de tropas

                        // Limpa o buffer de entrada após ler o número de tropas
                        limparBuffer();
                        
                        // Incrementa o número de territórios cadastrados
                        numTerritorios++;
                    } else {
                        printf("Limite de territórios atingido!\n");
                    }
                }
                
                
                // Listando os territórios cadastrados pós cadastro de todos os territórios
                for (int i = 0; i < numTerritorios; i++) { // Loop para listar os territórios cadastrados
                    printf("-----------------------------------\n");
                    printf("Território %d:\n", i + 1); // Exibe o número do território (começando de 1)
                    printf("Nome: %s\n", mapa[i].nome); // Exibe o nome do território
                    printf("Cor: %s\n", mapa[i].cor); // Exibe a cor do território
                    printf("Tropas: %d\n", mapa[i].tropas); // Exibe o número de tropas do território
                    printf("-----------------------------------\n");
                }

                // Espera o usuário pressionar Enter para continuar
                printf("Pressione Enter para continuar...");
                getchar(); // Espera o usuário pressionar Enter
                break;

            case 2:
                // Listar as regras do jogo
                printf("\nRegras do Jogo de Guerra:\n");
                printf("Regras ainda não implementadas!\n");
                break;

            case 3:
                
                // Listar os territórios cadastrados
                printf("====================================\n");
                printf("\nMapa dos Territórios:\n");
                printf("====================================\n");
                for (int i = 0; i < numTerritorios; i++) { // Loop para listar os territórios cadastrados
                    printf("-----------------------------------\n");
                    printf("Território %d:\n", i + 1); // Exibe o número do território (começando de 1)
                    printf("Nome: %s\n", mapa[i].nome); // Exibe o nome do território
                    printf("Cor: %s\n", mapa[i].cor); // Exibe a cor do território
                    printf("Tropas: %d\n", mapa[i].tropas); // Exibe o número de tropas do território
                    printf("-----------------------------------\n");
                }
                break;
            case 4:
                // Usuario escolheu sair do jogo
                printf("Saindo do jogo. Até a próxima!\n");
                break;
            default:
                // Opção inválida, usuario digita um número que não corresponde a nenhuma opção do menu
                printf("Opção inválida! Tente novamente.\n");
                break;
        }


    } while (opcao != 4); // Continua o loop até que o usuário escolha a opção de sair

}
